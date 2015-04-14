
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

enum COMMAND { EXIT_PROGRAM, READ, STATES, LIST, OLDEST, YOUNGEST, FIND, MOVE, MERGE, ERROR};

string months[] = {"January", "February", "March", "April","May","June","July", "August", "September", "October", "November","December"};

//This function converts a string to an integer
//It returns a variable of type int
int converStringToInt(string myString){
    //atoi() isn't something you would normally know about it
    //Documentation link http://www.cplusplus.com/reference/cstdlib/atoi/
    return atoi(myString.c_str());
}
//This function converts a string to an long
//It returns a variable of type long
//This function assumes that the string being converted is NOT a zero!!
long convertStringToLong(string myString){
    //Documentation Link http://www.cplusplus.com/reference/cstdlib/atol/
    long convertedNumber;
    convertedNumber = atol(myString.c_str());
    //Check if conversion failed
    if (convertedNumber == 0){
        cout << "***Error: Conversion to long Failed. Unicode bytes " << endl;
        cout << "***       detected in Data File." << endl;
        cout << "***Error Reading File. Remove Unicode Bytes in Data File." << endl;
        for (int i = 0; i < myString.length(); i++){
            //cout << i << ": " << myString[i] << " ";
            //If it is not a digit, remove it
            if (!isdigit(myString[i])){
                cout << " <--  ***** Not a integer *****"<< endl;
            }
        }
        //throw  "***Error Reading File. Remove Unicode Bytes from first line";
        string newString = myString.substr(3);
        convertedNumber = atol(newString.c_str());
    }
    return convertedNumber;
}

//**************************
//          Date
//**************************

class Date {
    
private:
    int year;
    int month;
    int day;
    
public:
    //Constructor
    Date(); //Default Constructor
    Date(int y, int m, int d); //This is the constructor
    Date(string d); //Overloaded Constructor with accepting long date format
    //Deconstructor
    ~Date();
    
    //Member functions//
    void printInfo();
    void prettyPrint();
    void printInfoInline();
    
    //GETTERS//
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    
    //SETTERS//
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
    
    bool operator>(const Date& object){
        if(this->getYear() > object.getYear()){
            return true;
        }else if(this->getYear() == object.getYear()){
            
            if(this->getMonth() > object.getMonth()){
                return true;
            }else if (this->getMonth() == object.getMonth()){
                if(this->getDay() > object.getDay()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    
    bool operator<(const Date& object){
        if(this->getYear() < object.getYear()){
            return true;
        }else if(this->getYear() == object.getYear()){
            if(this->getMonth() < object.getMonth()){
                return true;
            }else if (this->getMonth() == object.getMonth()){
                if(this->getDay() < object.getDay()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};

//Default Constructor
Date::Date(){
    this->year = 0;
    this->month = 0;
    this->day = 0;
}

//Constructor with params
Date::Date(int y, int m, int d){
    this->year = y;
    this->month = m;
    this->day = d;
}

Date::Date(string d){
    
    //Change from string to a long
    long dateValue = convertStringToLong(d);
    
    /*
     //break the dateValue into Year Month Day
     this->year = int(dateValue/10000);
     this->month = (dateValue/100) % 100;
     this->day = dateValue % 100;
     */
    
    this->day = int(dateValue/1000000);
    this->month = (dateValue/10000) % 100;
    this->year = dateValue % 10000;
}

//Deconstructor
Date::~Date(){
}

//Member Functions//
//YYYYMMDD Format
void Date::printInfo(){
    int zero = 0;
    if(day < 10) printf("%d", zero);
    printf("%d", day);
    if(month < 10) printf("%d", zero);
    printf("%d", month);
    printf("%d\n", year);
}

void Date::printInfoInline(){
    int zero = 0;
    if(day < 10) printf("%d", zero);
    printf("%d", day);
    if(month < 10) printf("%d", zero);
    printf("%d", month);
    printf("%d", year);
}

void Date::prettyPrint(){
    printf("%d of %s %d\n", this->day, months[this->month].c_str(), this->year );
}

//GETTERS//
int Date::getYear() const{
    return this->year;
}
int Date::getMonth() const{
    return this->month;
}
int Date::getDay() const{
    return this->day;
}

//SETTERS//
void Date::setYear(int y){
    this->year = y;
}
void Date::setMonth(int m){
    this->month = m;
}
void Date::setDay(int d){
    this->day = d;
}

//**************************
//  List Node
//**************************

template<class Element>
class ListNode{
protected:
    Element* data;
    ListNode<Element>* next;
public:
    
    ListNode(){
        this->data = NULL;
        this->next = NULL;
    }
    
    ListNode(Element* data){
        this->data = data;
        this->next = NULL;
    }
    
    ListNode(Element* data, ListNode<Element>* next){
        this->data = data;
        this->next = next;
    }
    
    ~ListNode(){
        
    }
    
    //Deletes node and data
    void deleteWithData(){
        
        if(this->data){
            delete this->data;
            this->data = NULL;
        }
    }
    
    void deleteCascading(bool preserveData){
        this->deleteNode(preserveData);
        if(this->next){
            this->next->deleteCascading(preserveData);
            delete this->next;
            this->next = NULL;
        }
    }
    
    void deleteNode(bool preserveData){
        
        if(preserveData){
            this->deleteWithoutData();
        }else{
            this->deleteWithData();
        }
    }
    
    //deletes node and preserves data
    void deleteWithoutData(){
        this->data = NULL;
    }
    
    void setNext(ListNode<Element>* next){
        this->next = next;
    }
    void setData(Element* data){
        this->data = data;
    }
    
    ListNode<Element>* getNext(){
        return this->next;
    }
    
    Element* getData(){
        return this->data;
    }
};

//**************************
//  List
//**************************

template<class Element>
class List{
    
protected:
    
    ListNode<Element>* head;
    ListNode<Element>* tail;
    long size;
    bool enforceUniqueItems;
    
public:
    List(){
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
        this->enforceUniqueItems = false;
    };
    
    List(ListNode<Element>* head){
        this->head = head;
        this->tail = this->getUnknownTail(head);
    }
    
    List(ListNode<Element>* head, ListNode<Element> *tail, int size){
        this->head = head;
        this->tail = tail;
        this->size = size;
    }
    
    ~List(){
    }
    
    void deleteWithData(){
        if(this->head){
            delete this->head;
            this->head = NULL;
            this->tail = NULL;
            this->size = 0;
        }
    }
    
    void deleteWithoutData(){
        if(this->head){
            this->head->deleteWithoutData();
            delete this->head;
            this->head = NULL;
            this->tail = NULL;
            this->size = 0;
        }
    }
    
    Element* addNode(Element* data){
        ListNode<Element>* newNode = new ListNode<Element>(data);
        ListNode<Element>* returnedNode = this->addNode(newNode);
        return returnedNode->getData();
    }
    
    ListNode<Element>* getUnknownTail(ListNode<Element>* node){
        int i = 0;
        while(node->getNext() != NULL){
            node = node->getNext();
            i++;
        }
        this->size = i; //Reset our number of nodes since we didn't know what it was.
        return node;
    }
    
    ListNode<Element>* addNode(ListNode<Element>* node){
        
        //If every node must be unique, lets check for that. If we find a duplicate node, return that node, if not return the inserted node.
        //In other words, to avoid duplicates, lets return an existing node or the new node.
        if(this->enforceUniqueItems){
            ListNode<Element>* myNode = this->isNodeInList(node);
            if(myNode) return myNode;
        }
        
        //what if this is the first node to be added?
        if(this->head == NULL){
            //If head is ==  to NULL, it is the first node
            this->setHead(node);
            this->setTail(node);
        }else{
            //If it is not the first song, we can assume it needs to go on to the end
            //Check to see if the tail is equal to null
            if(this->tail == NULL){
                cout << "ERROR: Tail is empty :: Do something to fix it" << endl;
            }
            
            //Get the last ListNode<Element>
            ListNode<Element>* lastNode = this->getTail();
            lastNode->setNext(node); //Set the newLastNode to next
            this->setTail(node); // New last node
        }
        this->size++;
        return node;
    }
    
    //Setters and Getters
    void setHead(ListNode<Element>* node){
        this->head = node;
    }
    ListNode<Element>* getHead(){
        return this->head;
    }
    void setTail(ListNode<Element>* node){
        this->tail = node;
    }
    ListNode<Element>* getTail(){
        return this->tail;
    }
    void setEnforceUniqueItems(bool enforcement){
        this->enforceUniqueItems = enforcement;
    }
    
    bool getEnforceUniqueItems(){
        return this->enforceUniqueItems;
    }
    
    ListNode<Element>* getNode(int index){
        //check if index it out of bounds
        if(index >= this->size || index < 0){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }
        
        //Check to see if the index is at the beginning or at the end.
        if(index == 0 ){
            return this->head;
        }else if (index == this->size-1){
            return this->tail;
        }
        
        ListNode<Element>* currentNode = this->head;
        for (int i = 0; i < this->size; i++) {
            if (index == i) {
                return currentNode;
            } else {
                currentNode = currentNode->getNext();
            }
        }
        //it will never run this line
        return currentNode;
    }
    
    long getSize(){
        return this->size;
    }
    
    //FIXME: Find way to reduce code
    ListNode<Element>* isNodeInList(ListNode<Element>* node){
        ListNode<Element>* currentNode = this->getHead();
        while(currentNode){ // While will keep iterating over the list until it is null
            if(*currentNode->getData() == *node->getData()){
                return currentNode;
            }else{
                currentNode = currentNode->getNext();
            }
        }
        //If the node is not found, return NULL.
        return NULL;
    }
    
    ListNode<Element>* find(ListNode<Element>* node){
        return this->isNodeInList(node);
    }
    
    ListNode<Element>* findNodeAtIndex(long index){
        if(index < 0 || index >= this->size){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }
        long currentIndex = 0;
        
        ListNode<Element>* myCurrentNode = this->head;
        //FIXME: Can this be cleaned up?
        while(myCurrentNode){
            if(currentIndex == index){
                return myCurrentNode;
            }
            if(myCurrentNode->getNext() == NULL){
                return myCurrentNode;
            }else{
                currentIndex ++;
                myCurrentNode = myCurrentNode->getNext();
            }
        }
        return myCurrentNode;
    }
    
    Element* findData(Element* data){
        ListNode<Element>* currentNode = this->getHead();
        while(currentNode){ // While will keep iterating over the list until it is null
            if(*currentNode->getData() == *data){
                return currentNode;
            }else{
                currentNode = currentNode->getNext();
            }
        }
        //If the node is not found, return NULL.
        return NULL;
    }
    
    //Helper function for finding and deleting data
    void findAndDeleteNode(Element* data){
        this->findAndDeleteNode(data, false);
    }
    
    //will find the ListNode but preserve the data in it but delete the
    void findAndDeleteNode(Element* data, bool preserveData){
        
        ListNode<Element>* node = new ListNode<Element>(data);
        //ListNode<Element>* newNode = this->find(node);
        //ListNode<Element>* node = this->find(new ListNode<Element>(data));
        this->deleteNode(node, preserveData);
    }
    
    int indexForNode(ListNode<Element>* node){
        int index = 0;
        ListNode<Element>* myCurrentNode = this->head;
        //FIXME: can it be reduced?
        while(myCurrentNode){
            if(*myCurrentNode->getData() == *node->getData()){
                return index;
            }
            if(myCurrentNode->getNext() == NULL){
                return index;
            }else{
                index ++;
                myCurrentNode = myCurrentNode->getNext();
            }
        }
        return index;
    }
    
    void deleteNode(ListNode<Element>* node){
        this->deleteNode(node, false);
    }
    
    void deleteNode(ListNode<Element>* node, bool preserveData){
        if(node == NULL){
            cout << "Warning: Node can not equal null when deleting a listNode" << endl;
            return;
        }
        
        //use case if there is no elements in the list
        if(this->size == 0){
            cout << "Warning: cannot remove node from empty list " << endl;
            return;
        }
        
        //use case if there is only one element in the list
        if(this->size == 1){
            //ListNode<Element>* headNode = this->getHead();
            if(*node->getData() == *node->getData()){
                this->head->deleteNode(preserveData);
                delete this->head;
                this->head = NULL;
                this->tail = NULL;
                this->size = 0;
                return;
            }else{
                cout << "Warning: nodes do match and cannot be removed" << endl;
                return;
            }
        }
        
        //Check if the node being removed is the first element
        if(*node->getData() == *this->head->getData()){
            
            ListNode<Element>* temp = this->head->getNext();
            this->head->deleteNode(preserveData);
            delete this->head;
            this->head = temp;
            this->size--;
            return;
        }
        
        //Check if the node being removed is the last element
        if(*node->getData() == *this->tail->getData()){
            ListNode<Element>* temp = this->findNodeAtIndex(this->size - 2);
            this->tail->deleteNode(preserveData);
            delete this->tail;
            this->tail = temp;
            this->size--;
            this->tail->setNext(NULL);
            return;
        }
        
        //Use Case: If the item is in the middle, delete the node and set previous node to the "next" pointer of the next item of the node being deleted.
        int indexForNodeToDelete = this->indexForNode(node);
        
        //Get the NEXT  node
        ListNode<Element>*  myNextNode = this->findNodeAtIndex(indexForNodeToDelete + 1);
        //get the PREVIOUS  node
        ListNode<Element>*  myPreviousNode = this->findNodeAtIndex(indexForNodeToDelete - 1);
        myPreviousNode->setNext(myNextNode);
        
        this->size --;    //Decrement the number nodes
        node->deleteNode(preserveData);
        delete node;
    }
    
    void Divide(ListNode<Element>* first, ListNode<Element>* &second ){
        ListNode<Element>* middle;
        ListNode<Element>* current;
        
        //Check for empty list
        if(first == NULL){
            second = NULL;
        }else if (first->getNext() == NULL){
            second = NULL;
        }else{
            middle = first;
            current = first->getNext();
            if(current != NULL){
                current = current->getNext();
            }
            while(current != NULL){
                middle = middle->getNext();
                current = current->getNext();
                if(current != NULL){
                    current = current->getNext();
                }
            }
            second = middle->getNext();
            middle->setNext(NULL);
        }
    }
    
    ListNode<Element>* MergeList(ListNode<Element>* first, ListNode<Element>* second){
        ListNode<Element>* lastSmall;
        ListNode<Element>* newHead;
        
        if(first == NULL){
            return second;
        }else if(second == NULL){
            return first;
        }else{
            if(*first->getData() < *second->getData()){
                newHead = first;
                first = first->getNext();
                lastSmall = newHead;
            }else{
                newHead = second;
                second = second->getNext();
                lastSmall = newHead;
            }
            
            while(first != NULL && second != NULL){
                if(*first->getData() < *second->getData()){
                    lastSmall->setNext(first);
                    lastSmall = lastSmall->getNext();
                    first = first->getNext();
                }else{
                    lastSmall->setNext(second);
                    lastSmall = lastSmall->getNext();
                    second = second->getNext();
                }
            }
            
            if(first == NULL){
                lastSmall->setNext(second);
            }else{
                lastSmall->setNext(first);
            }
            return newHead;
        }
    }
    
    void RecMergeSort(ListNode<Element>* & head){
        ListNode<Element>* otherHead;
        if(head != NULL){
            if (head->getNext() != NULL){
                Divide(head,otherHead);
                RecMergeSort(head);
                RecMergeSort(otherHead);
                head = MergeList(head,otherHead);
            }
        }
    }
    
    void sort(){
        RecMergeSort(this->head);
        if(this->head == NULL){
            this->tail = NULL;
        }else{
            this->tail = this->head;
            while(this->tail->getNext() != NULL){
                this->tail = this->tail->getNext();
            }
        }
        
    }
};

//**************************
//      State
//**************************

class Person; //Forward Declartion of Person class
class State{
    
protected:
    string stateAbbreviation;
    List<Person>* people;
    
public:
    State(){
        this->stateAbbreviation = "";
        this->people = new List<Person>();
    }
    
    State(string abbreviation){
        this->stateAbbreviation = abbreviation;
        this->people = new List<Person>();
    }
    
    ~State(){
        this->people->deleteWithoutData();
        delete this->people;
        this->people = NULL;
    };
    
    //Setters & Getters
    void setState(string abbreviation){
        this->stateAbbreviation = abbreviation;
    }
    
    string getState() const{
        return this->stateAbbreviation;
    }
    
    void addPerson(Person* person){
        this->people->addNode(person);
    }
    
    List<Person>* getPeople(){
        return this->people;
    }
    
    void printInfo(){
        cout << this->stateAbbreviation << endl;
    }
    
    bool operator==(const State& object){
        if(this->getState() == object.getState()){
            return true;
        }else{
            return false;
        }
    }
    
    bool operator!=(const State& object){
        if(this->getState() == object.getState()){
            return false;
        }else{
            return true;
        }
    }
    
    bool operator>(const State& object){
        //if(this->getState().compare(object.getState()) < 0) {
        if(this->getState() > object.getState()){
            return true;
        }else{
            return false;
        }
    }
    
    bool operator<(const State& object){
        //if(this->getState().compare(object.getState()) > 0) {
        if(this->getState() < object.getState()){
            return true;
        }else{
            return false;
        }
    }
};

//**************************
//  Class Person
//**************************
class Person {
    
private:
    string lastName;
    string firstName;
    string ssn;
    Date* birthday;
    State* state;
    
public:
    //Constructor
    Person(); //Default Constructor
    Person(string ssn, string firstName, string lastName, Date* birthday, State* state);
    Person(string ssn, string firstName, string lastName, string birthday, State* state);
    Person(string ssn);
    Person(string firstName, string lastName);
    ~Person(); //Deconstructor
    
    //Member Functions//
    void printName();
    void printInfo(); //Print Name (first and last), SSN, Birthdate
    void printInfoInline();
    long age();     //Calculate the age of the person based on the birthdate
    
    //Setters and Getters
    
    //GETTERS//
    string getSsn() const;
    string getFirstName() const;
    string getLastName() const;
    Date* getBirthday() const;
    State* getState();
    
    //SETTERS//
    void setSsn(string ssn);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setBirthday(Date *birthday);      //Overloaded!!
    void setBirthday(string birthday);    //Overloaded!!
    void setState(State* state);
    
    bool operator==(const Person& object){
        if((this->getLastName() == object.getLastName() && this->getFirstName() == object.getFirstName()) || this->getSsn() == object.getSsn()){
            return true;
        }else{
            return false;
        }
    }
    
    bool operator!=(const Person& object){
        if((this->getLastName() == object.getLastName() && this->getFirstName() == object.getFirstName()) || this->getSsn() == object.getSsn()) {
            return false;
        }else{
            return true;
        }
    }
    
    bool operator>(const Person& object){
        if(this->getSsn() > object.getSsn()) {
            return true;
        }else{
            return false;
        }
    }
    
    bool operator<(const Person& object){
        if(this->getSsn() < object.getSsn()) {
            return true;
        }else{
            return false;
        }
    }
};

//Default Constructor
Person::Person(){
    delete this->birthday;
    this->birthday = NULL;
    //delete this->state; //Dont need to delete. The Database Object will take care of that
    this->state = NULL;
}

//Constructor with params
Person::Person(string ssn, string firstName, string lastName, Date* birthday, State* state){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = birthday;
    this->state = state;
}

Person::Person(string ssn, string firstName, string lastName, string birthday, State* state){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = new Date(birthday);
    this->state =  state;
}

Person::Person(string ssn){
    this->ssn = ssn;
    this->firstName = "John121";
    this->lastName = "Deere121";
    this->birthday = new Date("02021965");
    this->state =  new State("RANDOM");
}

Person::Person( string firstName, string lastName){
    this->ssn = "000000000";
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = new Date("02021965");
    this->state =  new State("RANDOM");
}

//Deconstructor
Person::~Person(){
}

//Member Functions//
//Prints full name
void Person::printName(){
    printf("%s %s \n", firstName.c_str(), lastName.c_str());
}

void Person::printInfo(){
    /*printf("SSN: %s \n", ssn.c_str());
    printf("First Name: %s \n", firstName.c_str());
    printf("Last Name: %s \n", lastName.c_str());
    printf("Birthdate (DDMMYYYY): ");
    birthday->printInfo();
    printf("State: %s\n", this->getState()->getState().c_str());
    */
    printf(" %s", ssn.c_str());
    printf("%s ", firstName.c_str());
    printf("%s ", lastName.c_str());
    birthday->printInfo();
    printf(" %s\n", this->getState()->getState().c_str());
}

void Person::printInfoInline(){
    printf(" %s ", ssn.c_str());
    printf("%s ", firstName.c_str());
    printf("%s ", lastName.c_str());
    birthday->printInfoInline();
    printf(" %s\n", this->getState()->getState().c_str());
}

long Person::age(){
    //This function computes the age to the nearest year.
    int age;
    age = 2014 - int(birthday->getYear());
    return age;
}

//Getters//
string Person::getSsn() const{
    return this->ssn; //Type of long
}
string Person::getFirstName() const{
    return this->firstName;
}
string Person::getLastName() const{
    return this->lastName;
}
Date* Person::getBirthday() const{
    return this->birthday;
}

State* Person::getState() {
    return this->state;
}

//Setters//
void Person::setSsn(string ssn){
    this->ssn = ssn;
}
void Person::setFirstName(string firstName){
    this->firstName = firstName;
}
void Person::setLastName(string lastName){
    this->lastName = lastName;
}

//Overloading -- two different means to the same end.
void Person::setBirthday(Date* birthdate){
    this->birthday = birthdate;
}
void Person::setBirthday(string b){
    this->birthday = new Date(b);
}
void Person::setState(State* state){
    this->state = state;
}

//**************************
//  Class Person
//**************************
class Database{
    
protected:
    List<Person>* people;
    List<State>* states;
    
public:
    long numberOfRecordsCounted;
    Database(){
        this->numberOfRecordsCounted = 0;
        this->people = new List<Person>();
        this->states = new List<State>();
        this->states->setEnforceUniqueItems(true);
    }
    
    ~Database(){
        
        delete this->people;
        delete this->states;
    }
    
    void readfile(string filename){
        this->numberOfRecordsCounted = 1;
        ifstream infile(filename.c_str()); //Open the file
        string str; // Declares a string and is used for temporary storage
        if (infile.is_open()){
            while (getline(infile,str)){
                string dateString;
                string ssnString;
                string firstName;
                string lastName;
                string stateString;
                
                string token;
                stringstream stringStream(str);
                
                //Get Birthday
                if (getline(stringStream, token, ' ')){
                    dateString = token;
                }
                //Get SSN
                if (getline(stringStream, token, ' ')){
                    ssnString = token;
                }
                //Get First Name
                if (getline(stringStream, token, ' ')){
                    firstName = token;
                }
                //Get Last Name
                if (getline(stringStream, token, ' ')){
                    lastName = token;
                }
                //Get State
                if (getline(stringStream, token, ' ')){
                    stateString = token;
                }
                //cout << "Birthdate: " << dateString << " ssn: " << ssnString << " firstname: " << firstName << " lastname: " << lastName << " state: " << stateString << endl;
                Date* birthdate = new Date(dateString); //Creates a new date object
                
                State* state = new State(stateString); //creating a new state
                state = this->states->addNode(state); //add it to the list BUT if there is already a state of the same name in it, return that state instead
                
                Person* person = new Person(ssnString, firstName, lastName, birthdate, state);
                state->addPerson(person);
                this->people->addNode(person);
                
                //person->printInfo();
                this->numberOfRecordsCounted ++;
            }
            infile.close();
        }
        else{
            cout << "Error: Unable to open file" << endl;
        }
    }
    
    List<Person>* getPeople(){
        return this->people;
    }
    
    List<State>* getStates(){
        return this->states;
    }
    
    void listStates(){
        int i = 0;
        ListNode<State> *currentHead = this->getStates()->getHead();
        while(currentHead){
            cout << i+1 << ": " << currentHead->getData()->getState() << endl;
            i++;
            currentHead = currentHead->getNext();
        }
    }
    
    void listPeopleInState(string stateAbrev){
        
        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);
        
        ListNode<State>* stateNode = this->states->find(newStateNode);
        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
    
    Person* findPerson(string firstName, string lastName){
        Person* newPerson = new Person(firstName, lastName);
        return this->findPerson(newPerson);
    }
    
    Person* findPerson(string ssn){
        Person* newPerson = new Person(ssn);
        return this->findPerson(newPerson);
    }
    
    Person* findPerson(Person* person){
        ListNode<Person>* newPersonNode = new ListNode<Person>(person);
        ListNode<Person>* personNode = this->people->find(newPersonNode);
        if(personNode){
            return personNode->getData();
        }else{
            return NULL;
        }
    }
    
    void findOldest(string stateAbrev){
        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);
        ListNode<State>* stateNode = this->states->find(newStateNode);
        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            Person* oldest = currentPerson->getData();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                if(currentPerson->getNext() != NULL){
                    if(*currentPerson->getData()->getBirthday() < *oldest->getBirthday()){
                        oldest = currentPerson->getData();
                    }
                }
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }
            
            cout << "The oldest person in " << stateAbrev << " is: ";
            oldest->printInfoInline();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
    
    void findYoungest(string stateAbrev){
        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);
        ListNode<State>* stateNode = this->states->find(newStateNode);
        
        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            Person* youngest = currentPerson->getData();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                if(currentPerson->getNext() != NULL){
                    if(*currentPerson->getData()->getBirthday() > *youngest->getBirthday()){
                        youngest = currentPerson->getData();
                    }
                }
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }
            
            cout << "The youngest person in " << stateAbrev << " is: ";
            youngest->printInfoInline();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }
    
    State* findState(string stateAbreviation){
        State* newState = new State(stateAbreviation);
        ListNode<State>* newStateNode = new ListNode<State>(newState);
        ListNode<State>* stateNode = this->states->find(newStateNode);
        if(stateNode){
            return stateNode->getData();
        }else{
            return NULL;
        }
    }
    
    //move ssn oldstate newstate
    void movePerson(string ssn, string oldStateString, string newStateString){
        Person* person = this->findPerson(ssn);
        State* oldState = this->findState(oldStateString);
        State* newState = this->findState(newStateString);
        if(person == NULL){
            cout << " -- " << ssn << " is not in the list of people" << endl;
        }else if (oldState == NULL){
            cout << " -- " << oldStateString << " is not in the list of states" << endl;
        }else if (newState == NULL){
            cout << " -- " << newStateString << " is not in the list of states" << endl;
        }else if (*person->getState() != *oldState){
            cout << " -- " << person->getFirstName() << " " << person->getLastName() << " does not live in " << oldState->getState() << endl;
        }
        else{
            
            //setting the person's state to the new state
            person->setState(newState);
            //remove the person from the old states linked list but preserve the person data
            oldState->getPeople()->findAndDeleteNode(person, true);
            //add the person to the new states data
            newState->getPeople()->addNode(person);
            newState->getPeople()->sort();
        }
    }
    
    //FIXME: and make me effecient
    void movePerson(Person* person, string oldStateString, string newStateString){
        this->movePerson(person->getSsn(),   oldStateString,  newStateString);
    }
    
    void mergeStates(string stateString1, string stateString2, string newStateString){
        
        State* state1 = this->findState(stateString1);
        State* state2 = this->findState(stateString2);
        State* newState = this->findState(newStateString);
        if(state1 == NULL){
            cout << " -- " << stateString1 << " is not in the list of states" << endl;
        }else if (state2 == NULL){
            cout << " -- " << stateString2 << " is not in the list of states" << endl;
        }else if (newState != NULL){
            cout << " -- " << newStateString << " is already a state and cannot be created." << endl;
        }else{
            while(state1->getPeople()->getSize() > 0){
                Person* person = state1->getPeople()->findNodeAtIndex(0)->getData();
                this->movePerson(person, stateString1, stateString2);
            }
            
            state2->setState(newStateString);
            this->states->findAndDeleteNode(state1);
            state2->getPeople()->sort();
        }
    }
};

//**************************
//  Test Cases
//  Interpreter
//**************************

//enum COMMAND { EXIT_PROGRAM, READ, STATES, LIST, OLDEST, YOUNGEST, FIND, MOVE, MERGE, ERROR};

void testDateClass(){
    Date* date = new Date(2015,4,2);
    assert(date->getYear() == 2015);
    assert(date->getMonth() == 4);
    assert(date->getDay() == 2);
}

void testPersonClass(){
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date, state);
    
    assert(person->getSsn() == "00000000" );
    assert(person->getFirstName() == "MyFirstName" );
    assert(person->getLastName() == "MyLastName" );
    
    Person* person1 = new Person("00000001", "MyFirstName", "MyLastName", date, state);
    Person* person2 = new Person("00000002", "MyFirstName", "MyLastName", date, state);
    //Person* person3 = new Person("00000003", "MyFirstName", "MyLastName", date, state);
    Person* person4 = new Person("00000004", "MyFirstName", "MyLastName", date, state);
    
    assert(*person1 < *person2);
    assert(*person2 > *person1);
    assert(!(*person2 < *person1));
    assert(*person4 > *person2);
    assert(!(*person1 > *person4));
}

void testStateClass(){
    
    State* newyork = new State("NY");
    State* newyork1 = new State("NY");
    State* newjersey = new State("NJ");
    
    assert( *newyork == *newyork1);
    assert( *newyork != *newjersey);
    
    string NY = "NY";
    string NJ = "NJ";
    assert(NY > NJ);
    assert( *newyork > *newjersey);
    assert( *newjersey < *newyork);
    assert(!(*newjersey > *newyork));
    assert(!(*newyork < *newjersey));
}

void testLinkedListSort(){
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    State* state1 = new State("NJ");
    State* state2 = new State("AL");
    State* state3 = new State("HI");
    State* state4 = new State("DC");
    
    Person* person = new Person("00100000", "MyFirstName", "MyLastName", date, state);
    Person* person1 = new Person("00030001", "MyFirstName", "MyLastName", date, state);
    Person* person2 = new Person("010000002", "MyFirstName", "MyLastName", date, state);
    Person* person3 = new Person("00000103", "MyFirstName", "MyLastName", date, state);
    Person* person4 = new Person("00100004", "MyFirstName", "MyLastName", date, state);
    
    List<Person> *personList = new List<Person>();
    personList->addNode(person);
    personList->addNode(person1);
    personList->addNode(person2);
    personList->addNode(person3);
    personList->addNode(person4);
    
    personList->sort();
    
    ListNode<Person>* currentHead = personList->getHead();
    
    while(currentHead){
        //cout << " " << currentHead->getData()->getSsn() << endl;
        if(currentHead->getNext()){
            assert(*currentHead->getData() < *currentHead->getNext()->getData());
        }
        currentHead = currentHead->getNext();
    }
    
    List<State> *stateList = new List<State>();
    stateList->addNode(state);
    stateList->addNode(state1);
    stateList->addNode(state2);
    stateList->addNode(state3);
    stateList->addNode(state4);
    
    
    stateList->sort();
    ListNode<State>* currentHeadState = stateList->getHead();
    while(currentHeadState){
        //cout << " " << currentHeadState->getData()->getState() << endl;
        if(currentHeadState->getNext()){
            assert(*currentHeadState->getData() < *currentHeadState->getNext()->getData());
        }
        currentHeadState = currentHeadState->getNext();
    }
}

void testLinkedList(){
    
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date, state);
    
    List<Person>* personList = new List<Person>();
    personList->addNode(person);
    
    ListNode<Person> *myPersonNode = personList->getHead();
    Person* myPerson = myPersonNode->getData();
    assert(myPerson->getLastName() == person->getLastName() );
    assert(*myPersonNode->getData() == *person );
    
    Person* newPerson = new Person("123", "FunTimes", "Ahead", date,state );
    personList->addNode(newPerson);
    
    ListNode<Person> *newPersonNode = personList->getTail();
    assert(*newPersonNode->getData() == * newPerson );
    assert(personList->getSize() == 2);
    
    Person* thirdPerson = new Person("1234", "MoreFunTimes", "WayAhead", date, state);
    personList->addNode(thirdPerson);
    assert(personList->getSize() == 3);
    
    personList->setEnforceUniqueItems(true);
    //Now i should not be able to re-insert "person"
    Person* myreturnedObject = personList->addNode(person);
    assert(*myreturnedObject == *person);
    assert(personList->getSize() == 3);
}

void testDatabase(string databaseLocation){
    Database* database = new Database();
    database->readfile(databaseLocation);
    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);
    
    State *headState = database->getStates()->getHead()->getData();
    List<Person>* peopleInState = headState->getPeople();
    //cout << "State: " << headState->getState() << endl;
    ListNode<Person>* currentPerson = peopleInState->getHead();
    while(currentPerson){
        //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
        assert(headState == currentPerson->getData()->getState());
        currentPerson = currentPerson->getNext();
    }
}

void testDateComparisonOperators(){
    Date* date1 = new Date("02021965");
    Date* date2 = new Date("24101947");
    Date* date3 = new Date("16061930");
    Date* date4 = new Date("13021922");
    
    assert(*date1 > *date2);
    assert(*date2 < *date1);
    assert(!(*date3 > *date2));
    assert(*date4 < *date1);
}

void testListFindNodeAndDatafunctions(string databaseLocation){
    //TODO: implement
    assert(false);
}

void testDeletionOfNodeInList(string databaseLocation){
    Database* database = new Database();
    database->readfile(databaseLocation);
    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);
}

void testMovePersonFunctionDatabase(string databaseLocation){
    Database* database = new Database();
    database->readfile(databaseLocation);
    
    int personIndex = 5;
    int oldStateIndex = 5;
    int newStateIndex = 6;
    
    Person* person = database->getPeople()->findNodeAtIndex(personIndex)->getData();
    ListNode<Person>* personNode = database->getPeople()->findNodeAtIndex(personIndex);
    person->printInfoInline();
    
    database->listStates();
    assert(database->getPeople()->indexForNode(personNode) == personIndex);
    
    State* oldState = database->getStates()->findNodeAtIndex(oldStateIndex)->getData();
    oldState->printInfo();
    State* newState = database->getStates()->findNodeAtIndex(newStateIndex)->getData();
    newState->printInfo();
    
    database->listPeopleInState(oldState->getState());
    database->listPeopleInState(newState->getState());
    
    database->movePerson(person->getSsn(), oldState->getState(), newState->getState());
    
    database->listPeopleInState(oldState->getState());
    database->listPeopleInState(newState->getState());
}

void testDatabaseDeletion(string databaseLocation){
    Database* database = new Database();
    
    database->readfile(databaseLocation);

    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);
    
    State *headState = database->getStates()->getHead()->getData();
    List<Person>* peopleInState = headState->getPeople();
    cout << "State: " << headState->getState() << endl;
    ListNode<Person>* currentPerson = peopleInState->getHead();
    while(currentPerson){
        cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
        assert(headState == currentPerson->getData()->getState());
        currentPerson = currentPerson->getNext();
    }
    delete database;
    database = new Database();
    database->readfile(databaseLocation);
    
    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);
    
    State *headState2 = database->getStates()->getHead()->getData();
    List<Person>* peopleInState2 = headState2->getPeople();
    cout << "State: " << headState2->getState() << endl;
    ListNode<Person>* currentPerson2 = peopleInState2->getHead();
    while(currentPerson2){
        cout << "    - " << currentPerson2->getData()->getLastName() << " "  << currentPerson2->getData()->getState()->getState() << endl;
        assert(headState2 == currentPerson2->getData()->getState());
        currentPerson2 = currentPerson2->getNext();
    }
}

vector<string> parseCommandString(string commandString){
    vector <string> arguments;
    
    string token;
    stringstream stringStream(commandString);
    
    while(getline(stringStream, token, ' ')){
        arguments.push_back(token);
    }
    
    if(arguments.size() == 0){
        arguments.push_back("ERROR");
    }
    return arguments;
}

COMMAND commandDetector(string s){
    if(s == "exit" ){
        return EXIT_PROGRAM;
    }else if(s == "read" ){
        return READ;
    }else if(s == "states" ){
        return STATES;
    }else if(s == "list" ){
        return LIST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest"){
        return YOUNGEST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest") {
        return YOUNGEST;
    }else if (s == "find" ){
        return FIND;
    }else if (s == "move") {
        return MOVE;
    }else if (s == "merge") {
        return MERGE;
    }else{
        //cout << "Error" << endl;
        return ERROR;
    }
}

void commandLineInterpreter(){
    cout << "Enter a command:" << endl;
    int command = 100;
    string commandString;
    Database* database;
    do{
        cout << "> ";
        getline(cin, commandString);
        vector<string> arguments = parseCommandString(commandString);
        COMMAND comm = commandDetector(arguments[0]);
        
        if(database == NULL && !(comm == READ || comm == EXIT_PROGRAM)){
            cout << "Error: There must be a data present prior to running commands against the database." << endl;
        }else{
            switch (comm){
                case READ:
                    cout << "READING" << endl;
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguements." << endl;
                        cout << "E.g. read /home/www/class/een118/labs/152/dbfile1.txt" << endl;
                    }else{
                        database = new Database();
                        database->readfile(arguments[1]);
                        cout << "Reading Complete" << endl;
                    }
                    break;
                case STATES:
                    
                    cout << "States" << endl;
                    if(arguments.size()>=2 ){
                        cout << "Error: Illegal number of arguments. This command takes one arguement." << endl;
                        cout << "E.g. states" << endl;
                    }else{
                        database->listStates();
                    }
                    break;
                case LIST:
                    
                    cout << "List" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. list FL" << endl;
                    }else{
                        database->listPeopleInState(arguments[1]);
                    }
                    break;
                case OLDEST:
                    
                    cout << "OLDEST" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. oldest NY" << endl;
                    }else{
                        database->findOldest(arguments[1]);
                    }
                    break;
                case YOUNGEST:
                    cout << "YOUNGEST" << endl;
                    
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. youngest NY" << endl;
                    }else{
                        database->findYoungest(arguments[1]);
                    }
                    break;
                    
                case FIND:
                    cout << "FIND" << endl;
                    
                    if(arguments.size() != 3){
                        cout << "Error: Illegal number of arguments. This command takes three arguement." << endl;
                        cout << "E.g. find Larry Brown" << endl;
                    }else{
                        Person* person = database->findPerson(arguments[1], arguments[2]);
                        if(person){
                            cout << "  FOUND: " ;
                            person->printInfoInline();
                        }else{
                            cout << " -- " << arguments[1] << " " <<  arguments[2] << " is not in the list of people" << endl;
                        }
                    }
                    break;
                    
                case MOVE:
                    
                    cout << "MOVE - If you want the list of people in state after the person moves use list command" << endl;
                    //FIXME: Insert in social security order
                    if(arguments.size() != 4){
                        cout << "Error: Illegal number of arguments. This command takes four arguement." << endl;
                        cout << "E.g. move 108690448 KS MD" << endl;
                    }else{
                        database->movePerson(arguments[1], arguments[2], arguments[3]);
                    }
                    break;
                    
                case MERGE:
                    cout << "MERGE - If you want a list of the merged states use list command with new state name" << endl;
                    
                    if(arguments.size() != 4){
                        cout << "Error: Illegal number of arguments. This command takes four arguement." << endl;
                        cout << "E.g. merge NC SC CR" << endl;
                    }else{
                        database->mergeStates(arguments[1], arguments[2], arguments[3]);
                    }
                    break;
                case EXIT_PROGRAM:
                    command = 0;
                    cout << "EXITING" << endl;
                    break;
                    
                case ERROR:
                    cout<< "Error: Illegal Syntax in command" << endl;
        
                default:
                    cout<< "Error: Illegal Syntax in command" << endl;
            }
        }
    }while(command != 0);
    cout << "Final EXIT" << endl;
}

//**************************
//         Main
//**************************

int main() {
    //string testDatabaseLocation = "/home/www/class/een118/labs/152/dbfile1.txt";
    //string testDatabaseLocation = "/Users/susanchang/Desktop/dbfile1.txt";
    //testDatabase(testDatabaseLocation);
    /*
     testLinkedListSort();
     testDateClass();
     testDateComparisonOperators();
     testPersonClass();
     testStateClass();
     testLinkedList();
     testDatabase(testDatabaseLocation);
     //testDatabaseDeletion();
     //testMovePersonFunctionDatabase(testDatabaseLocation);
     */
    commandLineInterpreter();
    
    return 0;
}

