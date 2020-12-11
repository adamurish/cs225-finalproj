//
// Created by Adam on 12/9/2020.
//
#pragma once
#include "../cs225/PNG.h"
#include "../AirGraph/AirGraph.h"

class AirRenderer {
public:
    AirRenderer(cs225::PNG& base, unordered_map<Vertex, airport>& airport_map);

    // Renders airports and flights on the base canvas
    // @param airports A vector of airports to render
    // @param radii Radii of each airport marker, in order
    // @param flights A vector of flight paths to render
    cs225::PNG draw_airports_and_flights(const std::vector<airport>& airports, const vector<double>& radii, const std::vector<flight>& flights);

    // Utility method to only render airports
    cs225::PNG draw_airports(const std::vector<airport>& airports, const vector<double>& radii);
    // Utility method to only render flights
    cs225::PNG draw_flights(const std::vector<flight>& flights);
private:
    cs225::PNG base_image;
    std::unordered_map<string, airport> airport_map;
    unsigned width, height;

    // Project latitude and longitude to x and y coordinates of image
    // @param latitude The latitude in degrees
    // @param longitude The longitude in degrees
    std::pair<int, int> project(double latitude, double longitude);

    // Draw circle on given image
    // @param center The center point of the circle
    // @param radius The radius of the circle
    // @param image The reference to the image to draw on
    // @param discrete_blocks How many lines to draw to form circle, smaller circle needs less
    void draw_circle(std::pair<int, int> center, double radius, cs225::PNG& image);

    // Draw line on given image
    // @param start The start point
    // @param end The end point
    // @param image The reference to the image to draw on
    // @param discrete_blocks How many pixels to draw for line, shorter line needs less
    void draw_line(std::pair<int, int> start, std::pair<int, int> end, cs225::PNG& image, int discrete_blocks);
};
