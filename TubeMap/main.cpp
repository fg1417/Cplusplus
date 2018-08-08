#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

#include "tube.h"

int main() {

	/* This code illustrates the use of the pre-supplied helper functions and the
	 * functions that you are supposed to write. */

	cout << "============== Pre-supplied functions ==============" << endl << endl;

	char** map;
	int height, width;

	cout << "Loading tube map with load_map():";

	/* loads the map from the file "map.txt" and sets height and width */
	map = load_map("map.txt", height, width);
	assert(map);
	cout << " done (height = " << height << ", width = " << width
			 << ")." << endl << endl;
	cout << "Printing map with print_map():" << endl;

	/* prints the map with row and column numbers */
	print_map(map,height,width);
	cout << endl;

	cout << "====================== Question 1 ==================" << endl << endl;

	int r, c;
	bool success = get_symbol_position(map, height, width, 'T', r, c);
	cout << "The symbol 'T' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	success = get_symbol_position(map, height, width, '4', r, c);
	cout << "The symbol '4' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	success = get_symbol_position(map, height, width, 'z', r, c);
	cout << "The symbol 'z' is ";
	if(success) {
		cout << "found at (" << r << "," << c << ")";
	} else {
		cout << "not found.";
	}
	cout << endl << endl;

	cout << "====================== Question 2 ==================" << endl << endl;

	cout << "The symbol for Victoria station is '" <<
		get_symbol_for_station_or_line("Victoria") << "'" << endl << endl;

	cout << "The symbol for Oxford Circus station is '" <<
		get_symbol_for_station_or_line("Oxford Circus") << "'" << endl << endl;

	cout << "The symbol for the District Line is '" <<
		get_symbol_for_station_or_line("District Line") << "'" << endl << endl;

	/* Birmingham station is not on the Tube map, so this should return ' ' */
	cout << "The symbol for Birmingham station is '" <<
		get_symbol_for_station_or_line("Birmingham") << "'" << endl << endl;

	cout << "====================== Question 3 ==================" << endl << endl;

	char route[512];
	char destination[512] = "nowhere";

	/* valid route to Leicester Square with 1 train change */
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	int result = validate_route(
			map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" train change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because of backtracking between stations */
	strcpy(route, "W,W,E,W,W,W");
	cout << "Starting at Sloane Square and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(
			map, height, width, "Sloane Square", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result
			<< " train change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because route goes outside of map bounds */
	strcpy(route, "E,NE,SE,SE,SE");
	cout << "Starting at Marylebone and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Marylebone", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" train change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* Add more of your own tests here. */
	/* valid route to Holborn with 3 train changes.*/
	strcpy(route, "S,S,S,S,N,N,N,N,S,S,S,S,E,E,NE,NE,NE,NE");
	cout << "Starting at Tottenham Court Road and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Tottenham Court Road", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" train change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because the endpoint of the route is not a sation.*/
	strcpy(route, "E,E,E");
	cout << "Starting at Queensway and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Queensway", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" train change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because direction is invalid.*/
	strcpy(route, "N,N,N,N,N,RE,N,NE");
	cout << "Starting at Bank and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Bank", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" train change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/* invalid route because lines change doesn't take place at station.*/
	strcpy(route, "E,E,S,E,SE,E,E,SE,E,E,SE");
	cout << "Starting at Piccadilly Circus and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Piccadilly Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" train change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	return 0;
}
