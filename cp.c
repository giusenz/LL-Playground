/* fopen, fread and fwrite are not used on purpose */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int cp(char *src, char *dest) {    
    /* Open files. Destination file is created if needed */
    int ret = 0;

    int srcd = open(src,O_RDONLY);
    if (srcd == -1) {
        perror("Unable to open source file");
        return 1;
    }     
    int destd = open(dest,O_WRONLY|O_CREAT|O_TRUNC,0644);
    if (destd == -1) {
        perror("Unable to open destination file");
        ret = 1;
        goto close_source;
    }  
    
    /* Read and copy */
    char buffer[4096];
    ssize_t nread;
    while (1) {
        nread = read(srcd,buffer,sizeof(buffer));
        if (nread == -1) {
            perror("Unable to read from source file");
            ret = 1;
            goto close_both;
        }
        if (nread == 0) break;
        ssize_t written = write(destd,buffer,nread);
        if (written == -1) {
            perror("Unable to write on destination file");
            ret = 1;
            goto close_both;
        }
    }
    /* Close files */
    close_both:
        close(destd);
    close_source:
        close(srcd);
    
    return ret;
}

int main(int argc, char **argv) { 
    if (argc != 3) {
        fprintf(stderr,"./cp [SOURCE FILE PATH] [DESTINATION FILE PATH]\n");
        return 1;
    }
    return cp(argv[1],argv[2]);
}
