#include "mycat.h"

void end(const char *msg) {
   perror(msg);
   exit(1); 
}

void read(char *filename) {
    FILE *f = fopen(filename,"rb");
    if (f == NULL) end("File opening failed\n");
    
   
    char buffer[BUFSIZ];   
    size_t bytes_read;

    while ((bytes_read = fread(buffer,1,sizeof(buffer),f)) > 0) {
        fwrite(buffer,1,bytes_read,stdout);    
    }  
        
    if (ferror(f)) {
        end("File read error");
    }
 
    fclose(f);
}


int main(int argc, char **argv) {
    if (argc != 2) end("Usage: ./mycat [FILE]");
    read(argv[1]);
    return 0;
}
