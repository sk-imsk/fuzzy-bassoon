#include <stdio.h>
#include <string.h>
#include "crypt.h"
#include <stdlib.h>
#include <errno.h>


#define program_name "test"
#pragma GCC poison sprintf




int main (int argc, const char** argv){
    int command_size = 0;
    char command[100];
    char command_[20];
    int * tmp = malloc(sizeof(int));
    struct crypt_items * crypt = malloc(sizeof(struct crypt_items));
    if (!tmp || !crypt){
        goto error;
        return 69;
    }
    memset(crypt, 0, sizeof(struct crypt_items));
    FILE *fptr;
    
    
    crypt->random = arc4random_uniform(10000);
    printf("Hello what is your string?\n");
    scanf("%99s", crypt->string);
    printf("\n which algorithem do you want \n 1 = sha512\n2=sha384\n3=sha256\n");
    scanf("%i",tmp);
    switch (*tmp){
        case 1 :{
            crypt->which = SHA_512;
            strcpy(command_, "/sbin/sha512\0");
            break;
        }case 2:{
            crypt->which = SHA_384;
            strcpy(command_, "/sbin/sha384\0");
            break;
        }case 3:{
            crypt->which = SHA_256;
            strcpy(command_, "/sbin/sha256\0");
            break;
        }default:{
            return -EINVAL;}
    }
    free(tmp);
    command_size = snprintf(command, 100,"%s -s \"%s\"",command_, crypt->string);
    if (command_size > 99 || command_size < 0){
        goto error;
    }
    fptr =  popen(command,"r");
    if (fptr == NULL){
        goto error;
    }
    while(fgets(crypt->output, sizeof(crypt->output), fptr) != NULL){
        if (fptr == NULL){
            goto error;
            break;
        }
    }
    
    printf("\n %s ",crypt->output );
    for (int i = 0; i < 199; i++){
        crypt->output[i] = '\0';
    }
    free (crypt);
    return 0;

    error:
    if (crypt){
        free(crypt);}
    free(tmp);
    printf("\n Sorry! a error occured\n");
    perror("error");
    return 1;
    
}
