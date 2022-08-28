#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "pack109.hpp"

using namespace std;
  int main() {
    struct Person myPerson = {.age = 10, .height = 3.4, .name = "Ann"};
    std::vector<u8> v8person = pack109::serialize(myPerson);
    ofstream myfile;
    myfile.open("person.pack109", ios::out | ios::app | ios::binary);
    char* temp1;
    for(int i = 0; i < v8person.size(); i++){
      myfile.write((char*)&v8person[i],v8person.size()*sizeof(u8));
    }
    vec readVector;
    char* temp;
    myfile.close();
    std::ifstream myfile1("person.pack109", std::ios::binary);
    //myfile1.read(temp, v8person.size()*sizeof(u8));
    //struct Person finalPerson = pack109::deserialize_person(temp);

    printf("Original person: age:%d height:%f name:%s\n",myPerson.age,myPerson.height,myPerson.name.c_str());
  return 0;
}
