
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char** allocate_2D_array(int rows, int columns) {
  char** m = new char* [rows];
  assert(m);
  for(int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char** m, int rows) {
  for(int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char* filename, int& height, int& width) {
  char line[512];

  ifstream input(filename);

  height = width = 0;

  input.getline(line, 512);
  while(input) {
    if( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line, 512);
  }

  if(height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width) {

  bool success = get_map_dimensions(filename, height, width);

  if(!success) return NULL;

  char** m = allocate_2D_array(height, width);

  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for(int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while( (int) strlen(m[r]) < width ) {
      strcat(m[r], space);
    }
  }

  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char** m, int height, int width) {
  cout << setw(2) << " " << " ";
  for(int c=0; c<width; c++) {
    if(c && (c % 10) == 0) {
      cout << c/10;
    } else {
      cout << " ";
    }
  }

  cout << endl;
  cout << setw(2) << " " << " ";

  for(int c=0; c<width; c++) cout << (c % 10);

  cout << endl;

  for(int r=0; r<height; r++) {
    cout << setw(2) << r << " ";
    for(int c=0; c<width; c++) cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char* error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID:
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char* token) {
  const char* strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for(int n=0; n<8; n++) {
    if(!strcmp(token, strings[n])) return (Direction) n;
  }
  return INVALID_DIRECTION;
}


/*THE FUNCTION IS FOR QUESTION 1 */
/*find the coordinates (r,c) of the first occurrence  of that symbol on an ASCII map.*/
bool get_symbol_position(char** map, const int& height, const int& width, const char &target, int& r, int& c){
  
  for (r = 0; r < height; r++){
    for (c = 0; c < width; c++){
      if (map[r][c] == target)
	return true;
    }
  }
  
  r = -1;
  c = -1;
  
  return false;
}
/*THE END OF THE FUNCTION. */


/*THE FUNCTION IS FOR QUESTION 2. */
/*returns the corresponding map symbol character.*/
char get_symbol_for_station_or_line(char name[]){
  char symbol, fullname[MAX_NUMBER];
  
  ifstream input1, input2;
  
  input1.open("stations.txt");
  if (input1.fail()){
    cout << "Sorry, the file couldn't be opened!\n";
    exit(1);
  }
  
  input1 >> symbol;
  while (input1.getline(fullname, MAX_NUMBER)){
    if (!strcmp(&fullname[1], name)){
      input1.close();
      return symbol;
    }
    else 
      input1 >> symbol;
  }
  input1.close();
  
  input2.open("lines.txt");
   if (input2.fail()){
    cout << "Sorry, the file couldn't be opened!\n";
    exit(1);
  }
   
  input2 >> symbol;
  while (input2.getline(fullname, MAX_NUMBER)){
    if (!strcmp(&fullname[1], name)){
      input2.close();
      return symbol;
    }
    else
      input2 >> symbol;
  }
  input2.close();
  
  return ' ';
}
/*THE END OF THE FUCNTION.*/

/*helper function to return the corresponding name of the line and station.*/
void  get_fullname_for_symbol (char position, char destination[]){
  char symbol, fullname[MAX_NUMBER];
  
  ifstream input;
  
  input.open("stations.txt");
  if (input.fail()){
    cout << "Sorry, the file couldn't be opened!\n";
    exit(1);
  }
  
  input >> symbol;
  while (input.getline(fullname, MAX_NUMBER)){
    if (position == symbol){
      strcpy(destination, &fullname[1]);
      break ;
    }
    else 
      input >> symbol;
  }
  input.close();
  
  return ;
  }
/*THE END OF THE FUNCTION.*/

/*helper function to return the position after next step.*/
void next_step (char step[], int& r, int& c){
  
  switch (string_to_direction(step)){
    case N : r--; break;
    case S : r++; break;      
    case W : c--; break;      
    case E : c++; break;      
    case NE : { r--; c++; break;}      
    case NW : { r--; c--; break;}      
    case SE : { r++; c++; break;}      
    case SW: { r++; c--; break;}
  default : break;
    }
  
}
 /*THE END OF THE FUNCTION.*/

  
/*helper function to determine if the char string is a legal route.*/
bool get_route (char route[]){
   char step[3];
   int i;
   
   if (!strchr(route, ',')){
      strcpy(step, route);
      switch (string_to_direction(step)){
    case N :      
    case S :       
    case W :       
    case E :       
    case NE : 
    case NW :       
    case SE : 
    case SW: return true;
    default:  return false;
    }
   }
   
   else{
      i = strchr(route, ',') - route;
      strncpy(step, route,i );
      step[i]='\0';
    switch (string_to_direction(step)){
    case N :      
    case S :       
    case W :       
    case E :       
    case NE : 
    case NW :       
    case SE : 
    case SW:  return get_route(&route[i+1]);
    default:  return false;
    }
   }
   
}
/*THE END OF THE FUNCTION. */

 
/*THE FUNCTION IS FOR QUESTION 3. */
  /* determines if the route is valid according to the some rules.*/
int validate_route(char** map, int& height, int& width,
		   char start_station[], char route[], char destination[]){
  int i=0, j=0, r = 0, c = 0, r1 = 0, c1 = 0, r2 = 0, c2 = 0,
    count_step = 0,  train_changes = 0, length = strlen(route);
  
  char step[3], character;
  
  character = get_symbol_for_station_or_line(start_station);
  
  if (!isalnum(character))
    return ERROR_START_STATION_INVALID;

  if (!get_symbol_position(map, height, width, character, r, c))
    return ERROR_START_STATION_INVALID;
  
  if (!get_route(route))
    return ERROR_INVALID_DIRECTION;
  
  r2 = r1 = r; // use (r1, c1) to record the last position, and (r2, c2) to record the position two steps ago.
  c2 = c1 = c;
  
  while (i < length){
    
    while( route[i] != ','&& route[i]!='\0'){
      step[j] = route[i];
      i++;
      j++;
    }
    
    step[j]='\0';
    next_step (step, r, c);
    if (r >= height || r < 0 || c < 0 || c >= width)
      return ERROR_OUT_OF_BOUNDS;
    
    character = map[r][c];  
    if (character == ' ')
      return ERROR_OFF_TRACK;
    
    count_step++;
    if (map[r1][c1] != map[r][c] && !isalnum (map[r1][c1]) && !isalnum (map[r][c]))
	return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
    
    if (count_step >= 2){
      
      if (r2==r && c2==c && !isalnum (map[r1][c1]))
	return ERROR_BACKTRACKING_BETWEEN_STATIONS;

      if (r2==r && c2==c && isalnum (map[r1][c1]))
	train_changes ++;
      
      if (map[r2][c2] != map[r][c] && !isalnum(map[r2][c2]) && !isalnum(map[r][c])){
	    if  (isalnum (map[r1][c1]))
	      train_changes ++;
	    else return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
	  }
    }
    
    i++;
    j = 0;
    strcpy(step, "\0");
    r2 = r1; c2 = c1;
    r1 = r; c1 = c;
  }
      
  character = map[r][c];
  
  if (!isalnum(character))
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
  
  get_fullname_for_symbol (character, destination);
  
  return train_changes;
}
/*THE END OF THE FUNCTION.*/
