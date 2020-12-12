# Development Log
**CS225** final project development log.

## Week 1
- Should complete core components of the project:
	- Create a file parser to read in data files
	- Design and develop the general graph structure
- Write a makefile for the project
	- A simple makefile is preferred over a complex file to reduce possibility of errors during building.
- Decided on directory structure for project.
	- We will be using separate folders for each module, then put the main file in the root of the project directory.
	- Tests employing CATCH will be stored in their own folder in the root directory.
	- Modules include the graph structure, file parser, traversal algorithms, graphics classes, and image classes from MPs. 
- Decided to follow same comment style as that employed in CS225. (Doxygen style)
- Work division:
	- File Parser: Adam and Jason
	- Beginning of graph structure: Armando and Sebastian
	- Makefile: Everyone

## Week 2
### Design Log
- Determined best method for flight data and graph correlation:
	- Graph is simple and directed where airport vertices are labeled by unique open flights id.
	- Dictionary containing airport data keyed by open flights id allows for airport lookup from graph.
	- Dictionary containing open flights id keyed by IATA code allows for user input of origin and destination airports via friendly names (i.e. ORD, LAX, JFK, ...)
- Minimized number of edges in order improve algorithm runtimes:
	- Since edge weights are determined via geographical distance between airports, only one edge is required to encode a set of flights from one airport to another in the same direction.
	- The label on each edge is an index in a vector of flight vectors allowing for retrieval of flight information for any flight between two airports.
	- Constant lookup time from vector matrix allows for minimal runtime penalties for pertinent lookups of first airline and number of airlines servicing route.
### Work Log
- Restructured project directory to properly separate project components.
- Implemented file parser to take flight data from CSV file and import it into the project.
- Implemented all core graph functionality for air traffic.
- Wrote a Makefile to build all modules and link together both the main executable and the test executable.

## Week 3

### Issues

* When developing BFS it was determined that one interface would not allow for retrieval of all information required by external code when BFS traversal is returned:
  * Resolution: Implementing separate wrappers for BFS traversal based on use case allowed for reuse of core BFS code across BFS traversal and shortestPath.
* In order to run separate algorithms, a command line interface between the user and the program was required for specifying program parameters and data file paths:
  * Issue: Used the BOOST program options library in order to parse user program parameters. We were unable to build the library within our project and resorted to dropping this library for input parsing.
  * Resolution: Made use of std::iostream header in order to receive arguments from the shell when being executed, and return information on the use of the program when incorrect arguments are passed in.
* When implementing Dijkstra's algorithm, a priority queue is used in order to specify which vertex should be added to the new graph next:
  * Issue: A priority queue was initially established containing integer type data in order to determine the priority of the each vertex, but the implementation lacked the ability to tie vertices back to their priorities.
  * Resolution: Implemented a std::pair where priority is the first element and vertex the second, allowing for the vertices to be retrieved in order of priority from the queue
* When implementing Dijkstra's algorithm, n items are removed from the priority queue in order to loop through all vertices (where n is the cardinality of the Vertex set):
  * Issue: Used a for loop to loop through inner code n times. This approach caused a segfault or double free due to the graph being disconnected.
  * Resolution: Looped through inner code until queue is empty, removing the possibility of a double free or segfault.
* A Makefile was used in order to script the building of our project and the fetching of datasets from OpenFlights:
  * Issue: Due to the multiple directory structure of our project and the distribution of modules, we had issues linking the project together after compilation
  * Resolution: Modified the compilation commands for current modules and created additional build steps for new modules, then linked them together at the end.
* The AirRender class requires a base Mercator projection png in order to plot the points in alignment with the map:
  * Issue: The resolution of most Mercator map projections was so low that when plotting all flights there was essentially no recognizable paths.
  * Resolution: The image was scaled up linearly 400% in order to increase the size of the image to allow for greater distance between individual routes plotted.

### Work Log

* Created a renderer for air traffic and airports that plots on a Mercator projection of the earth.
  * Includes functionality for displaying airports with varying radii in order to plot the importance of an airport according to the AirportRank algorithm.

* Wrote BFS traversal in addition to wrapper functions to allow for full traversal and path plotting.
* Wrote Dijkstra's Algorithm and implemented common interface mirroring BFS.
* Wrote multiple public facing interfaces to render the solutions from BFS, Dijkstra, and AirportRank modules.
* Created CLI to allow user to pass in program arguments.