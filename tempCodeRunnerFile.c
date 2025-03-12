#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TABLE_SIZE 10

struct HashTable {
    char key[100]; //for the key or value
}ht[TABLE_SIZE];

//initialization function: Has Table
void initializationHT() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        strcpy(ht[i].key, ""); //set empty data
    }
}

int StringToInteger(char key[]) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i]; //sum of ASCII values of character
    }
    return sum;
}

//Hash Function (Division)
int Division(char key[]) {
    int intKey = StringToInteger(key);
    return intKey % TABLE_SIZE;
}

int firstCharHash(char key[]) {

    //Check if there is data
    if(key[0] == '\0') {
        return -1;
    }
    char firstChar = key[0];

    //Check if the first character is a word
    if(!isalpha(firstChar)) {
        return -1;
    }
    return tolower(firstChar) - 'a';
}

int FoldingHash(char key[]) {
    int sum = 0;
    int groupSize = 2;
    int len = strlen(key);

    for (int i = 0; i < len; i += groupSize) {
        int groupValue= 0;

        for (int j = 0; j < groupSize && (i + j) < len; j++) {
            groupValue = (groupValue << 8) + key[i + j];
        }

        sum += groupValue;
    }

    return sum % TABLE_SIZE;
}

// Insert data into Hash Table with Linear Probing
void insert(char key[], int(*hashFunction)(char[])) {
    int index = hashFunction(key);
    int originalIndex = index; // Store original index
    int i = 0;

    // Linear probing: search for next available slot if collision occurs
    while (strcmp(ht[index].key, "") != 0) {
        printf("Collision at index %d for key %s! Trying next slot...\n", index, key);
        i++;
        index = (originalIndex + i) % TABLE_SIZE; // Move to next index (circular)

        // If we've checked all slots, the table is full
        if (index == originalIndex) {
            printf("Hash table is full! Cannot insert key %s.\n", key);
            return;
        }
    }

    // Insert key into the available slot
    strcpy(ht[index].key, key);
    printf("Key %s inserted into index %d.\n", key, index);
}


//Function to display Hash Table
void displayHT() {
    printf("\nHash Table\n");
    for(int i = 0; i < TABLE_SIZE; i++) {
        if(strcmp(ht[i].key, "") != 0) {
            printf("Index %d: %s\n", i, ht[i].key);
        }
        else {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main() {
    initializationHT();
    char key[100];

    //Execute hashing uding hash function 
    int (*hashFunction)(char[]) = NULL;

    // hashFunction = Division;
    // hashFunction = firstCharHash;
    hashFunction = FoldingHash;

    //Input key
    while(1) {
        printf("Insert key (string) or exit to stop: ");
        scanf("%s", key);
        if(strcmp(key, "exit") == 0) break;
        insert(key , hashFunction);
    }

    //Display hash table
    displayHT();

    return 0;
}