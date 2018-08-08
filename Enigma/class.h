
#ifndef CLASS_H

#include <vector>

using namespace std;

const char alpha[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int FIXED_SIZE = 26;
const int MAX_SIZE = 512;

class Rotor{
private:
  int mappingForwards[26];
  int mappingBackwards[26];
  int top_position;
  vector<int> notch;

public:
  Rotor();
  int connect_contacts(const char* rt_file);
  void set_top_position(const int number);
  void rotate();
  char after_rotor_forwards(const char message_in) const;
  char after_rotor_backwards(const char message_in) const;
  bool get_notch();
};


class Plugboard{
private:
  char output_side[FIXED_SIZE];

public:
  Plugboard();
  int connect_contacts(const char* rf_file);
  char after_plugboard(const char message_in) const ;

};


class Reflector{
private:
  char output_side[FIXED_SIZE];

public:
  Reflector();
  int connect_contacts(const char* rf_file);
  char after_reflector(const char message_in) const;

};


class Input_switches{
 public:
  bool input_message(char information[]);
};


class Output_board{};


class Enigma{
private:
  Input_switches input;
  Output_board output;
  Plugboard plugb;
  Rotor** rots;
  Reflector *reflect;
  const int number_rotor;
  char information[MAX_SIZE];

public:
  Enigma(const int &number);
  ~Enigma();
  int startOn(char* file_name[]);
  int encryptOrDecrypt();
};


#define CLASS_H
#endif
