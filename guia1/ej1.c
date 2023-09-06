#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);

#define FILE 8
#define DIREC 4

/* struct dirent {
    ino_t          d_ino;       // Inode number
    off_t          d_off;       // Not an offset; see below
    unsigned short d_reclen;    // Length of this record
    unsigned char  d_type;      // Type of file; not supported
                                    by all filesystem types
    char           d_name[256]; // Null-terminated filename
}; */

void printTree(char * path, int index);


int main(int argc, char * argv[]) {
    printTree(argv[1], 0);
    return 0;
}

void printTree(char * path, int index) {
    DIR * directory = opendir(path);
    struct dirent * content;
    do {
        content = readdir(directory);
        if (content && content->d_name[0] != '.') {
            printf("%c", content->d_type == FILE ? 'f' : 'd');
            for (int i = 0; i <= index; i++)
                printf("\t");
            printf("%s\n", content->d_name);
            if (content->d_type == DIREC) {
                char aux[80];
                sprintf(aux, "%s/%s", path, content->d_name);
                printTree(aux, index + 1);
            }
        }
    } while (content != NULL);
    closedir(directory);
}
