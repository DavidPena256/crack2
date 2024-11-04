#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hashText = md5(plaintext, strlen(plaintext));
    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    // Loop through the hash file, one line at a time.
    char line[1000];
    while(fgets(line, 1000, hashFile)){
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';

        if (!strcmp(hashText, line)){
            return hashText;
        }
    }
    fclose(hashFile);
    free(hashText);
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    FILE *dicFile = fopen(argv[2], "r");
    char line[1000];
    int count = 0;
    
    while(fgets(line, 1000, dicFile)){
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';

        char *hash = tryWord(line, argv[1]);
        if (hash){
            printf("%s %s\n", hash, line);
            count += 1;
            free(hash);
        }
    }

    fclose(dicFile);
    printf("%d hashes cracked!\n", count);
}
