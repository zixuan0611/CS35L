#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
int frobcmp(const void *a, const void *b);
char decrypt(char c);

static int caseFlag = 0;

int frobcmp(const void *a, const void *b)
{
    const char *c_a = *(const char **) a;
    const char *c_b = *(const char **) b;
    int i = 0;
    while (c_a[i] != ' ' && c_b[i] != ' ')
    {
        if (decrypt(c_a[i]) != decrypt(c_b[i]))
        {
            if (decrypt(c_a[i]) < decrypt(c_b[i]))
                return -1;
            else if (decrypt(c_a[i]) > decrypt(c_b[i]))
                return 1;
        }
        else
        {
            i++;
        }
    }
    if (c_a[i] == ' ' && c_b[i] != ' ')
        return -1;
    if (c_a[i] != ' ' && c_b[i] == ' ')
        return 1;
        
        return 0;
}

char decrypt(char c)
{
     if (caseFlag == 0)
     {   
        return c^42;
     }
     else
     {
        char u = c ^ 42;
        if (u == EOF || u >= CHAR_MIN || u <= CHAR_MAX)
        {
           u = toupper((unsigned char)u);
           return u;
        }
        else
        {
           fprintf(stderr, "Error1!");
           exit(1);
        }
     }
}
int main(int argc, char * argv[]) {
    struct stat status;
    if (argc == 1)
    {
       caseFlag = 0;
    }
    else if (argc == 2)
    {
       char* cFlag = argv[1];
       if (cFlag[0] == '-' && cFlag[1] == 'f')
       {
          caseFlag = 1;
       }
       else
       {
           fprintf(stderr, "Error!");
           exit(1);
       }
    }
    else
    {
       fprintf(stderr, "Error2!");
       exit(1);
    }
    if (fstat(0, &status) < 0)
    {
       fprintf(stderr, "Error3!");
       exit(1);
    }
    int size;
    if (S_ISREG(status.st_mode))
    {
        size = status.st_size;
    }
    else
    {
        size = 0;
    }
    char* word = (char*)malloc(size * sizeof(char));
    char** words = (char**)malloc(sizeof(char*));
    int word_n = 0;
    int words_n = 0;
    char aixinnan = ' ';
    while (read(0, &aixinnan, sizeof(char)) > 0)
    {
        if (word_n >= size)
        {
           size++;
           word = realloc(word, size * sizeof(char));
           if (word == NULL)
           {
              fprintf(stderr, "Error5!");
              exit(1);
           }
         }
         word_n++;
         word[word_n-1] = aixinnan;
    }
    if (word[word_n-1] != ' ')
    {
        size++;
        word_n++;
        word = realloc(word, size * sizeof(char));
        if (word == NULL)
        {
            fprintf(stderr, "Error6!");
            exit(1);
        }
        word[word_n-1] = ' ';
    }
    
    int s = 0;
    int p = 0;
    for (s = 0; s < word_n; s++)
    {
        if (word[s] == ' ')
        {
           words_n++;
           words = realloc(words, words_n * sizeof(char*));
           if (words == NULL)
           {
            fprintf(stderr, "Error7!");
            exit(1);
           }
           words[words_n-1] = word + p;
           p = s + 1;
         }
     }

    qsort(words, words_n, sizeof(char*), frobcmp);
    
    if (words_n == 0)
    {
        return 0;
    }
    int i;
    for (i = 0; i < words_n; i++)
    {
        int j = 0;
        while (words[i][j] != ' ')
        {
            if (write(1, &words[i][j], 1) < 1)
            {
                fprintf(stderr, "Error8!");
                exit(1);
            }
            j++;
        }
        if (words[i][j] == ' ')
        {
           if (write(1, &words[i][j], 1) < 1)
            {
                fprintf(stderr, "Error9!");
                exit(1);
            }
        }
    }
    
    free(word);
    free(words);
    return 0;
}

