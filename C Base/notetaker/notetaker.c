#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<hacking.h>

void usage(char *prog_name, char *file_name){
    printf("Usage: %s <data add to> %s\n", prog_name, file_name);
    exit(0);
}

void fatal(char *);
void *updatedMalloc(unsigned int);

int main(int argc, char *argv[]){
    int fdescrypt, userID;
    char *buffer, *datafile;

    buffer = (char *) updatedMalloc(100);
    datafile = (char *) updatedMalloc(20);

    strcpy(datafile, "/var/notes");

    if(argc < 2)
        usage(argv[0], datafile);

    strcpy(buffer, argv[1]);

    printf("[DEBUG] buffer @ %p \' %s \' \n", buffer, buffer);
    printf("[DEBUG] datafile @ %p \' %s \' \n", datafile, datafile);

    strncat(buffer, "\n", 2);

    fdescrypt = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(fdescrypt == -1)
        fatal("fatal in func main when openning file\n");

    printf("[DEBUG], file descryptor: %d\n", fdescrypt);

    userID = getuid();

    if(write(fdescrypt, &userID,4) == -1){
        fatal("In func main when writing userID to file");
    }
    write(fdescrypt, "\n", 1);

    if(write(fdescrypt, buffer, strlen(buffer)) == -1)
        fatal("fatal in func main when writing to file\n");
    write(fdescrypt, "\n", 1);

    if(close(fdescrypt) == -1)
        fatal("fatal in func main when closing the file\n");

    printf("note is saved\n");
    free(datafile);
    free(buffer);

    return 0;
}
