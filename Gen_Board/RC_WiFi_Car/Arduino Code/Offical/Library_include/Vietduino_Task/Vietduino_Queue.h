/*
 *  Vietduino_Queue.h (Clone and modify from Arduino.cc)
 *
 *  Library implementing a generic, dynamic queue (linked list version).
 *
 *  ---
 *
 *  Copyright (C) 2010  Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  ---
 *
 *  Version 1.0
 *
 */

// header defining the interface of the source.
#ifndef _VIETDUINO_H_QUEUE_H_
#define _VIETDUINO_H_QUEUE_H_

// include Arduino basic header.
#include <Arduino.h>

// the definition of the queue class.
template<typename T>
class Vietduino_Queue {
public:
    // init the queue (constructor).
    Vietduino_Queue ();

    // clear the queue (destructor).
    ~Vietduino_Queue ();

    // push an item to the queue.
    void push (const T i);

    // pop an item from the queue.
    T pop ();

    // pull an item from the queue (not delete).
    T pull ();

    // get an item from the queue.
    T peek () const;

    // check if the queue is empty.
    bool isEmpty () const;
    bool pull_available() const;
    void pull_reset_index();

    // get the number of items in the queue.
    int count () const;
    int getIndex() const;

    // set the printer of the queue.
    void setPrinter (Print & p);
    Print * printer; // the printer of the queue.

private:
    // exit report method in case of error.
    void exit (const char * m) const;

    // led blinking method in case of error.
    void blink () const;

    // the pin number of the on-board led.
    static const int ledPin = 13;

    // the structure of each node in the list.
    typedef struct node {
        T item;      // the item in the node.
        node * next; // the next node in the list.
    } node;

    typedef node * link; // synonym for pointer to a node.

//    Print * printer; // the printer of the queue.
    int size;        // the size of the queue.
    int index;        // the index of the queue.
    link head;       // the head of the list.
    link pull_head;       // the head of the list.
    link tail;       // the tail of the list.
};

// init the queue (constructor).
template<typename T>
Vietduino_Queue<T>::Vietduino_Queue () {
    size = 0;       // set the size of queue to zero.
    index = 0;
    head = NULL;    // set the head of the list to point nowhere.
    tail = NULL;    // set the tail of the list to point nowhere.
    printer = NULL; // set the printer of queue to point nowhere.
}

// clear the queue (destructor).
template<typename T>
Vietduino_Queue<T>::~Vietduino_Queue () {
    // deallocate memory space of each node in the list.
    for (link t = head; t != NULL; head = t) {
        t = head->next; delete head;
    }

    size = 0;       // set the size of queue to zero.
    tail = NULL;    // set the tail of the list to point nowhere.
    printer = NULL; // set the printer of queue to point nowhere.
}

// push an item to the queue.
template<typename T>
void Vietduino_Queue<T>::push (const T i) {
    // create a temporary pointer to tail.
    link t = tail;

    // create a new node for the tail.
    tail = (link) new node;

    // if there is a memory allocation error.
    if (tail == NULL)
        exit ("QUEUE: insufficient memory to create a new node.");

    // set the next of the new node.
    tail->next = NULL;

    // store the item to the new node.
    tail->item = i;

    // check if the queue is empty.
    if (isEmpty ()){
        // make the new node the head of the list.
        head = tail;
        pull_head = tail;
    }else
        // make the new node the tail of the list.
        t->next = tail;

    // increase the items.
    size++;
}

// pop an item from the queue.
template<typename T>
T Vietduino_Queue<T>::pop () {
    // check if the queue is empty.
    if (isEmpty ()){
        exit ("QUEUE: can't peek item from queue: queue is empty.");
//        return (T)0;
    }

    // get the item of the head node.
    T item = head->item;

    // remove only the head node.
    link t = head->next; delete head; head = t;

    // decrease the items.
    size--;

    // return the item.
    return item;
}

// pull an item from the queue.
template<typename T>
T Vietduino_Queue<T>::pull () {
    // check if the queue is empty.
    if (getIndex() == size){
        exit ("QUEUE: EndOfqueue");
//        return (T)0;
    }

    // get the item of the head node.
//    T item = head->item;
    T item = pull_head->item;

    link t;

    // remove only the head node.
    if(pull_available()){
        t = pull_head->next;
        pull_head = t;
        index++;
    }


    // return the item.
    return item;
}

// get an item from the queue.
template<typename T>
T Vietduino_Queue<T>::peek () const {
    // check if the queue is empty.
    if (isEmpty ()){
        exit ("QUEUE: can't peek item from queue: queue is empty.");
    }

    // return the item of the head node.
    return head->item;
}

// check if the queue is empty.
template<typename T>
bool Vietduino_Queue<T>::isEmpty () const {
    return head == NULL;
}

template<typename T>
bool Vietduino_Queue<T>::pull_available() const
{
    return (getIndex() < count ());
}

template<typename T>
void Vietduino_Queue<T>::pull_reset_index(){
    index = 0;
    pull_head = head;
}

// get the number of items in the queue.
template<typename T>
int Vietduino_Queue<T>::count () const {
    return size;
}

// get the index of items in the queue.
template<typename T>
int Vietduino_Queue<T>::getIndex() const {
    return index;
}

// set the printer of the queue.
template<typename T>
void Vietduino_Queue<T>::setPrinter (Print & p) {
    printer = &p;
}

// exit report method in case of error.
template<typename T>
void Vietduino_Queue<T>::exit (const char * m) const {
    // print the message if there is a printer.
    if (printer)
        printer->println (m);

    // loop blinking until hardware reset.
    //  blink ();
}

// led blinking method in case of error.
template<typename T>
void Vietduino_Queue<T>::blink () const {
    // set led pin as output.
    pinMode (ledPin, OUTPUT);

    // continue looping until hardware reset.
    while (true) {
        digitalWrite (ledPin, HIGH); // sets the LED on.
        delay (250);                 // pauses 1/4 of second.
        digitalWrite (ledPin, LOW);  // sets the LED off.
        delay (250);                 // pauses 1/4 of second.
    }

    // solution selected due to lack of exit() and assert().
}

#endif // _QUEUELIST__KXN_H
