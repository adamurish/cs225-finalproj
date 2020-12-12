# CS 225 Final Project
**Team Members: Armando Rodea, Adam Urish, Sebastian Moruszewicz, Jason Zou**

## Building

This project is most easily built using the "make" command. There are two targets used,

    make main
    
which produces the executable "traffic," and

    make test
    
which produces the catch testing suite executable "test."

## Getting the data

Our makefile includes a tool for grabbing the datasets off the internet and storing them in the
./datasets directory, and it can be run by executing

    make fetch

## Running

Our program can be run  using the "traffic" executable. A typical usage looks like this:

    ./traffic ./datasets/airports.dat ./datasets/routes.dat [operation] [operation arguments]
    
The first two positional arguments are the location of the airport dataset and routes dataset,
which should be formatted in the standard openflights formatting, seen [here](https://openflights.org/data.html). 
If you used the "make fetch" command, the location will be exactly as seen in the command here.
"[operation]" tells our program which operation you wish to run, and should be selected from one 
of the following:

### sssp

The sssp operation performs a shortest path calculation, and has three operation specific arguments.
A typical usage looks like this:

    ./traffic ./datasets/airports.dat ./datasets/routes.dat sssp [start airport] [end airport] [traversal]
    
[start airport] should be replaced by the IATA callsign for the airport you wish to start the shortest
path at, i.e. if you wish to start at Los Angeles International Airport you would use LAX

[end airport] should be replaced by the end of the shortest path, again using the IATA callsign

[traversal] is one of "bfs" or "dijkstra," and specifies which traversal to use to find the 
predecessors for use in the shortest path calculation.

For example, if you wished to calculate the shortest path from LAX to ORD, using BFS, you would run:

    ./traffic ./datasets/airports.dat ./datasets/routes.dat sssp LAX ORD bfs

### airportrank

The airport rank operation performs a modified PageRank algorithm to determine the relative importances
of every airport in the graph. It requires no additional arguments, thus its usage looks like:

    ./traffic ./datasets/airports.dat ./datasets/routes.dat airportrank
    
### bfs

The bfs operation runs a breadth first search across the graph, starting from a specified airport.
As such it has one additional argument, and a typical usage looks like:

    ./traffic ./datasets/airports.dat ./datasets/routes.dat bfs [start airport]
    
[start airport] should be replaced by the IATA callsign of the start airport you want.

### render

The render operation simply renders all the airports and flights that are stored in the graph.
A typical usage looks like this:

    ./traffic ./datasets/airports.dat ./datasets/routes.dat render [objects]
    
[objects] should be replaced by one of "airports," "routes," or "all." "airports" will only
draw the airports, "routes" will only draw the routes, "all" will draw them both.

## Output

Every operation will save its result in an image named "output.png" in the same directory it was run in.
This image will consist of a Mercator projection world map, overlaid with the output of whatever
operation was run. Usually it will look like a bunch of small dots representing airports, and in 
the case of airportrank the dots will be sized according to their importance. If connections between
the airports are shown, they will appear as lime green lines connecting the airports.