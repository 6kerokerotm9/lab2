#include <iostream>
#include <iomanip>
#include <sstream>

struct proposition {
  bool value;
  std::string name;
};

struct operations { //holds the type of operation and the propositions involved in the operation
  propositions prop1;
  std::string operation;
  poropositions prop2;

bool negation(bool);
bool conjunction(bool, bool);
bool disjunction(bool, bool);
bool exclusiveor(bool, bool);
bool implies(bool, bool);
bool biconditional(bool, bool);
void print(bool);
void input(std::string[], int);
void fill(proposition[], std::string);
bool check(std::string);
int numcheck(int*);
std::string lowercase(std::string);

int main() {
  int psize = 4;
  int csize = 50; //size for second list 
  std::string name;
  proposition props[psize]; //list to hold the propositions in which the user chooses the amount
  std::string choices[csize]; //list that holds the the operations that the user chooses
  std::cout << "Hi, please enter your name: ";
  std::getline(std::cin, name);
  fill(props, name);
  input(choices, csize);
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

void print(bool value) { //used to print out the string values true and false from bool values
  if(value == true) {
    std::cout << std::setw(20) << std::left << "true"; //changes the 1 and 0 boolean values to string values
  }
  if(value == false) {
    std::cout << std::setw(20) << std::left << "false";  
  }
}

void input(std::string choices[], int csize) { //function that takes user input 
  std::string temp; //temporary string to hold the user input
  std::string userinput;
  int size = 0; //counter that keeps track of how many operations the user has chosen
  std::string options [] = {"~", "^", "v", "xor", "->", "<->"}; //list of operations that will be used to compare later
  std::cout << "Which propositions would you like to include (Use ~, ^, v, xor, ->, <-> with spaces in between the propositions and operations): ";
  std::getline(std::cin, temp); //gets the entire user input and stores it in a string
  std::istringstream iss(temp); //then formats the string for use
  while(iss >> choices[size]) {
    if(size == csize) {
      break;
    }
    size++;
  }
}

void fill(proposition props[], std::string name) {
  std::string temp; 
  int size; //temp int that helps fill the array
  std::string propnames[] = {"p", "q", "r", "s"};
  std::cin.clear();
  std::cout << "Hi, " << name << "! How many propositions would you like to include (Max 4): ";
  std::cin >> size;
  numcheck(&size);
  std::cin.ignore();
  for(int i=0; i<size; i++) {
    std::cout << "Please enter truth value number " << i+1 << ": ";
    std::getline(std::cin, temp);
    props[i].value = check(temp);
    props[i].name = propnames[i]; 
  }
}

bool check(std::string temp) { //data validation as well as turning the user input into boolean values
  temp = lowercase(temp);
  bool flag = false; //condition for loop
  while(flag == false) { //felt wrong to return from function without completing loop so I impliment a flag that will fulfill the condition to exit the loop
    if(temp == "true") {
      flag = true;
      return true;
    }
    else if(temp == "false") {
      flag = true;
      return false;
    }
    else { 
      std::cout << "Please reenter a value: "; 
      std::getline(std::cin, temp);
    }
  }
}

int numcheck(int * amount) { //some data validation for integers
  bool flag = false;
  while(flag == false) { 
    std::cin.clear();
    if(*amount <= 0 || *amount > 4) {
      std::cout << "Invalid amount, please reenter: ";
      std::cin >> *amount;
    }
    else {
      flag = true;
    }
  } 

}

std::string lowercase(std::string temp) {
  for(int i=0; i<temp.size(); i++) {
    temp[i] = tolower(temp[i]);
  }
  return temp;
}
