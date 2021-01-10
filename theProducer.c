#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <ctype.h>



#define BUFFER_MAX 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

char intCount[500];

void* fileRead(void* arg){
    pthread_mutex_lock(&mutex);
    FILE *input;
    input = fopen("/Users/janehu/OneDrive/Visual Studio Code/t.txt", "r");
    int y = getc(input);
    int x = 0;
    while(y != EOF){
        intCount[x] = y;
        printf("%c", intCount[x]);
        y = getc(input);
        x++;
    }
    pthread_mutex_unlock(&mutex);
    return 0;

}


void* character(void *arg){
    pthread_mutex_lock(&mutex);
    int x;
    for(x = 0;  x < strlen(intCount); x++){
        if(intCount[x] == ' '){

            intCount[x] = '^';
        }
        pthread_mutex_unlock(&mutex);

    }
    return 0;
}


void* toUpper(void *arg){
    pthread_mutex_lock(&mutex);
    int x;
    for(x = 0; x < 100; x++){

        intCount[x] = toupper(intCount[x]);
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

void* writer(void* arg)
{
    pthread_mutex_lock(&mutex);
    printf("\n");
    int x;
    for(x = 0; x < 100; x++)
    {
        printf("%c", intCount[x]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
    return 0;
}


int main(){
    pthread_t p1, p2, p3, p4;
    pthread_create(&p1, NULL, fileRead, NULL);
    pthread_create(&p2, NULL, character, NULL);
    pthread_create(&p3, NULL, toUpper, NULL);
    pthread_create(&p4, NULL, writer, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    return 0;
 } 
    