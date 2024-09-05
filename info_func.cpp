//
// Created by Vica on 21.03.2024.
//
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <optional>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <utility>
#include "../untitled/info.h"

void printErrorFlags(ErrorFlags& flags) {
    if (flags.invalid_id) {
        std::cout << "Invalid ID!" << std::endl;
    }
    if (flags.invalid_continent_token) {
        std::cout << "Invalid continent token!" << std::endl;
    }
    if (flags.invalid_name) {
        std::cout << "Invalid name!" << std::endl;
    }
    if (flags.invalid_foundation_year) {
        std::cout << "Invalid foundation year!" << std::endl;
    }
    if (flags.invalid_founder) {
        std::cout << "Invalid founder!" << std::endl;
    }
    if (flags.invalid_country) {
        std::cout << "Invalid country!" << std::endl;
    }
    if (flags.invalid_latitude) {
        std::cout << "Invalid latitude!" << std::endl;
    }
    if (flags.invalid_longitude) {
        std::cout << "Invalid longitude!" << std::endl;
    }
}

inline Continent deserialize_continent(const char* continent_token,  ErrorFlags& flags) {
    if (strcmp(continent_token, "ASIA") == 0) {
        return ASIA;
    }
    else if (strcmp(continent_token, "AFRICA") == 0) {
        return AFRICA;
    }
    else if (strcmp(continent_token, "NORTHAMERICA") == 0) {
        return NORTHAMERICA;
    }
    else if (strcmp(continent_token, "SOUTHAMERICA") == 0) {
        return SOUTHAMERICA;
    }
    else if (strcmp(continent_token, "ANTARCTICA") == 0) {
        return ANTARCTICA;
    }
    else if (strcmp(continent_token, "EUROPE") == 0) {
        return EUROPE;
    }
    else if (strcmp(continent_token, "AUSTRALIA") == 0) {
        return AUSTRALIA;
    }
    else {
        flags.invalid_continent_token = true;
        return static_cast<Continent>(7);
    }
}


void serialize_continent(Continent continent, FILE* file, ErrorFlags& flags) {
    switch (continent) {
        case ASIA:
            fputs("ASIA", file);
            break;
        case AFRICA:
            fputs("AFRICA", file);
            break;
        case NORTHAMERICA:
            fputs("NORTHAMERICA", file);
            break;
        case SOUTHAMERICA:
            fputs("SOUTHAMERICA", file);
            break;
        case EUROPE:
            fputs("EUROPE", file);
            break;
        case AUSTRALIA:
            fputs("AUSTRALIA", file);
            break;
        default:
            flags.invalid_continent_token = true;
            fputs("NONE", file);
            break;
    }
}


City deserialize_city(char* buffer, ErrorFlags& flags) {
    City city;
    char* token = strtok(buffer, ",");

    city.id = static_cast<size_t>(std::stoi(token));

    token = strtok(NULL, ",");

    std::strncpy(city.name.data(), token, MaxStringLength);
    city.name[MaxStringLength - 1] = '\0';

    token = strtok(NULL, ",");
    city.foundation_year = std::stoi(token);

    token = strtok(NULL, ",");

    std::strncpy(city.founder.data(), token, MaxStringLength);
    city.founder[MaxStringLength - 1] = '\0';

    token = strtok(NULL, ",");

    std::strncpy(city.country.data(), token, MaxStringLength);
    city.country[MaxStringLength - 1] = '\0';

    token = strtok(NULL, ",");
    city.latitude = std::stof(token);

    token = strtok(NULL, ",");
    city.longitude = std::stof(token);

    token = strtok(NULL, ",");

    city.continent = deserialize_continent(token, flags);

    validateAndFillCity(city,flags);
    if (checkErrorFlags(flags)) {
        std::cout << "Errors found:" << std::endl;
        printErrorFlags(flags);
        static City nullCity;
        return nullCity;
    }
    return city;
}

void serialize_city(City* city, FILE* file, ErrorFlags& flags) {
    validateAndFillCity(*city,flags);
    if (checkErrorFlags(flags)) {
        std::cout << "Errors found:" << std::endl;
        printErrorFlags(flags);
        return;
    }
    fprintf(file, "%zu,", city->id);
    fprintf(file, "%s,", city->name.data());
    fprintf(file, "%d,", city->foundation_year);
    fprintf(file, "%s,", city->founder.data());
    fprintf(file, "%s,", city->country.data());
    fprintf(file, "%.6f,", city->latitude);
    fprintf(file, "%.6f,", city->longitude);
    serialize_continent(city->continent, file, flags);
}

std::vector<City> read_cities_from_csv(const char* fname, ErrorFlags& flags) {
    std::ifstream file(fname);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << fname << std::endl;
    }

    std::vector<City> result;

    // Пропускаем заголовок!!!!
    std::string header;
    std::getline(file, header);

    std::string line;
    while (std::getline(file, line)) {
        std::string_view lineView(line);
        result.push_back(deserialize_city(const_cast<char*>(lineView.data()), flags));
    }

    file.close();

    return result;
}

void print_output(std::pair<double, City*> result_search, size_t search_id) {
    double time_for_search = result_search.first;
    City* city_from_search = result_search.second;

    if (city_from_search != nullptr) {
        std::cout << "City found: " << city_from_search->id << std::endl <<
        "Name: " << city_from_search->name.data() << std::endl;
        std::cout << "Time: " << time_for_search << std::endl << std::endl;
    } else {
        std::cout << "City not found with ID: " << search_id << std::endl;
    }
}

void validateAndFillCity(City& city, ErrorFlags& flags) {

    if (city.id <= 0) {
        flags.invalid_id = true;
    }
    if (std::strlen(city.name.data()) == 0) {
        flags.invalid_name = true;
    }
    if (std::strlen(city.founder.data()) == 0) {
        flags.invalid_founder = true;
    }
    if (std::strlen(city.country.data()) == 0) {
        flags.invalid_country = true;
    }
    if (city.foundation_year <= 0) {
        flags.invalid_foundation_year = true;
    }
    if (city.latitude < -90 || city.latitude > 90) {
        flags.invalid_latitude = true;
    }
    if (city.longitude < -180 || city.longitude > 180) {
        flags.invalid_longitude = true;
    }
}
bool checkErrorFlags(const ErrorFlags& flags) {
    return (flags.invalid_id ||
           flags.invalid_continent_token ||
           flags.invalid_name ||
           flags.invalid_foundation_year ||
           flags.invalid_founder ||
           flags.invalid_country ||
           flags.invalid_latitude ||
           flags.invalid_longitude);
}

