//
// Created by Adam on 12/9/2020.
//

#include "AirRenderer.h"
#include <cmath>

AirRenderer::AirRenderer(cs225::PNG& base, std::unordered_map<Vertex, airport>& airport_map) : base_image(base), airport_map(airport_map){
    width = base.width();
    height = base.height();
}

// @param airports A vector of airports to render
// @param radii Radii of each airport marker, in order
// @param flights A vector of flight paths to render
cs225::PNG AirRenderer::draw_airports_and_flights(const vector<airport> &airports, const vector<double>& radii, const vector<flight> &flights) {
    auto ret = cs225::PNG(base_image);
    int i = 0;
    for(const airport& ap : airports){
        //project airport onto map and then draw a circle at its location
        auto center = project(std::stod(ap.latitude), std::stod(ap.longitude));
        draw_circle(center, radii[i++], ret);
    }
    for(const flight& fl : flights){
        //project start and end onto map, then connect them with a line
        auto start = project(std::stod(airport_map[fl.src_open_ID].latitude), std::stod(airport_map[fl.src_open_ID].longitude));
        auto end = project(std::stod(airport_map[fl.dest_open_ID].latitude), std::stod(airport_map[fl.dest_open_ID].longitude));
        draw_line(start, end, ret);
    }
    return ret;
}

//utility methods for only rendering one
cs225::PNG AirRenderer::draw_flights(const vector<flight> &flights) {
    return draw_airports_and_flights(std::vector<airport>(), std::vector<double>(), flights);
}

cs225::PNG AirRenderer::draw_airports(const std::vector<airport>& airports, const vector<double>& radii) {
    return draw_airports_and_flights(airports, radii, std::vector<flight>());
}

std::pair<int, int> AirRenderer::project(double latitude, double longitude) {
    // math taken from https://en.wikipedia.org/wiki/Mercator_projection

    //radius of the globe
    double R = ((double) width) / (2 * M_PI);

    //convert longitude from degrees to radians
    double longitude_radians = longitude * (M_PI / 180.0);
    //from wikipedia, X = R * (longitude - longitude of origin)
    double x = R * (longitude_radians + M_PI);

    //latitude is given in degrees, have to convert it to use tan()
    double latitude_radians = latitude * (M_PI / 180.0);
    //y coord is calculated relative to origin, i.e. distance from equator
    double y_delta = R * (log(tan((M_PI / 4.0) + (latitude_radians / 2.0))));
    //normalize y for use in PNG, equator is the center of the image
    double y = ((double) height / 2.0) - y_delta;

    //return rounded to nearest pixel
    return {lrint(x), lrint(y)};
}

void AirRenderer::draw_circle(std::pair<int, int> center, double radius, cs225::PNG& image){
    //how many discrete lines to draw, can tweak for efficiency
    int discrete_block = 1000;
    //rotate all the way around circle
    double discrete_delta = (2 * M_PI) / (double) discrete_block;
    for(int t = 0; t < discrete_block + 1; ++t){
        //calculate coords from radius and sin/cos
        int x = lrint(center.first + (radius * cos(discrete_delta * t)));
        int y = lrint(center.second + (radius * sin(discrete_delta * t)));
        //draw line from center to edge of circle
        draw_line(center, {x, y}, image);
    }
}

void AirRenderer::draw_line(std::pair<int, int> start, std::pair<int, int> end, cs225::PNG &image) {
    //how many discrete pixels to draw, can tweak for efficiency
    int discrete_block = 1000;
    //discretized slope vector, points from start to end
    auto discrete_slope_vec = std::pair<double, double>((end.first - start.first) / (double) discrete_block, (end.second - start.second) / (double) discrete_block);
    for(int t = 0; t < discrete_block + 1; ++t){
        //calculate change in each direction using slope vector
        double delta_x = discrete_slope_vec.first * t;
        double delta_y = discrete_slope_vec.second * t;
        //calculate coords with change
        int x = lrint(delta_x + start.first);
        int y = lrint(delta_y + start.second);
        //edit pixel
        auto& pix = image.getPixel(x, y);
        pix.h = 0;
        pix.s = 1.0;
        pix.l = 0.5;
    }
}