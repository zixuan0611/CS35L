#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    if (argc != 3)
    {
       fprintf(stderr, "Error! Incorrect number of arguments.");
       exit(1);
    }

    char* from = argv[1];
    char* to = argv[2];
    if (strlen(from) != strlen(to))
    {
       fprintf(stderr, "Error! from and to are not the same length.");
       exit(1);
    }
    int i;
    int j;
    for (i = 0; i < strlen(from); i++)
    {
        for(j = i + 1; j < strlen(from); j++)
        {
            if (from[i] == from[j])
            {
               fprintf(stderr, "Error! from has duplicate bytes.");
               exit(1);
            }
        }
    }
    
    char aixinnan = getchar();
    int match = 0;
    while (aixinnan != EOF)
    {
       int m;
       for(m = 0; m < strlen(from); m++)
       {
          if(aixinnan == from[m])
          {
             match = 1;
             putchar(to[m]);
             break;
          }
          else
          {
             match = 0;
          }
        }
          if(match == 0)
          {
            putchar(aixinnan);
          }
          aixinnan = getchar();
     }
     return 0;
}
