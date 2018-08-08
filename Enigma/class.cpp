#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "errors.h"
#include "class.h"

using namespace std;


Rotor::Rotor(){
  for(int i=0;i<FIXED_SIZE; i++){
    mappingForwards[i] = i;
    mappingBackwards[i] = i;  } }

int Rotor:: connect_contacts(const char* rt_file){
  int count = 0, number = 0, tag[FIXED_SIZE];
  for(int i=0; i< FIXED_SIZE; i++)
    tag[i] = 0;

  ifstream input;
  input.open(rt_file);
  if(input.fail()){
    cerr<<"ERROR OPENING CONFIGURATION FILE"<<endl;
    return ERROR_OPENING_CONFIGURATION_FILE;  }

  while(!input.eof()){

    if(input >> number){

    if (number < 0 || number > 25){
      input.close();
      cerr<<"INVALID INDEX"<<endl;
      return INVALID_INDEX;  }

    if (count< FIXED_SIZE && tag[number] == 1){
      input.close();
      int i = 0;
      for (; i < FIXED_SIZE; i++){
        if(mappingForwards[i] == number)
        break;  }
      cerr<<"Invalid mapping of input "<< count <<" to output "<< number <<" (output "<< number <<" is already mapped to from input "<< i <<")"<<endl;
      return INVALID_ROTOR_MAPPING; }

       if(count < FIXED_SIZE)
      mappingForwards[count] = number;
      else {
        int new_notch = number;
        notch.push_back(new_notch);  }

    count++;
    tag[number] = 1;   }

    else  if(!input.eof()){
    cerr<<"Non-numeric character for mapping in rotor file "<<rt_file<<endl;
    return NON_NUMERIC_CHARACTER;   }
    else break;  }

  if (count < (FIXED_SIZE+1)){
    input.close();
    cerr<<"Not all inputs mapped in rotor file: "<<rt_file<<endl;
    return INVALID_ROTOR_MAPPING; }

  for(int i = 0; i < FIXED_SIZE; i++)
  mappingBackwards[mappingForwards[i]] = i;
  return NO_ERROR;  }


void Rotor:: set_top_position(const int number){
  top_position = number;  }

void Rotor:: rotate(){
  top_position++;
  top_position = top_position %(FIXED_SIZE);  }

char Rotor:: after_rotor_forwards(const char message_in) const{
  int track;
  track = static_cast<int>(message_in - 'A');
  track = (track + top_position) % (FIXED_SIZE);
  track = mappingForwards[track];
  track = (track - top_position + FIXED_SIZE)% (FIXED_SIZE);
  return alpha[track];  }

char Rotor:: after_rotor_backwards(const char message_in) const{
  int track;
  track = static_cast<int>(message_in - 'A');
  track = (track + top_position) % (FIXED_SIZE);
  track = mappingBackwards[track];
  track = (track - top_position+ FIXED_SIZE)% (FIXED_SIZE);
  return alpha[track];  }

bool Rotor:: get_notch(){
  for (int i = 0; i < static_cast<int> (notch.size()); i++){
    if (top_position == notch[i])
      return true;  }
    return false; }


Plugboard:: Plugboard(){
  for(int i=0; i < FIXED_SIZE; i++)
    output_side[i] = alpha[i];  }

int Plugboard:: connect_contacts(const char* pb_file){
  int number_1 = 0, number_2 = 0, count = 0;
  int tag[FIXED_SIZE];
  for(int i=0; i< FIXED_SIZE; i++)
    tag[i] = 0;

  ifstream input;
  input.open(pb_file);

  if(input.fail()){
    cerr<<"ERROR OPENING CONFIGURATION FILE"<<endl;
    return ERROR_OPENING_CONFIGURATION_FILE;}

  while(!input.fail()){
    if(input >> number_1){
      if (number_1 < 0 || number_1 > 25){
        input.close();
	cerr<<"INVALID INDEX"<<endl;
	return INVALID_INDEX;  }

      count++;  }

    else{
      if(!input.eof()){
        cerr<<"Non-numeric character in plugboard file "<<pb_file<<endl;
        return NON_NUMERIC_CHARACTER; }
      else break; }

    if (input >> number_2){
      if (number_2 < 0 || number_2 > 25){
        input.close();
        cerr<<"INVALID INDEX"<<endl;
        return INVALID_INDEX; }

      count++;  }

   else if(!input.eof()){
     cerr<<"Non-numeric character in plugboard file "<<pb_file<<endl;
     return NON_NUMERIC_CHARACTER;  }
     else break;

     if (number_1 == number_2){
       input.close();
       cerr<<"IMPOSSIBLE PLUGBOARD CONFIGURATION"<<endl;
       return IMPOSSIBLE_PLUGBOARD_CONFIGURATION; }

    if (tag[number_1] ==1 || tag[number_2] == 1){
      input.close();
      cerr<<"IMPOSSIBLE PLUGBOARD CONFIGURATION"<<endl;
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;  }

    swap (output_side[number_1], output_side[number_2]);
    tag[number_1] = 1;
    tag[number_2] = 1;}

    if(count%2 != 0){
      input.close();
      cerr<<"Incorrect number of parameters in plugboard file "<<pb_file<<endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;  }

      return NO_ERROR;  }

char Plugboard:: after_plugboard(const char message_in) const {
  char message_out;
  int i=0;
  i = static_cast<int>(message_in-'A');
  message_out = output_side[i];
  return message_out; }


Reflector:: Reflector(){
  for(int i=0; i< FIXED_SIZE; i++)
    output_side[i] =alpha[i]; }

int Reflector:: connect_contacts(const char* rf_file){
  ifstream input;
  input.open(rf_file);
  if(input.fail()){
    cerr<<"ERROR OPENING CONFIGURATION FILE"<<endl;
  return ERROR_OPENING_CONFIGURATION_FILE;  }

  int number_1, number_2, count = 0;
  int tag[FIXED_SIZE];
  for(int i=0; i< FIXED_SIZE; i++)
    tag[i] = 0;

  while(!input.fail()){
    if(input >> number_1){
      if (number_1 < 0 || number_1 > 25){
        input.close();
        cerr<<"INVALID INDEX"<<endl;
        return INVALID_INDEX;}
      count++;  }

    else{
      if(!input.eof()){
    cerr<<"NON NUMERIC CHARACTER"<<endl;
    return NON_NUMERIC_CHARACTER;}
      else break; }

    if (input >> number_2){
      if (number_2 < 0 || number_2 > 25){
        input.close();
        cerr<<"INVALID INDEX"<<endl;
        return INVALID_INDEX;}
      count++;  }

    else if(!input.eof()){
      cerr<<"Non-numeric character in reflector file "<<rf_file<<endl;
      return NON_NUMERIC_CHARACTER; }
      else break;

    if (number_1 == number_2){
      input.close();
      cerr<<"INVALID REFLECTOR MAPPING"<<endl;
      return INVALID_REFLECTOR_MAPPING; }

    if (tag[number_1] ==1 || tag[number_2] == 1){
      input.close();
      cerr<<"INVALID REFLECTOR MAPPING"<<endl;
      return INVALID_REFLECTOR_MAPPING; }

    swap (output_side[number_1], output_side[number_2]);
    tag[number_1] = 1;
    tag[number_2] = 1;  }

    if(count != FIXED_SIZE){
      input.close();
      if(count % 2 == 0){
        cerr<<"Insufficient number of mappings in reflector file: "<<rf_file<<endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;  }
        else {
          cerr<<"Incorrect (odd) number of parameters in reflector file "<<rf_file<<endl;
          return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;  } }

    return NO_ERROR;  }

char Reflector:: after_reflector(const char message_in) const{
  char message_out;
  int i=0;
  i = static_cast<int>(message_in-'A');
  message_out = output_side[i];
  return message_out; }

bool Input_switches:: input_message(char information[]){
 if (cin.getline(information, MAX_SIZE))
  return true;
 else
  return false; }

Enigma:: Enigma(const int &num):number_rotor(max(num - 3, 0)){
  Input_switches newInput;
  Output_board newOutput;
  Plugboard newPlugb;
  input = newInput;
  output = newOutput;
  plugb = newPlugb;
  reflect = new Reflector();
  rots = new Rotor*[num];
    for(int i=0; i<num;i++)
      rots[i] = new Rotor();
      strcpy(information, "");  }

Enigma:: ~Enigma(){
  delete reflect;
  for(int i=0; i < number_rotor; i++)
    delete rots[i];  }

int Enigma:: startOn(char* file_name[]){
    int file_count = number_rotor + 3;
    int error = NO_ERROR;

    error = plugb.connect_contacts(file_name[0]);
    if(error != NO_ERROR)
      return error;

    error = reflect->connect_contacts(file_name[1]);
     if(error != NO_ERROR)
      return error;

     for(int i=0; i<number_rotor; i++){
     error = rots[i]->connect_contacts(file_name[2+i]);
      if(error != NO_ERROR)
      return error; }

     if (number_rotor != 0){
      ifstream in;
      int number;
      in.open(file_name[file_count-1]);
      if(in.fail()){
        cerr<<"ERROR OPENING CONFIGURATION FILE"<<endl;
        return ERROR_OPENING_CONFIGURATION_FILE;   }

      int i = 0;
      while(!in.eof()){
      if(in >> number){
        if (number < 0 || number > 25){
          in.close();
  	cerr<<"INVALID INDEX"<<endl;
  	return INVALID_INDEX;  }
    if (i < number_rotor){
      rots[i]->set_top_position(number);
      i++;  }   }

      else{
        if(!in.eof()){
      cerr<<"Non-numeric character in rotor positions file "<<file_name[file_count-1]<<endl;
      return NON_NUMERIC_CHARACTER;  }
        else break; } }
      if(i != number_rotor){
        cerr<<"No starting position for rotor "<< i <<" in rotor position file: "<<file_name[file_count-1]<<endl;
        return NO_ROTOR_STARTING_POSITION;  }
      in.close();  }

    return NO_ERROR;  }

int Enigma:: encryptOrDecrypt(){
  char message;

  while (input.input_message(information)){
    int count =0;
    while(count < static_cast<int> (strlen(information))){
      message = information[count];

      if(message >= 'A' && message <= 'Z'){
        message = plugb.after_plugboard(message);
       if (number_rotor != 0)
        rots[number_rotor-1]->rotate();
        for(int i=number_rotor-1; i>0; i--){
          if(rots[i]->get_notch()){
            rots[i-1]->rotate(); } }
         for(int i=number_rotor-1; i>= 0; i--){
          message = rots[i]->after_rotor_forwards(message);
        }
        message = reflect->after_reflector(message);
       for(int i=0; i< number_rotor; i++){
          message = rots[i]->after_rotor_backwards(message);
        }
        message = plugb.after_plugboard(message);
        cout << message;
        count++;   }

      else if (message == static_cast<char>(9) || message == static_cast<char>(10) || message == static_cast<char>(13)||message == static_cast<char>(32))
      continue;

      else {
        cerr << message << " is not a valid input character (input characters must be upper case letters A-Z)!"<< endl;
        return INVALID_INPUT_CHARACTER;     }   }  }

    return NO_ERROR;
}
