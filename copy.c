#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int letterTrack = 0;
int letterBankLength = 0;
struct tuple possibilities;
int p_start = 0;
int p_end = 0;
struct tuple{
    int row_focus;
    int col_focus;
};

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
void printPathfinder(int** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%d \t", *(*(arr + i) +j));
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
void findFirst(char **arr, int **pathfinder, char *word, struct tuple *possibleFirsts){
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
void directions(char **arr, char *word, struct tuple *letterBank, int letterTrack, int struct_row, int struct_col){
    if(letterBankLength == strlen(word)){
        return;
    }
    if(*(*(arr + struct_row) + struct_col) == *(word + letterTrack)){ //COMPARING H TO E AGAIN
        struct tuple new_tup;
        new_tup.row_focus = struct_row;
        new_tup.col_focus = struct_col;
        letterBankLength += 1;
        *(letterBank + letterTrack) = new_tup;
        letterTrack += 1;
    }
    if(struct_col + 1 >= 0 && struct_col + 1 < bSize && struct_row + 1 >= 0 && struct_row + 1 < bSize && *(*(arr + struct_row + 1) + struct_col + 1) == *(word + letterTrack)){
        directions(arr, word, letterBank, letterTrack, struct_row + 1, struct_col + 1);
    }
    if(struct_col - 1 >= 0 && struct_col - 1 < bSize && struct_row - 1 >= 0 && struct_row - 1 < bSize && *(*(arr + struct_row - 1) + struct_col - 1) == *(word + letterTrack)){
        directions(arr, word, letterBank, letterTrack, struct_row - 1, struct_col - 1);
    }
    if(struct_col >= 0 && struct_col < bSize && struct_row - 1 >= 0 && struct_row - 1 < bSize && *(*(arr + struct_row - 1) + struct_col) == *(word + letterTrack) ){
        directions(arr, word, letterBank, letterTrack, struct_row - 1, struct_col);
    }
    if(struct_col + 1 >= 0 && struct_col + 1 < bSize && struct_row - 1 >= 0 && struct_row - 1 < bSize && *(*(arr + struct_row - 1) + struct_col + 1) == *(word + letterTrack)){
        directions(arr, word, letterBank, letterTrack, struct_row - 1, struct_col + 1);  
    }
    if(struct_col - 1 >= 0 && struct_col - 1 < bSize && struct_row >= 0 && struct_row < bSize && *(*(arr + struct_row) + struct_col - 1) == *(word + letterTrack)){
        directions(arr, word, letterBank, letterTrack, struct_row, struct_col - 1); 
    }
    if(struct_col - 1 >= 0 && struct_col - 1 < bSize && struct_row >= 0 && struct_row < bSize && *(*(arr + struct_row) + struct_col + 1) == *(word + letterTrack)){
        directions(arr, word, letterBank, letterTrack, struct_row, struct_col + 1); 
    }
    if(struct_col - 1 >= 0 && struct_col - 1 < bSize && struct_row + 1 >= 0 && struct_row + 1 < bSize && *(*(arr + struct_row + 1) + struct_col - 1) == *(word + letterTrack)){
        directions(arr, word, letterBank, letterTrack, struct_row + 1, struct_col - 1);
    }
    if(struct_col >= 0 && struct_col < bSize && struct_row + 1 >= 0 && struct_row + 1 < bSize && *(*(arr + struct_row + 1) + struct_col) == *(word + letterTrack)){
        directions(arr, word, letterBank, letterTrack, struct_row + 1, struct_col);   
    }
}
void correctPath(int **pathfinder, struct tuple *letterBank, int letterTrack){
    //BUILDS FINISHED RESULT
    for(int i = 1; i < letterBankLength; i++){
        if (*(*(pathfinder + (letterBank + i)->row_focus) + (letterBank + i)->col_focus) == 0){
            *(*(pathfinder + (letterBank + i)->row_focus) + (letterBank + i)->col_focus) = i+1 ;
        }
        else{
            *(*(pathfinder + (letterBank + i)->row_focus) + (letterBank + i)->col_focus) = *(*(pathfinder + (letterBank + i)->row_focus) + (letterBank + i)->col_focus) * 10 + i+1;
        }
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
    struct tuple *letterBank = (struct tuple *)malloc(strlen(word) * sizeof(struct tuple));
    struct tuple *possibleFirsts = (struct tuple *)malloc(strlen(word) * sizeof(struct tuple));

    findFirst(arr, pathfinder, word, possibleFirsts);

    struct tuple *p_traverse = possibleFirsts;

    while(letterBankLength != strlen(word) && p_start < p_end){
        letterBankLength = 0;
        directions(arr, word, letterBank, letterTrack, (possibleFirsts + p_start)->row_focus, (possibleFirsts + p_start)->col_focus);
        p_start += 1;
    }
    
    printf("\n");
    printf("Word found! \n");
    printf("Printing the search path: \n");
    correctPath(pathfinder, letterBank, letterTrack);
    printPathfinder(pathfinder);
}