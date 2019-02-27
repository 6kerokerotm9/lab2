#include <iostream>
#include <iomanip>
#include <sstream>

struct proposition {
  bool value;
  std::string name;
  std::string operation = " "; //connective for lists
};

void print(bool);
bool negation(bool);
bool conjunction(bool, bool);
bool disjunction(bool, bool);
bool exclusiveor(bool, bool);
bool implies(bool, bool);
bool biconditional(bool, bool);
int numcheck(int *);
std::string lowercase(std::string);
bool check(std::string temp);
void fill(proposition[], std::string[], std::string, int, int *);
void operate(proposition[], int, int);
bool booleanoperation(proposition, proposition, std::string);

int main() { //the main function
  int psize = 4;
  int csize = 50; //size for second list 
  int totalsize; //size of how many propositions are chosen by the user
  char condition = 'y'; //loop condition
  std::string name;
  proposition props[psize]; //list to hold the propositions in which the user chooses the amount
  std::string choices[csize]; //list that holds the the operations that the user chooses
  fill(props, choices, name, csize, &totalsize); 
  operate(props, csize, totalsize);
}

void print(bool value) { //used to print out the string values true and false from bool values
  if(value == true) {
    std::cout << "true" << std::endl; //changes the 1 and 0 boolean values to string values
  }
  if(value == false) {
    std::cout << "false" << std::endl;  
  } 
}

bool negation(bool value) { //basic negation function 
  if(value == true) {
    return false;
  }
  return true;
}

bool conjunction(bool value1, bool value2) { //conjunction function 
  if(value1 == true && value2 == true) { //only returns true when both propositions are true
    return true; //returns true and exits function 
  }
  return false; //any other combination will yield false
}

bool disjunction(bool value1, bool value2) { //disjunction
  if(value1 == true || value2 == true) { //if either proposition is true then return true
    return true;
  }
  return false; 
}

bool exclusiveor(bool value1, bool value2) { //xor function
  return value1 xor value2; //uses c++ operation xor and returns value
}

bool implies(bool value1, bool value2) {
  if(value1 == true && value2 == false) { //only false when true implies false so checks for that condition
    return false;
  }
  return true;
}

bool biconditional(bool value1, bool value2) {
  if(value1 == value2) { //the biconditional statement is only true if both values are the same so first check equality
    return true;
  }
  return false; //otherwise return false
}

int numcheck(int * amount) { //some data validation for integers
  while(true) { 
    std::cin.clear();
    if(*amount <= 0 || *amount > 4) {
      std::cout << "Invalid amount, please reenter: ";
      std::cin >> *amount;
    }
    else {
      break;
    }
  } 
}

std::string lowercase(std::string temp) {
  for(int i=0; i<temp.size(); i++) {
    temp[i] = tolower(temp[i]);
  }
  return temp;
}

bool check(std::string temp) { //data validation as well as turning the user input into boolean values
  temp = lowercase(temp);
  while(true) { 
    if(temp == "true") {
      return true;
    }
    else if(temp == "false") {
      return false;
    }
    else { 
      std::cout << "Please reenter a value: "; 
      std::getline(std::cin, temp);
    }
  }
}

void fill(proposition props[], std::string choices[], std::string name, int csize, int * totalsize) {
  std::string temp; 
  std::string temp2;
  int size; //temp int that helps fill the array
  int counter = 0; //counter that helps fill the props array
  std::string options [] = {"~", "^", "v", "xor", "->", "<->"}; //list of operations that will be used to compare later
  std::string propnames[] = {"p", "q", "r", "s"};
  std::cin.clear();
  std::cout << "Hi, " << name << "! How many propositions would you like to include (Max 4): ";
  std::cin >> size;
  numcheck(&size);
  std::cin.ignore();
  for(int i=0; i<size; i++) {
    std::cout << "Please enter truth value " << propnames[i] << ": ";
    std::getline(std::cin, temp);
    props[i].value = check(temp);
    props[i].name = propnames[i]; 
  }
  *totalsize = size;
  std::cout << "Which propositions would you like to include (Use ~, ^, v, xor, ->, <-> with spaces in between the propositions and operations): ";
  std::getline(std::cin, temp2); //gets the entire user input and stores it in a string
  std::istringstream iss(temp2); //then formats the string for use
  while(iss >> choices[counter]) {
    if(size == csize) {
      break;
    }
    counter++;
  }
  counter = 0; //reset size to use for the second half of the function
  for(int i=0; i<size; i++) {
    if((props[i].name)[0] == '~') {
      props[i].value = negation(props[i].value);
    }
  }
  for(int i=1; i<csize; i+=2) {
    if(choices[i].empty()) {
      break;
    }
    props[counter].operation = choices[i];
    counter++;
  }
} 

void operate(proposition props[], int csize, int totalsize) {
  proposition temp[csize]; //temporary array used to hold the merged propositions after operation
  proposition tempmerge; //temporary proposition created to help hold the merged propositions after operation
  std::string options [] = {"~", "^", "v", "xor", "->", "<->"}; 
  for(int i=1; i<6; i++) { //cycles through the options list to determine order of operation
    for(int j=0; j<totalsize; j++) {
      if(props[j].operation == options[i]) {
          tempmerge.name = props[j].name + props[j+1].name;
          tempmerge.value = booleanoperation(props[j], props[j+1], options[i]);
          tempmerge.operation = props[j+1].operation;
          temp[j] = tempmerge;
      }
    }
  }
}

bool booleanoperation(proposition prop1, proposition prop2, std::string operation) {
  bool temp;
  if(operation == "^") {
    temp = conjunction(prop1.value, prop2.value);
  }
  else if(operation == "v") {
    temp = disjunction(prop1.value, prop2.value);
  }
  else if(operation == "xor") {
    temp = exclusiveor(prop1.value, prop2.value);
  }
  else if(operation == "->") {
    temp = implies(prop1.value, prop2.value);
  }
  else if(operation == "<->") {
    temp = biconditional(prop1.value, prop2.value);
  }
  return temp;
}

/*

for(int i=0; i<csize; i++) {  
    if(choices[i].empty()) {
      break;
    }
    std::cout << choices[i] << std::endl;
  }

print {tempmerge.name, tempmerge.value, tempmerge.operation}

p ^ q -> r xor s

for(int i=0; i<4; i++) {  
    std::cout << props[i].operation << std::endl;
  }

std::cout << totalsize << std::endl;
*/
