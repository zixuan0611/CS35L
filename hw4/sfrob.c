#include <stdio.h>
#include <stdlib.h>

int frobcmp(const void *a, const void *b)
{
    const char *c_a = *(const char **) a;
    const char *c_b = *(const char **) b;
    int i = 0;
    while (c_a[i] != ' ' && c_b[i] != ' ')
    {
        if ((c_a[i] ^ 42) != (c_b[i] ^ 42))
        {
            if ((c_a[i] ^ 42) < (c_b[i] ^ 42))
                return -1;
            else if ((c_a[i] ^ 42) > (c_b[i] ^ 42))
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


int main(int argc, const char * argv[]) {
    char* word = (char*)malloc(sizeof(char));
    char** words = (char**)malloc(sizeof(char*));
    int word_n = 0;
    int words_n = 0;
    char aixinnan = ' ';
    do{
        aixinnan = getchar();
        if (ferror(stdin))
        {
            fprintf(stderr, "Error!");
            exit(1);
        }
        if (aixinnan == EOF)
            break;
        word_n++;
        word = realloc(word, word_n * sizeof(char));
        word[word_n - 1] = aixinnan;
        if (word == NULL)
        {
            fprintf(stderr, "Error!");
            exit(1);
        }
        if (aixinnan == ' ')
        {
            words_n++;
            words = realloc(words, words_n * sizeof(char*));
            words[words_n-1] = word;
            if (words == NULL)
            {
                fprintf(stderr, "Error!");
                exit(1);
            }
            word_n = 0;
            word = (char*)malloc(sizeof(char));
        }
    }while (!ferror(stdin) && !feof(stdin));
    
    if (word_n != 0)
    {
        word_n++;
        word = realloc(word, word_n * sizeof(char));
        word[word_n - 1] = ' ';
        if (word == NULL)
        {
            fprintf(stderr, "Error!");
            exit(1);
        }
        words_n++;
        words = realloc(words, words_n *sizeof(char*));
        words[words_n - 1] = word;
        if (words == NULL)
        {
            fprintf(stderr, "Error!");
            exit(1);
        }
        word_n = 0;
        word = (char*)malloc(sizeof(char));
    }
    
    qsort(words, words_n, sizeof(char*), frobcmp);
    
    if (words_n == 0)
    {
        return 0;
    }
    
    for (int i = 0; i < words_n; i++)
    {
        int j = 0;
        while (words[i][j] != ' ')
        {
            putchar(words[i][j]);
            if (ferror(stdout))
            {
                fprintf(stderr, "Error!");
            }
            j++;
        }
        putchar(' ');
    }
    
    free(word);
    for (int i = 0; i < words_n; i++)
    {
        free(words[i]);
    }
    free(words);
    
    return 0;
}

