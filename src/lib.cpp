#include <vector>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "pack109.hpp"
using namespace std;

// ----------------------------------------
// PACK109_TRUE and PACK109_FALSE
// ----------------------------------------

vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE);
  } else {
    bytes.push_back(PACK109_FALSE);
  }
  return bytes;
}

bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) {
     throw;
  }

  if (bytes[0] == PACK109_TRUE) {
    return true;
  } else if (bytes[0] == PACK109_FALSE) {
    return false;
  } else {
    throw;
  }

}

// ----------------------------------------
// PACK109_U8
// ----------------------------------------

vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8); //push tag
  bytes.push_back(item); //push byte
  return bytes;
}

u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) { // need two bytes for u8 -- one for tag and one for the byte
    throw;
  }
  if (bytes[0] == PACK109_U8) { // check for correct tag
    return bytes[1];
  } else {
    throw;
  }
}

// ----------------------------------------
// PACK109_U32
// ----------------------------------------

vec pack109::serialize(u32 item){
  vec bytes;
  u32 temp;
  u32 temp2;
  bytes.push_back(PACK109_U32);
  for(int i = 6; i >= 0; i-=2){
    //shift in byte size intervals, starting from the beggining of number
    temp = item >> 4 * i;
    temp2 = temp & 0x000000FF;
    //push casted byte to the back of the vector
    bytes.push_back((u8)temp2);
  }
  return bytes;
}

u32 pack109::deserialize_u32(vec bytes){
  if(bytes.size() != 5){ // need tag and then 4 bytes
    throw;
  }
  u32 item = 0x00000000; // container for result
  if(bytes[0] == PACK109_U32){ // check for correct tag
    for(int i = 1; i < 5; i++){ //take byte at a time and shift into correct position
      item = item | (u32)bytes[i] << (6+2*(1-i))*4;
    }
    return item;
  }
}

// ----------------------------------------
// PACK109_U64
// ----------------------------------------
//these functions are almost the same as the u32, but just has some adjustments for the sizing
vec pack109::serialize(u64 item){
  vec bytes;
  u64 temp;
  u64 temp2;
  bytes.push_back(PACK109_U64);
  for(int i = 14; i >= 0; i-=2){
    temp = item >> 4 * i;
    temp2 = temp & 0x00000000000000FF;
    bytes.push_back((u8)temp2);
  }
  return bytes;
}
u64 pack109::deserialize_u64(vec bytes){
  if(bytes.size() != 9){
    throw;
  }
  u64 item = 0x0000000000000000;
  if(bytes[0] == PACK109_U64){
    for(int i = 1; i < 9; i++){
      item = item | (u64)bytes[i] << (14+2*(1-i))*4;
    }
    return item;
  }
}

// ----------------------------------------
// PACK109_I8
// ----------------------------------------

vec pack109::serialize(i8 item){
  vec bytes;
  bytes.push_back(PACK109_I8);
  bytes.push_back((u8)item);
  return bytes;
}
i8 pack109::deserialize_i8(vec bytes){
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_I8) {
    return (i8)bytes[1];
  } else {
    throw;
  }
}

// ----------------------------------------
// PACK109_I32
// ----------------------------------------

vec pack109::serialize(i32 item){
  vec bytes;
  i32 temp;
  i32 temp2;
  bytes.push_back(PACK109_I32);
  //printf("item is %x\n",item);
  for(int i = 6; i >= 0; i-=2){
    temp = item >> 4 * i;
    //printf("temp for int %d is: %x\n",i,temp);
    temp2 = temp & 0x000000FF;
    //printf("temp2 for int %d is: %x\n",i,temp2);
    bytes.push_back((u8)temp2);
  }
  return bytes;
}
i32 pack109::deserialize_i32(vec bytes){
  if(bytes.size() != 5){
    throw;
  }
  i32 item = 0x00000000;
  if(bytes[0] == PACK109_I32){
    for(int i = 1; i < 5; i++){
      item = item | (i32)bytes[i] << (6+2*(1-i))*4;
    }
    return item;
  }
}

// ----------------------------------------
// PACK109_I64
// ----------------------------------------

vec pack109::serialize(i64 item){
  vec bytes;
  i64 temp;
  i64 temp2;
  bytes.push_back(PACK109_I64);
  for(int i = 14; i >= 0; i-=2){
    temp = item >> 4 * i;
    temp2 = temp & 0x00000000000000FF;
    bytes.push_back((u8)temp2);
  }
  return bytes;
}
i64 pack109::deserialize_i64(vec bytes){
  if(bytes.size() != 9){
    throw;
  }
  i64 item = 0x0000000000000000;
  if(bytes[0] == PACK109_I64){
    for(int i = 1; i < 9; i++){
      item = item | (i64)bytes[i] << (14+2*(1-i))*4;
    }
    return item;
  }
}

// ----------------------------------------
// PACK109_F32
// ----------------------------------------

vec pack109::serialize(f32 item){
  
  vec bytes;
  //printf("item is:%d\n",item);
  u32 val = *(u32*)&item;
  // *(u32*)(&item)
  //printf("val is: %d\n",val);
  u32 temp;
  u32 temp2;
  //printf("item is %x\n",val);
  bytes.push_back(PACK109_F32);
  for(int i = 6; i >= 0; i-=2){
    temp = val >> 4 * i;
    //printf("temp for int %d is: %x\n",i,temp);
    temp2 = temp & 0x000000FF;
    //printf("temp2 for int %d is: %x\n",i,temp2);
    bytes.push_back(temp2);
  }
  return bytes;
}
f32 pack109::deserialize_f32(vec bytes){
  if(bytes.size() != 5){
    throw;
  }
  u32 item = 0x00000000;
  if(bytes[0] == PACK109_F32){
    int j = 6;
    for(int i = 1; i < 5; i++){
      item = item | (u32)bytes[i] << j*4;
      //printf("bytes[%d] is %x\n",i,bytes[i]);
      //printf("tem is now %x\n",item);
      j-=2;
    }
  }
  return *(f32*)&item;
}

// ----------------------------------------
// PACK109_F64
// ----------------------------------------

vec pack109::serialize(f64 item){
  vec bytes;
  u64 val = *(u64*)&item;
  u64 temp;
  u64 temp2;
  bytes.push_back(PACK109_F64);
  for(int i = 14; i >= 0; i-=2){
    temp = val >> 4 * i;
    temp2 = temp & 0x00000000000000FF;
    bytes.push_back(temp2);
  }
  return bytes;
}
f64 pack109::deserialize_f64(vec bytes){
  if(bytes.size() != 9){
    throw;
  }
  u64 item = 0x0000000000000000;
  if(bytes[0] == PACK109_F64){
    int j = 14;
    for(int i = 1; i < 9; i++){
      item = item | (u64)bytes[i] << j*4;
      //printf("bytes[%d] is %lx\n",i,bytes[i]);
      //printf("tem is now %lx\n",item);
      j-=2;
    }
  }
  return *(f64*)&item;
}

// ----------------------------------------
// PACK109_S8 and PACK109_S16
// ----------------------------------------
vec pack109::serialize(string item){
  vec bytes;
  if(item.size() <= 255){ //can handle S8 and S16 in same function so we just check the size
    bytes.push_back(PACK109_S8); //push tag
    u8 stringSize = item.size();
    bytes.push_back((u8)stringSize); //push size of string
  }
  else if(item.size() < 65536){
    bytes.push_back(PACK109_S16); //push tag
    u32 size = item.size();
    //split size of string into two bytes and push the two
    bytes.push_back((u8)size >> 8 & 0x000000FF);
    bytes.push_back((u8)size & 0x000000FF);
  }
  else{
    throw;
  }
  for(int i = 0; i < item.size() ; i++){
    bytes.push_back(item[i]); //push each byte of string into vector
  }
  return bytes;
}
string pack109::deserialize_string(vec bytes){
  int i;
  int size;
  if(bytes[0] == PACK109_S8){ //check size since we handle S8 and S16 in the same function
    i = 2;
    size = bytes[1];
  }
  else if(bytes[0] == PACK109_S16){
    i = 3;
    size = 0x00000000;
    for(int z = 1; z < 3; z++){ //put string size back together from two bytes in the vector
      size = size | bytes[z] << (2-z)*8;
    }
  }
  else{
    throw;
  }
  string returnVal = "";
  int f = i;
  for(i; i < size+f; i++){ //loop through and reconstruct the string starting from the appropriate position
    //printf("bytes[%d] is %x\n",i,bytes[i]);
    returnVal.push_back(bytes[i]);
  }
  //std::cout << returnVal << "\n";
  return returnVal;
}

// ----------------------------------------
// PACK109_A8 and PACK109_A16
// ----------------------------------------

vec pack109::serialize(std::vector<u8> item){
  vec bytes;
  //check size and assign correct tag
  if(item.size() < 256){
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
  }
  else if(item.size() < 65536){
    bytes.push_back(PACK109_A16);
    u32 size = item.size();
    //split size into two bytes and push
    bytes.push_back((u8)size >> 8 & 0x000000FF);
    bytes.push_back((u8)size & 0x000000FF);
  }
  else{
    throw;
  }
  
  for(int i = 0; i < item.size(); i++){ //loop and push each byte since they're u8's
    bytes.push_back(PACK109_U8);
    bytes.push_back(item.at(i));
  }
  return bytes;
}
vec pack109::serialize(std::vector<u64> item){
  vec bytes;
  if(item.size() < 256){
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
  }
  else if(item.size() < 65536){
    bytes.push_back(PACK109_A16);
    u32 size = item.size();
    //split size into two bytes and push
    bytes.push_back((u8)size >> 8 & 0x000000FF);
    bytes.push_back((u8)size & 0x000000FF);
  }
  else{
    throw;
  }
  u64 temp;
  u64 temp2;
  for(int i = 0; i < item.size(); i++){ //loop to push each u64 once serialized
    bytes.push_back(PACK109_U64);
    u64 temp3 = item.at(i);
    for(int j = 14; j >= 0; j-=2){ //for each u64, we must do the same serialization procedure
      temp = temp3 >> 4 * j;
      temp2 = temp & 0x00000000000000FF;
      bytes.push_back(temp2);
    }
  }
  return bytes;
}
vec pack109::serialize(std::vector<f64> item){
  vec bytes;
  if(item.size() < 256){
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
  }
  else if(item.size() < 65536){
    bytes.push_back(PACK109_A16);
    u32 size = item.size();
    bytes.push_back((u8)size >> 8 & 0x000000FF);
    bytes.push_back((u8)size & 0x000000FF);
  }
  else{
    throw;
  }
  u64 temp;
  u64 temp2;
  for(int j = 0; j < item.size(); j++){
    u64 val = (u64)item.at(j);
    bytes.push_back(PACK109_F64);
    for(int i = 14; i >= 0; i-=2){
      temp = val >> 4 * i;
      temp2 = temp & 0x00000000000000FF;
      bytes.push_back(temp2);
    }
  }
  return bytes;
}
vec pack109::serialize(std::vector<string> item){
  vec bytes;
  if(item.size() < 256){
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
  }
  else if(item.size() < 65536){
    bytes.push_back(PACK109_A16);
    u32 size = item.size();
    bytes.push_back((u8)size >> 8 & 0x000000FF);
    bytes.push_back((u8)size & 0x000000FF);
  }
  else{
    throw;
  }
  string temp;
  for(int j = 0; j < item.size(); j++){
    temp = item.at(j);
    if(temp.size() <= 255){
      bytes.push_back(PACK109_S8);
      bytes.push_back((u8)temp.size());
      //printf("temp size is:%d\n",temp.size());
      //printf("bytes[%d] is %d\n",j,bytes[j]);
    }
    else if(item.size() < 65536){
      bytes.push_back(PACK109_S16);
      u32 size = temp.size();
      bytes.push_back((u8)size >> 8 & 0x000000FF);
      bytes.push_back((u8)size & 0x000000FF);
    }
    else{
      throw;
    }
    //printf("entering string push loop\n");
    for(int i = 0; i < temp.size() ; i++){
      bytes.push_back(temp[i]);
    }
  }

  return bytes;
}

std::vector<u8> pack109::deserialize_vec_u8(vec bytes){
  int i;
  int size;
  if(bytes[0] == PACK109_A8){
    i = 2;
    size = bytes[1];
  }
  else if(bytes[0] == PACK109_A16){
    i = 3;
    size = 0x00000000;
    int j = 2;
    for(int z = 1; z < 3; z++){
      size = size | bytes[z] << j*4;
      j-=2;
    }
  }
  else{
    throw;
  }
  std::vector<u8> returnVal;
  i++;
  int f = i;
  for(i; i < 2*size+f; i += 2){
    returnVal.push_back(bytes[i]);
  }
  return returnVal;
}
std::vector<u64> pack109::deserialize_vec_u64(vec bytes){
  int i;
  int size;
  if(bytes[0] == PACK109_A8){
    i = 2;
    size = bytes[1];
  }
  else if(bytes[0] == PACK109_A16){
    i = 3;
    size = 0x00000000;
    int j = 2;
    for(int z = 1; z < 3; z++){
      size = size | bytes[z] << j*4;
      j-=2;
    }
  }
  else{
    throw;
  }
  std::vector<u64> returnVal;
  int f = i;
  u64 temp = 0x0000000000000000;
  int z = 14;
  for(i; i < 8*size+f+size; i++){
    if(bytes[i] != PACK109_U64){
      temp = temp | (u64)bytes[i] << z*4;
      //printf("(u64)bytes[i] << z*4 for i=%d z=%d is %lx\n",i,z,(u64)bytes[i] << z*4);
      z-=2;
    }
    else if(bytes[i] == PACK109_U64 && i>3){
      returnVal.push_back(temp);
      temp = 0x0000000000000000;
      z = 14;
    }
  }
  returnVal.push_back(temp);
  return returnVal;
}
std::vector<f64> pack109::deserialize_vec_f64(vec bytes){
  int i;
  int size;
  if(bytes[0] == PACK109_A8){
    i = 2;
    size = bytes[1];
  }
  else if(bytes[0] == PACK109_A16){
    i = 3;
    size = 0x00000000;
    int j = 2;
    for(int z = 1; z < 3; z++){
      size = size | bytes[z] << j*4;
      j-=2;
    }
  }
  else{
    throw;
  }
  std::vector<f64> returnVal;
  u64 temp = 0x0000000000000000;
  int z = 14;
  int f = i;
  for(i; i < 8*size+f+size; i++){
    if(bytes[i] != PACK109_F64){
      temp = temp | (u64)bytes[i] << z*4;
      z-=2;
    }
    else if(bytes[i] == PACK109_F64 && i>2){
      returnVal.push_back(f64(temp));
      temp = 0x0000000000000000;
      z = 14;
    }
  }
  returnVal.push_back(temp);
  return returnVal;
}
std::vector<string> pack109::deserialize_vec_string(vec bytes){
  int i;
  int size;
  if(bytes[0] == PACK109_A8){
    i = 2;
    size = bytes[1];
  }
  else if(bytes[0] == PACK109_A16){
    i = 3;
    size = 0x00000000;
    int j = 2;
    for(int z = 1; z < 3; z++){
      size = size | bytes[z] << j*4;
      j-=2;
    }
  }
  else{
    throw;
  }
  std::vector<string> returnVal;
  int f = i;
  string temp;
  while(i < bytes.size()){
    if(bytes[i] == PACK109_S8 || bytes[i] == PACK109_S16){
      if(i > 3){
        returnVal.push_back(temp);
        temp.clear();
      }
    }
    else{
      //printf("bytes[%d] is %c\n",i,bytes[i]);
      temp.push_back(bytes[i]);
    }
    i++;
  }
  returnVal.push_back(temp);
  return returnVal;
}

void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}

void pack109::printVectoru64(std::vector<u64> &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%lx ", bytes[i]);
  }
  printf("]\n");
}

void pack109::printVectorf64(std::vector<f64> &bytes){
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%lf ", bytes[i]);
  }
  printf("]\n");
}

void pack109::printVectorString(std::vector<string> &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%s ", bytes[i].c_str());
  }
  printf("]\n");
}

void pack109::printPerson(Person &person){
  printf("Person name:%s Person age:%d Person height:%f\n",person.name.c_str(),person.age,person.height);
}