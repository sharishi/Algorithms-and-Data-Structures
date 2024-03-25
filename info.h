//
// Created by Vica on 21.03.2024.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <array>

#ifndef INFO_H
#define INFO_H
struct ErrorFlags {
    bool invalid_id = false;
    bool invalid_continent_token = false;
    bool invalid_name = false;
    bool invalid_foundation_year = false;
    bool invalid_founder = false;
    bool invalid_country = false;
    bool invalid_latitude = false;
    bool invalid_longitude = false;
};

enum Continent
{
    ASIA, AFRICA, NORTHAMERICA, SOUTHAMERICA, ANTARCTICA, EUROPE, AUSTRALIA
};

const static size_t MaxStringLength = 100;

struct City {
    size_t id;
    std::array<char, MaxStringLength> name;
    int foundation_year;
    std::array<char, MaxStringLength> founder;
    std::array<char, MaxStringLength> country;
    float latitude;
    float longitude;
    Continent continent;
};

#endif  // INFO_H

void printErrorFlags(ErrorFlags& flags);
Continent deserialize_continent(const char* continent_token, ErrorFlags& flags);
void serialize_continent(Continent continent, FILE* file, ErrorFlags& flags);
City deserialize_city(char* buffer, ErrorFlags& flags);
void serialize_city(City* city, FILE* file, ErrorFlags& flags);
std::vector<City> read_cities_from_csv(const char* fname, ErrorFlags& flags);
void print_output(std::pair<double, City*> result_search, size_t search_id);
template<typename Func, typename... Args>
std::pair<double, decltype(std::declval<Func>()(std::declval<Args>()...))> measureTimeAndResult(Func&& func, Args&&... args);
void validateAndFillCity(City& city, ErrorFlags& flags);
bool checkErrorFlags(const ErrorFlags& flags);
