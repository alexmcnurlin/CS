// Name; Alex McNurlin
// Class: CS120
// hw: Homework 5
// Date: Mon Nov 23 10:04:21 PST 2015

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

struct Node {
  public:
    string value;
    Node *next;
    Node(const std::string& input_value){
      value = input_value;
      next = NULL;
    };
};

void add(const std::string&,Node*);
int is_number(const std::string&);
int is_special(const std::string&);
void print_ll(Node*);


int main() {
  ifstream somefile;
  string filename;
  cout << "Enter file name: ";
  cin >> filename;
  somefile.open(filename.c_str());
  if (somefile.fail()) {
    cout << somefile << " is not a valid file." << endl << "Exiting..." << endl;
    exit(0);
  }
  cout << "categorizing...  ";

  Node *spec_list,*num_list,*norm_list;
  spec_list = new Node("Special");
  norm_list = new Node("Normal");
  num_list = new Node("Numbers");

  string temp;
  while (somefile >> temp) {
    if (is_number(temp)) {
      add(temp, num_list);
    } else if (is_special(temp)) {
      add(temp, spec_list);
    } else {
      add(temp, norm_list);
    }
  }

  cout << "finished." << endl << endl;

  print_ll(spec_list);
  print_ll(norm_list);
  print_ll(num_list);

  
  return 0;
}



void add(const std::string& input_value,Node* ll) {
  Node *a;
  a = ll;
  while(a->next != NULL) {
    a = a->next;
  }
  a->next = new Node(input_value);
}

int is_number(const std::string& input) {
  for(int i=0; i<input.length(); i++){
    if (input[i]<48 || input[i]>57) {
      return 0;
    }
  }
  return 1;
}

int is_special(const std::string& input) {
  string spec_words[] = {"integer", "real", "accessor", "mutator", "function", "limited", "if", "loop", "delta", "range", "type", "abs", "constant", "else", "interface", "of", "select", "while", "array", "do", "is", "end", "procedure", "not", "to"};
  if(input.length()>256){
    return 0;
  }
  for(int i=0; i<25; i++){
    if(input.length() == spec_words[i].length()){
      for(int j=0; j<input.length(); j++){
        if (tolower(input[j]) != tolower(spec_words[i][j])){
          goto nextword;      // This is to break out of 2 nested loops;
        }
      }
      return 1;
    }
  nextword: NULL; 
  }
  return 0;
}

void print_ll(Node* ll){
  Node *a = ll;
  if(ll->value == "Numbers") {
    cout << "Numbers" << endl;
  } else if (ll->value == "Special") {
    cout << "Special Words" << endl;
  } else if (ll->value == "Normal") {
    cout << "Normal Words" << endl;
  }

  int count=0;
  while(a->next != NULL) {
    count++;
    a = a->next;
  }
  cout << count << endl;
  a = ll;
  while(a->next != NULL) {
    a = a->next;
    cout << a->value << " ";
  }
  cout << endl << endl;
}
