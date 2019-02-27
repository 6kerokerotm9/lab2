#include <iostream>
#include <iomanip>
#include <sstream>

struct proposition {
  bool value;
  std::string name;
};

void print(bool);
bool negation(bool);
bool conjunction(bool, bool);
bool disjunction(bool, bool);
bool exclusiveor(bool, bool);
bool implies(bool, bool);
bool biconditional(bool, bool);
void input(std::string[], std::string[], int);
void fill(proposition[], std::string);
void sort(std::string[], std::string[], std::string[], int);
bool impliesorder(std::string[], std::string[], int);
bool result(std::string[], std::string[], proposition[], int);
int numcheck(int*);
bool check(std::string);
std::string lowercase(std::string);

int main() {
  int psize = 4;
  int csize = 50; //size for second list 
  char condition = 'y'; //loop condition
  std::string name;
  proposition props[psize]; //list to hold the propositions in which the user chooses the amount
  std::string choices[csize]; //list that holds the the operations that the user chooses
  std::string sortedchoices[csize]; //sorted version of choices by order of operations
  while(condition == 'y' || condition == 'Y') {
    std::cout << "Hi, please enter your name: ";
    std::getline(std::cin, name);
    fill(props, name);
    input(choices, sortedchoices, csize);
    result(choices, sortedchoices, props, csize);
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

void input(std::string choices[], std::string sortedchoices[], int csize) { //function that takes user input 
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
  sort(choices, options, sortedchoices, size);
}

void sort(std::string choices[], std::string options[], std::string sortedchoices[], int size) { //function that sorts the array by the order of boolean operations
  std::string temp[size];
  int count = 0; //variable that keeps track of the temporary arrays index
  for(int i=1; i<6; i++) { //starts at one so program checks for conjunction first in the list of options
    for(int j=0; j<size; j++) {  
      if(choices[j] == options[i]) { //if the operation is found in the choices list
        if(j == 1 && count > 0) { //if the operation is found in the start of the list, uses count to check if the sorted list is empty
          sortedchoices[count] = choices[j];
          sortedchoices[count+1] = choices[j-1];
          count+=2;
        }
        else if(count == 0) { //if temp is empty then fill the array with the first group of operations
          sortedchoices[count] = choices[j-1];
          sortedchoices[count+1] = choices[j];
          sortedchoices[count+2] = choices[j+1];
          count+=3;
        }
        else { //if the operation is found but it is not the first operation or group of operations found
          sortedchoices[count] = choices[j];
          sortedchoices[count+1] = choices[j+1];
          count+=2;
        }  
      }
    }
  }
  /*for(int i=0; i<size; i++) {
    sortedchoices[i] = temp[i];
  }*/
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
    std::cout << "Please enter truth value " << propnames[i] << ": ";
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

bool result(std::string choices[], std::string sortedchoices[], proposition props[], int csize) {
  bool temp; //boolean value that holds the values of the operations as the program goes through the array
  proposition prop1; //three temporary variables that hold the two propositions and the operation between them
  proposition prop2;
  std::string operation; 
  for(int i=0; i<csize; i+=2) {
    if(sortedchoices[i] == "") {
      break;
    }
    else if(i == 0) {
      for(int j=0; j<4; j++) {
        if(props[j].name == "") {
          break;
        } 
        if(sortedchoices[i] == props[j].name) {
           prop1 = props[j]; 
           break;
        } 
        else if(sortedchoices[i] == ("~" + props[j].name)) {
           prop1 = props[j];
           prop1.value = negation(prop1.value); 
           break;
        } 
      }
    }
    else {
      prop1.value = temp;  
    }
    for(int k=0; k<4; k++) {
      if(props[k].name == "") {
        break;
      }
      if(sortedchoices[i+2] == props[k].name) {
         prop2 = props[k]; 
         break;
      } 
      else if(sortedchoices[i+2] == ("~" + props[k].name)) {
         prop2 = props[k];
         prop2.value = negation(prop2.value);  
         break;
      } 
    }
    operation = sortedchoices[i+1];
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
	  if(impliesorder(choices, sortedchoices, csize)) {
		temp = implies(prop2.value, prop1.value);
	  }
	  else{  
        temp = implies(prop1.value, prop2.value);
	  }
    }
    else if(operation == "<->") {
      temp = biconditional(prop1.value, prop2.value);
    }
  }  
  print(temp);
}

bool impliesorder(std::string choices[], std::string sortedchoices[], int csize) {
  int temp1 = 0; //temporary integer to hold the index of the implication found in the first array
  int temp2 = 0;
  for(int i; i<csize; i++) {
	if(choices[i].empty()) { //uses the string function to check if string is empty (first time trying it)
	  break;
    }
	else if(choices[i] == "->") {
	  temp1 = i;
	  break;
	}
  }
  for(int j; j<csize; j++) {
	if(sortedchoices[j].empty()) {
	  break;
    }
	else if(sortedchoices[j] == "->") {
	  temp2 = j;
	  break;
	}
	
  }
  if(temp2 > temp1) {
    return true;
  }	
  return false;
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
