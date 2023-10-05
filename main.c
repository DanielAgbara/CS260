#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INITIAL_CAPACITY 2

// Struct for Entry
typedef struct entry
{
    char *name;
    char *lastname;
    float height;
    int age;
} Entry;

//Struct for List
typedef struct list 
{
	int capacity;
	int size;
	Entry** data;
} List;

//Function that initialize the list, this function returns a list pointer
List* initializeList()
{
    List* newlist = malloc(sizeof(List));
    newlist->size = 0;
    newlist->capacity = INITIAL_CAPACITY;
    newlist->data = malloc(sizeof(Entry) * newlist->capacity);

    return newlist;

}

//function that creates a new entry, this fucntion returns and entry pointer
Entry* CreateEntry(char* name, char* lastname, float height, int age)
{
    Entry* newEntry = malloc(sizeof(Entry));
    newEntry->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(newEntry->name, name);

    newEntry->lastname = malloc(sizeof(char) * (strlen(lastname) + 1));
    strcpy(newEntry->lastname, lastname);

    newEntry->height = height;
    newEntry->age = age;

    return newEntry;
}
void deleteList(List *myList){
    free(myList->data);
    free(myList);
}

void freeEntry(Entry *entry)
{
    if (entry != NULL)
    {
        free(entry->name);
        free(entry->lastname);
        free(entry);
    }
}
//This function will double the capacity of the List when the size = capacity
void doubleCapacity(List *myList){
    myList->capacity = myList->capacity * 2;
    myList->data = realloc(myList->data, sizeof(Entry) * myList->capacity);

}

// This function will double the capacity of the List when the size is less than halve of the capacity
void halveCapacity(List *myList){
    myList->capacity = myList->capacity / 2;
    myList->data = realloc(myList->data, sizeof(Entry) * myList->capacity);
}

//gotten from the starter pack
void printList(List *myList)
{
    if (myList->size == 0)
    {
        printf("List is empty!\n");
    }
    else
    {
        for (int i = 0; i < myList->size; i++)
        {
            printf("[%d]\t%s\t%s\t%0.2f\t%d\n", i, myList->data[i]->name, myList->data[i]->lastname, myList->data[i]->height, myList->data[i]->age);
        }
    }
}

//gotten from the starter pack
void printListInfo(List *myList)
{
    printf("size:%d, capacity:%d\n", myList->size, myList->capacity);
}
void insertToHead(List *myList, char *name, char *lastname, float height, int age){
    //initializing Entry
    Entry *Entry = CreateEntry(name, lastname, height, age);
    //Checking if the List is empty
    if (myList->size == 0){
        myList->data[myList->size] = Entry;
        myList->size++;
        

    }else if (myList->size < myList->capacity){
        //Shift exsiting entries to the right as illustrated in the Description
        for (int i = (myList->size); i > 0; i--)
        {
            myList->data[i] = myList->data[i - 1];
        }

        //Setting the new entry as the head
        myList->data[0] = Entry;
        myList->size++;

    }else if (myList->size == myList->capacity){
        doubleCapacity(myList);
        // Shift exsiting entries to the right as illustrated in the Description
        for (int i = (myList->size); i > 0; i--)
        {
            myList->data[i] = myList->data[i - 1];
        }
        // Setting the new entry as the head
        myList->data[0] = Entry;
        myList->size++;
    }
}

void insertToPosition(List *myList, int position, char *name, char *lastname, float height, int age){
    // initializing Entry
    Entry *Entry = CreateEntry(name, lastname, height, age);
    //if position = 0, then I am technically inserting to the head
    if (position == 0){
        //Checking if the list is empty
        if (myList->size == 0)
        {
            myList->data[0] = Entry;
            myList->size++;
        }
        else
        {
            // Checking if there is space in the list 
            if (myList->size < myList->capacity)
            {
                //Shift exsiting entries to the right as illustrated in the Description
                for (int i = (myList->size); i > 0; i--)
                {
                    myList->data[i] = myList->data[i - 1];
                }

                // Setting the new entry as the head
                myList->data[0] = Entry;
                myList->size++;

            }else if (myList->size == myList->capacity){
                doubleCapacity(myList);
                // Shift exsiting entries to the right as illustrated in the Description
                for (int i = (myList->size); i > 0; i--)
                {
                    myList->data[i] = myList->data[i - 1];
                }
                // Setting the new entry as the head
                myList->data[0] = Entry;
                myList->size++;
            
            }
        }
    }else if ((position != 0)  && (position < myList->size)){
        //Checking if the List is full
        if (myList->size < myList->capacity)
        {
            // Shift exsiting entries from [Position, size] to the right as illustrated in the Description
            for (int i = (myList->size); i > position; i--)
            {
                myList->data[i] = myList->data[i - 1];
            }

            // Setting the new entry as the head
            myList->data[position] = Entry;
            myList->size++;
        }
        // if the list is full, the program will double capacity
        else if (myList->size == myList->capacity)
        {
            doubleCapacity(myList);
            // Shift exsiting entries from [Position, Size] to the right as illustrated in the Description
            for (int i = (myList->size); i > position; i--)
            {
                myList->data[i] = myList->data[i - 1];
            }
            // Setting the new entry as the head
            myList->data[position] = Entry;
            myList->size++;
        }
    //if the position equals to the size of the list, that is technically insert to tail
    }else if (position == myList->size){
        if (myList->size < myList->capacity){
            //Placing the entry at the tail
            myList->data[position] = Entry;        
            //incremet the size
            myList->size++;
        }else if (myList->size == myList->capacity){
            //Double the capacity
            doubleCapacity(myList);
            //Placing the entry at the tail
            myList->data[position] = Entry;

            //increment list size
            myList->size++;
        }
    }else if (position > myList->size){
        printf("List is too Small to insert at that Position\n");
    }
}
//Function that inserts entry at the end the of the list
void insertToTail(List *myList, char *name, char *lastname, float height, int age){
    Entry *Entry = CreateEntry(name, lastname, height, age);
    if (myList->size < myList->capacity)
    {
        // Placing the entry at the tail
        myList->data[myList->size] = Entry;
        // incremet the size
        myList->size++;
    }
    else if (myList->size == myList->capacity)
    {
        // Double the capacity
        doubleCapacity(myList);
        // Placing the entry at the tail
        myList->data[myList->size] = Entry;

        // increment list size
        myList->size++;
    }
}

void deleteFromHead(List *myList){
    Entry* head;
    head = myList->data[0];

    //shifting the values array to the left
    for(int i = 1; i < myList->size; i++){
        myList->data[i - 1] = myList->data[i];
    }

    myList->size--;
    //checking if the size of the list is half of the capacity
    if (myList->size < (myList->capacity / 2))
    {
        halveCapacity(myList);   
    }
}

void deleteFromTail(List *myList){
    Entry* Tail;
    Tail = myList->data[(myList->size) - 1];

    myList->size--;
    // checking if the size of the list is half of the capacity
    if (myList->size < (myList->capacity / 2))
    {
        halveCapacity(myList);
    }
}
void deleteFromPosition(List *myList, int position){
    //if position equals zero, then it is technically delete from head
    if (position == 0){
        Entry *head;
        head = myList->data[0];
        
        // shifting the values array to the left
        for (int i = 1; i < myList->size; i++)
        {
            myList->data[i - 1] = myList->data[i];
        }

        myList->size--;
        // checking if the size of the list is half of the capacity
        if (myList->size < (myList->capacity / 2))
        {
            halveCapacity(myList);
        }
    }
    else if ((position != 0) && (position < myList->size))
    {
        Entry *delentry;
        delentry = myList->data[position];
        //freeEntry(delentry);

        // shifting the values array to the left
        for (int i = (position + 1); i < myList->size; i++)
        {
            myList->data[i - 1] = myList->data[i];
        }

        myList->size--;
        // checking if the size of the list is half of the capacity
        if (myList->size < (myList->capacity / 2))
        {
            halveCapacity(myList);
        }
    }
    else if (position > myList->size)
    {
        printf("List is too Small to Delete at that Position\n");
    }
}
int findPosition(List *myList, char *name){
    int index = -1;
    for(int i = 0; i < myList->size; i++){
        if (strcmp(name, myList->data[i]->name) == 0){
            return i;
        }
    }
    return index;
}

//Program will take the path of file with the commands, this is done through the command line
//Using argc and argv to get this done
//argc is the number of arguments and argv is the values in an array
int main(int argc, char *argv[])
{
    //File Handling
    // Open the file for reading
    FILE *fp = fopen(argv[1], "r");
    char* line = NULL;
    size_t lineBuffSize = 0;
    size_t linesize;

    // Check if the file was successfully opened
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        return -1;
    }


    //initializing list before working on the file
    List* myList = initializeList();

    // Read and print each line from the file
    while ((linesize = getline(&line, &lineBuffSize, fp)) != -1)
    {
        char *token;
        const char delimiter[2] = " ";

        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        token = strtok(line, delimiter);

        if (strcmp(token, "insertToHead") == 0)
        {
            char *name;
            char *lastname;
            float height;
            int age;

            name = strtok(NULL, delimiter);
            lastname = strtok(NULL, delimiter);
            height = atof(strtok(NULL, delimiter));
            age = atoi(strtok(NULL, delimiter));

            
            //Implenting InserttoHead function
            insertToHead(myList, name, lastname, height, age);
        }
        else if (strcmp(token, "insertToPosition") == 0)
        {
            char *name;
            char *lastname;
            float height;
            int age;
            int position;

            position = atoi(strtok(NULL, delimiter));
            name = strtok(NULL, delimiter);
            lastname = strtok(NULL, delimiter);
            height = atof(strtok(NULL, delimiter));
            age = atoi(strtok(NULL, delimiter));
            // Uncomment the following insertToPosition function call when you have implemented it
            insertToPosition(myList, position, name, lastname, height, age);
        }
        else if (strcmp(token, "insertToTail") == 0)
        {
            char *name;
            char *lastname;
            float height;
            int age;

            name = strtok(NULL, delimiter);
            lastname = strtok(NULL, delimiter);
            height = atof(strtok(NULL, delimiter));
            age = atoi(strtok(NULL, delimiter));
            // Uncomment the following insertToTail function call when you have implemented it
            insertToTail(myList, name, lastname, height, age);
        }
        else if (strcmp(token, "deleteFromHead") == 0)
        {
            //implementing thye deletefromHead
            deleteFromHead(myList);
        }
        else if (strcmp(token, "deleteFromTail") == 0)
        {
            //Uncomment the following insertToHead function call when you have implemented it
            deleteFromTail(myList);
        }
        else if (strcmp(token, "deleteFromPosition") == 0)
        {
            int position;

            position = atoi(strtok(NULL, delimiter));

            // Uncomment the following deleteFromPosition function call when you have implemented it
            deleteFromPosition(myList, position);
        }
        else if (strcmp(token, "findPosition") == 0)
        {
            char *name;

            name = strtok(NULL, delimiter);
            //Uncomment the following printf statement using the return value from a findPosition function call when you have implemented the function
            printf("%d\n", findPosition(myList, name));
        }
        else if (strcmp(token, "printList") == 0)
        {
            printList(myList);
        }
        else if (strcmp(token, "printListInfo") == 0)
        {
            printListInfo(myList);
        }
        else if (strcmp(token, "deleteList") == 0)
        {
            // Uncomment the following deleteList function call when you have implemented it
            deleteList(myList);
        }
        else
        {
            printf("Invalid command: <%s>\n", token);
        }
    }
    
    // Close the file
    fclose(fp);
}