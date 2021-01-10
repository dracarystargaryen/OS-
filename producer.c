#include <stdio.h>
#include <string.h>


int main(){
    int x;
    char c;

//This reads the file input  
FILE *input = fopen("/Users/janehu/OneDrive/Visual Studio Code/producerText.txt", "r");
if(!input)
{
    printf("There is a problem opening the file.");
    return 0;
    }

//This reads file output
FILE  *output = fopen("testout.txt","w");
if(!output){

    printf("There is a problem writing into the file.");
    return 0;
    }

//Converts ASCII to binary
  while (!feof(input)) {
                //
                fread(&c, sizeof(c), 1, input);
                x = c;
                fwrite(&x, sizeof(int), 1, output);
        }


fclose(input);
fclose(output);
return 0;

}


