    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // Declarations of the two functions you will implement
    // Feel free to declare any helper functions or global variables
    void printPuzzle(char** arr);
    void searchPuzzle(char** arr, char* word);
    int bSize;

    struct pairs{
        int row;
        int col;
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
        for(int i = 0; i < bSize; i++){
            for(int j = 0; j < bSize; j++){
                printf("%c ", *(*(arr + i) + j));
            }
            printf("\n");
        }
        printf("\n");
    }

    void printMatrix(int** array) {
        for(int i = 0; i < bSize; i++){
            for(int j = 0; j < bSize; j++){
                printf("%d ", *(*(array + i) + j));
            }
            printf("\n");
        }
        printf("\n");
    }



    void UpperCase(char* word){
        for(int i = 0; i < strlen(word); i++){
            if(*(word + i) >= 'a' && *(word + i) <= 'z'){
                *(word + i) -= 32;
            }
        }
    }

    // void FirstLetter(char** arr, char* word){
    //     struct pairs z;
    //     for(int i = 0; i < bSize; i++){
    //         for(int j = 0; j < bSize; j++){
    //             if(*(*(arr + i) + j) == *(word)){
    //                 z.row = i;
    //                 z.col = j;
    //             }
    //         }
    //     }
    // }

    int Moves(char** arr, char* word, int x, int y, int index, struct pairs* coordinates){
        int length = strlen(word);

        if(index == length - 1){ // if reached end of word
            return 1;
        }
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if(i + x >= 0 && i + x < bSize && j + y >= 0 && j + y < bSize){
                    if(index < length){ // if not reached end
                        if(i == 0 && j == 0){ // ignore current location
                            continue;
                    }
                    if(*(*(arr + i + x) + j + y) == *(word + index)){
                        struct pairs coords;
                        coords.row = i + x;
                        coords.col = j + y;
                        *(coordinates + index) = coords; //check around current letter
                        Moves(arr, word, index + 1, x + i, y + j, coordinates);
                    }
                    else{
                        return 0;
                    }
                }

            }
            }
        }
        

        return 1;
    }

    void searchPuzzle(char** arr, char* word) {

        UpperCase(word);
        struct pairs *coordinates = (struct pairs *)malloc(strlen(word) * sizeof(struct pairs));
        // struct pairs *
        int x;
        int y;
        int index = 0;
        for(int i = 0; i < bSize; i++){
            for(int j = 0; j < bSize; j++){
                if(*(*(arr + i) + j) == *word){
                    if(Moves(arr, word, i, j, index,coordinates)){
                        x = j;
                        y = i;
                    }
                }
            }
        }

        int** array = (int**) malloc(bSize * sizeof(int*));
        for(int i = 0; i < bSize; i++){
            *(array + i) = (int*) malloc(bSize * sizeof(int));
            for(int j = 0; j < bSize; j++){
                *(*(array + i) + j) = 0;
            }
        }

        for(int i = 0; i < strlen(word); i++){
            if(*(*(array + (coordinates + i)->row) + (coordinates + i)->col) == 0){
                *(*(array + (coordinates + i)->row) + (coordinates + i)->col) = i +1;
            }
            else{
                *(*(array + (coordinates + i)->row) + (coordinates + i)->col) = *(*(array + (coordinates + i)->row) + (coordinates + i)->col) * 10 + i + 1;

            } 
        }

        //printMatrix(array);

        printf("%d", index);
        for(int i = 0; i < strlen(word); i++){
            printf("%d\n", (coordinates + i)->row);
            printf("%d\n", (coordinates + i)->col);
        }




        // This function checks if arr contains the search word. If the 
        // word appears in arr, it will print out a message and the path 
        // as shown in the sample runs. If not found, it will print a 
        // different message as shown in the sample runs.
        // Your implementation here...

    }
