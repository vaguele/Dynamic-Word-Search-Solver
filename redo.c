#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int p_end = 0; //tells us how many possible firsts we have
struct tuple{
    int row_focus;
    int col_focus;
};
struct tuple possibilities;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for(int i = 0; i < bSize; i++){
    for(int j = 0; j < bSize; j++){
        printf("%c \t", *(*(arr + i) +j));
    }
    printf("\n");
    }
}

void upperCase(char *word){
    for(int i = 0; i < strlen(word); i++){
        if(*(word + i) >= 'a' && *(word + i) <= 'z'){
            *(word + i) -=  32;
        }
    }
}

void findFirst(char **arr, char *word, struct tuple *possibleFirsts){
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if(*(*(arr + i) +j) == *(word+0)){
                possibilities.row_focus = i;
                possibilities.col_focus = j;
                *(possibleFirsts + p_end) = possibilities;
                p_end += 1;
            }
        }
    }
    for(int i = 0; i < p_end; i++){
        printf("(%d, %d)\n", (possibleFirsts + i)->row_focus, (possibleFirsts + i)->col_focus);
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    upperCase(word);
    int **pathfinder = (int**)malloc(bSize * sizeof(int*));
    for(int i = 0; i < bSize; i++){
        *(pathfinder + i) = (int*)malloc(bSize * sizeof(int));
        for(int j = 0; j < bSize; j++){
            *(*(pathfinder + i) + j) = 0;
        }
    }
    struct tuple *possibleFirsts = (struct tuple *)malloc(strlen(word) * sizeof(struct tuple));
    findFirst(arr, word, possibleFirsts);

    for(int i = 0; i < p_end; i++){
        struct tuple *letterBank
        if(letterBankLength == strlen(word)){
            printf("Word found !\n");
            return;
        }
        directions(arr, word, letterBank, letterTrack, (possibleFirsts)->row_focus, (possibleFirsts)->col_focus)
    }
    
}
