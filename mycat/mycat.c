    #include "mycat.h"

    void end(const char *msg) 
    {
    fprintf(stderr,msg);
    puts("");
    exit(1); 
    }

    void myread(char *filename) {
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

    int toscreen(void) {
        ssize_t nread;
        char buffer[4096];
        while (true) {
            nread = read(0,buffer,sizeof(buffer));
            if (nread == -1) return -1;
            if (nread == 0) break;
            write(1,buffer,nread);
        }
        return 0;
    }

    int main(int argc, char **argv) {
        if (argc > 2) end("Usage: ./mycat [FILE] or ./mycat");
        if (argc == 1) toscreen();
        else myread(argv[1]);
        return 0;
    }
