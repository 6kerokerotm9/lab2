#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

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
  while(condition == 'y' || condition == 'Y') {
    std::cout << "Hi, please enter your name: ";
    std::getline(std::cin, name);
    proposition props[psize]; //list to hold the propositions in which the user chooses the amount
    std::string choices[csize]; //list that holds the the operations that the user chooses
    fill(props, choices, name, csize, &totalsize); 
    operate(props, csize, totalsize);
    std::cout << "Would you like to try again(y for yes, anything else for no): ";
    std::cin >> condition;
    std::cin.ignore();
  }
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
  proposition propstemp[4]; //temporary array that holds the made propositions
  int size; //temp int that helps fill the array
  int counter = 0; //counter that helps fill the props array
  int counter2 = 0;
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
    propstemp[i].value = check(temp);
    propstemp[i].name = propnames[i]; 
  }
  std::cout << "Which propositions would you like to include (Use ~, ^, v, xor, ->, <-> with spaces in between the propositions and operations): ";
  std::getline(std::cin, temp2); //gets the entire user input and stores it in a string
  std::istringstream iss(temp2); //then formats the string for use
  while(iss >> choices[counter]) {
    if(size == csize) {
      break;
    }
    counter++;
  }
  for(int i=0; i<counter; i+=2) { //for every other value in the choices array
    for(int j=0; j<size; j++) {
      if(propstemp[j].name == choices[i]) {
        props[counter2] = propstemp[j]; //copy the struct from propstemp array 
        props[counter2].operation = choices[i+1]; //set the operation to the next element of choices
        counter2++;
      }
      else if(("~" + propstemp[j].name) == (choices[i])) {
        props[counter2] = propstemp[j];
        props[counter2].value = negation(props[counter].value);
        props[counter2].operation = choices[j+1];
        counter2++;
      }
    }
  }
  *totalsize = counter2;
} 

void operate(proposition props[], int csize, int totalsize) {
  std::vector<proposition> temp; //temporary array used to hold the merged propositions after operation
  for(int i=0; i<totalsize; i++) {
    temp.push_back(props[i]);
  }
  proposition tempmerge; //temporary proposition created to help hold the merged propositions after operation
  std::string options [] = {"~", "^", "v", "xor", "->", "<->"}; 
  for(int i=1; i<6; i++) { //cycles through the options list to determine order of operation
    if(temp[0].operation == "") {
      break;
    }
    for(int j=0; j<temp.size(); j++) {
      if(temp[j].operation == options[i]) {
          tempmerge.name = temp[j].name + temp[j+1].name;
          tempmerge.value = booleanoperation(temp[j], temp[j+1], options[i]);
          tempmerge.operation = temp[j+1].operation;
          temp[j] = tempmerge;
          temp.erase(temp.begin()+(j+1));
      }
    }
  }  
  std::cout << temp[0].name << temp[0].value << temp[0].operation << std::endl;
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
