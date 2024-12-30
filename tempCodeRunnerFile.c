    BUILDS FINISHED RESULT
    for(int i = 0; i < letterBankLength; i++){
        *(*(pathfinder + (letterBank + i)->row_focus) + (letterBank + i)->col_focus) = letterTrack + '0';
        letterTrack += 1;
    }