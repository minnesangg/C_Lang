#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<hacking.h>

#define FILENAME "/var/notes"

int print_notes(int, int, char *);
int find_user_note(int, int);
int search_note(char *, char *);
void fatal(char *);

int main(int argc, char *argv[]){
    int userID, printing = 1, fdescrypt;
    char search_string[100];

    if(argc > 1){
        strcpy(search_string, argv[1]);
    }  else {
        search_string[0] = 0;
    }

    userID = getuid();

    fdescrypt = open(FILENAME, O_RDONLY);

    if(fdescrypt == -1)
        fatal("in main func when oppening file");

    while(printing){
        printing = print_notes(fdescrypt, userID, search_string);
    }
    printf("----------end of data of note----------");
    close(fdescrypt);

    return 0;
}

int print_notes(int fdescrypt, int uID, char *search_string){
    int note_length;
    char byte = 0, note_buffer[100];

    note_length = find_user_note(fdescrypt, uID);

    if(note_length == -1)
        return 0;

    read(fdescrypt, note_buffer, note_length);

    note_buffer[note_length] = 0;

    if(search_note(note_buffer, search_string))
        printf("%s", note_buffer);
    return 1;
}

int find_user_note(int fdescrypt, int userID){
    int note_uid = -1;
    unsigned char byte;
    int length;

    while(note_uid != userID){
        if(read(fdescrypt, &note_uid, 4) != 4)  
            return -1;
        if(read(fdescrypt, &byte, 1) != 1)
            return -1;

        byte = length = 0;
        while(byte != '\n'){
            if(read(fdescrypt, &byte, 1) != 1)
                return -1;
            length++;
        }
    }
    lseek(fdescrypt, length * -1, SEEK_CUR);

    printf("[DEBUG] find note length of %d for id %d\n", length, note_uid);
    return length;
}

int search_note(char *note, char *keyword){
    int i, keyword_length, match = 0;

    keyword_length = strlen(keyword);
    if(keyword_length == 0)
        return 1;
    
    for(i = 0; i < strlen(note); i++){
        if(note[i] == keyword[match])
            match++;
        else{
            if(note[i] == keyword[0])
                match = 1;
            else 
                match = 0;
        }
        if(match == keyword_length)
            return 1;
    }
    return 0;
}