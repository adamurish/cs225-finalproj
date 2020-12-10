//
// Created by Adam on 12/9/2020.
//
#pragma once
#include "../cs225/PNG.h"
#include "../AirGraph/AirGraph.h"

class AirRenderer {
public:
    AirRenderer(cs225::PNG& base, unordered_map<Vertex, airport>& airport_map);

    cs225::PNG draw_airports_and_flights(const std::vector<airport>& airports, const vector<double>& radii, const std::vector<flight>& flights);
    cs225::PNG draw_airports(const std::vector<airport>& airports, const vector<double>& radii);
    cs225::PNG draw_flights(const std::vector<flight>& flights);
private:
    cs225::PNG base_image;
    std::unordered_map<string, airport> airport_map;
    unsigned width, height;

    // Project latitude and longitude to x and y coordinates of image
    // @param latitude The latitude in degrees
    // @param longitude The longitude in degrees
    std::pair<int, int> project(double latitude, double longitude);

    void draw_circle(std::pair<int, int> center, double radius, cs225::PNG& image);
    void draw_line(std::pair<int, int> start, std::pair<int, int> end, cs225::PNG& image);
};
