// SafeBuffer.cpp --- 
// 
// Filename: SafeBuffer.cpp
// Description: 
// Author: James Hall
// Created: Tue Nov 26 2020 
// Version: 
// Package-Requires: ()
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:
#include "SafeBuffer.h"
#include <iostream>


int Buffer::size(){
    return count;
}
bool Buffer::isEmpty(){
    return (size() == 0);
}
bool Buffer::isFull(){
    return (size() == capacity);
}
void Buffer::enqueue(int value){
    if (isFull()){
        exit(0);
    }
    back = (back+1)%capacity;
    arr[back] = value;
    count++;
}
void Buffer::dequeue(){
    if(isEmpty()){
        exit(0);
    }
    front = (front+1)%capacity;
    count--;
}
int Buffer::viewBack(){
    return arr[back];
}
int Buffer::viewFront(){
    return arr[front];
}
// 
// SafeBuffer.cpp ends here