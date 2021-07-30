#include<stdio.h>
#include<string.h>
#include"function.h"
#include<stdlib.h>
#include<dirent.h>
int getline(FILE *fp, char *line) {
    char ch;
    int i = 0;
    while(fread(&ch, sizeof(char), 1, fp)) {
        if(ch != '\n')
            line[i++] = ch;
        else if (ch == '\n') {
            line[i] = '\0';
            return i + 1;
        }
    }
    line[i] = '\0';
    return i;
}
char *uppertolower(char *word) {
    for(int i = 0; i < strlen(word); i++) {
        if(word[i] >= 65 && word[i] <= 90) {
            word[i] += 32;
        }
    }
    return word;
}
int search(char *word, char *line, int casesen, int wordc) {
    int i = 0, j = 0;
    char temp3[strlen(word) - 2];// removing ^ and $
    while(word[i] != '\0') {
        if(word[i] != '^' && word[i] != '$')
            temp3[j++] = word[i];
        i++;
    }
    if(casesen == 0 && wordc == 0) {
        if(word[i] == '^' && word[strlen(word) - 1] != '$') {
            i++;
            for(i = 1; i < strlen(word); i++) {
                if(word[i] == line[j]) {
                    j++;
                    if(j == strlen(word) - 1)
                        return 1;
                }
                else
                    return 0;
            }
        }
        else if(word[strlen(word) - 1] == '$' && word[0] != '^') {
            i = strlen(word) - 2;
            for(j = strlen(line) - 1; j >= 0; j--) {
                if(line[j] == word[i]) {
                    i--;
                    if(i == -1)
                        return 1;
                }
                else
                    return 0;
            }
        }
        else if(word[0] != '^' && word[strlen(word) - 1] != '$') {
            if(strstr(line, word))
                return 1;
            else
                return 0;
        }
        else if(word[0] == '^' && word[strlen(word) - 1] == '$') {
            if(strcmp(temp3, line) == 0)
                return 1;
            else
                return 0;
        }
    }
    char temp1[strlen(word)], line1[1000], temp2[strlen(word) - 1];
    strcpy(temp1, word);//copying word
    strcpy(line1, line);
    i = 1, j = 0;
    while(word[i] != '\0')
        temp2[j++] = word[i++];//removing ^
    temp2[j] = '\0';
    i = j = 0;
    if(casesen == 1 && wordc == 0) {
        uppertolower(temp1);// case sensitive
        uppertolower(line1);
        uppertolower(temp3);
        if(temp1[0] != '^' && word[strlen(word) - 1] != '$') {
            if(strstr(line1, temp1))
                return 1;
            else
                return 0;
        }
        else if(temp1[i] == '^' && temp1[strlen(temp1) - 1] != '$') {
            i++;
            for(i = 1; i < strlen(word); i++) {
                if(temp1[i] == line1[j]) {
                    j++;
                    if(j == strlen(word) - 1)
                        return 1;
                }
                else
                    return 0;
            }
        }
        else if(temp1[strlen(temp1) - 1] == '$' && temp1[0] != '^') {
            i = strlen(temp1) - 2;
            for(j = strlen(line1) - 1; j >= 0; j--) {
                if(line1[j] == temp1[i]) {
                    i--;
                    if(i == -1)
                        return 1;
                }
                else
                    return 0;
            }
        }
        else if(word[0] == '^' && word[strlen(word) - 1] == '$') {
            if(strcmp(temp3, line1) == 0)
                return 1;
            else
                return 0;
        }
    }
    if(casesen == 0 && wordc == 1) {
        if(word[0] != '^' && word[strlen(word) - 1] != '$') {
            for(i = 0; i < strlen(line); i++) {
                if(word[j] == line[i]) {
                    j++;
                    if(j == strlen(word) - 1) {
                        if(line[++i] == '\n' || line[++i] == ' ' || line[i] == '\n')
                            return 1;
                        else
                            return 0;
                    }
                }
                else
                    j = 0;
            }
        }
        else if(word[0] == '^' && word[strlen(word) - 1] != '$') {
            for(j = 0; j < strlen(temp2); j++) {
                if(temp2[j] != line[j]) {
                    return 0;
                }
            }
            if(line[j] == '\0' || line[j] == ' ' || line[j] == '\n')
                return 1;
            else
                return 0;
        }
        else if(word[strlen(word) - 1] == '$' && word[0] != '^') {
            i = strlen(word) - 2;
            for(j = strlen(line) - 1; j >= 0; j--) {
                if(word[i] != line[j])
                    return 0;
                else {
                    i--;
                    if(i == -1) {
                        if(line[j - 1] == ' ')
                            return 1;
                        else
                            return 0;
                    }
                }
            }
        }
        else if(word[0] == '^' && word[strlen(word) - 1] == '$') {
            if(strcmp(temp3, line) == 0)
                return 1;
            else
                return 0;
        }
    }
    if(casesen && wordc) {
        uppertolower(line1);
        uppertolower(temp1);
        uppertolower(temp2);
        uppertolower(temp3);
        i = 0, j = 0;
        if(word[0] != '^' && word[strlen(word) - 1] != '$') {
            for(i = 0; i < strlen(line1); i++) {
                if(temp1[j] == line1[i]) {
                    j++;
                    if(j == strlen(temp1) - 1) {
                        if(line1[++i] == '\n' || line1[++i] == ' ' || line1[i] == '\0')
                            return 1;
                        else
                            return 0;
                    }
                }
                else
                    j = 0;
            }
        }
        else if(word[0] == '^' && word[strlen(word) - 1] != '$') {
            for(i = 0; i < strlen(temp2); i++) {
                if(temp2[i] != line1[i])
                    return 0;
            }
            if(line1[i] == '\0' || line1[i] == ' ' || line1[i] == '\n')
                return 1;
            else
                return 0;
        }
        else if(word[strlen(word) - 1] == '$' && word[0] != '^') {
            i = strlen(temp1) - 2;
            for(j = strlen(line1) - 1; j >= 0; j--) {
                if(temp1[i] != line1[j])
                    return 0;
                else {
                    i--;
                    if(i == -1) {
                        if(line1[j - 1] == ' ')
                            return 1;
                        else
                            return 0;
                    }
                }
            }
        }
        else if(word[0] == '^' && word[strlen(word) - 1] == '$') {
            if(strcmp(temp3, line) == 0)
                return 1;
            else
                return 0;
        }
    }
    return 0;
}
void o_flag(char *word, char *line, int casesen) {
    int i, j = 0;
    char word1[1000];
    while(word[i] != '\0') {
        if(word[i] != '^' && word[i] != '$')
            word1[j++] = word[i];
        i++;
    }
    int k = strlen(word1);
    char *temp2 = (char *)malloc(sizeof(char) * strlen(word1));
    if(casesen) {
        j = i = 0;
        while(line[i] != '\0') {
            if((word1[j] == line[i]) || (word1[j] == line[i] - 32) || (word1[j] == line[i] + 32)) {
                temp2[j] = line[i];
                j++;
                if(j == k)
                    break;
            }
            else
                j = 0;
            i++;
        }
    }
    else if(!casesen) {
        j = i = 0;
        while(line[i] != '\0') {
            if(word1[j] == line[i]) {
                temp2[j] = line[i];
                j++;
                if(j == k)
                    break;
            }
            else
                j = 0;
            i++;
        }
    }
    temp2[j] = '\0';
    printf("%s\n", temp2);
    return;
}
char* f_flag(char *temp) {
    int i, j = 0;
    char *ch = (char *)malloc(sizeof(char) * 10);
    if(temp[strlen(temp) - 1] == 'f')
        ch[0] = '\0';
    else {
        while(temp[i] != '\0') {
            if(temp[i] == 'f') {
                while(temp[i] != '\0') {
                    i++;
                    ch[j] = temp[i];
                    j++;
                }
            }
            else
                i++;
        }
    }
    ch[j] = '\0';
    return ch;
}
int isfile(char *file) {
    FILE *fp = fopen(file, "r");
    if(fp != NULL) {
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}
int iscommand(char *s) {
    return s[0] == '-';
}
void printversion() {
    printf("grep (GNU GREP) 3.4\n");
    printf("Copyright (C) 2020 Free Software Foundation, Inc.\n");
    printf("This is a free Software: you are free to change and redistribute it\n");
    printf("There is no WARRANTY, to the extent permitted by law.\n\n");
    return;
    }
void print_help() {
    printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
    printf("Search for PATTERNS in each FILE.\n");
    printf("Example: grep -i 'hello world' menu.h main.c\n");
    printf("PATTERNS can contain multiple patterns separated by newlines.\n\n");

    printf("Pattern selection and interpretation:\n");
    printf("\t-E, --extended-regexp     PATTERNS are extended regular expressions\n");
    printf("\t-F, --fixed-strings       PATTERNS are strings\n");
    printf("\t-G, --basic-regexp        PATTERNS are basic regular expressions\n");
    printf("\t-P, --perl-regexp         PATTERNS are Perl regular expressions\n");
    printf("\t-e, --regexp=PATTERNS     use PATTERNS for matching\n");
    printf("\t-f, --file=FILE           take PATTERNS from FILE\n");
    printf("\t-i, --ignore-case         ignore case distinctions\n");
    printf("\t-w, --word-regexp         match only whole words\n");
    printf("\t-x, --line-regexp         match only whole lines\n");
    printf("\t-z, --null-data           a data line ends in 0 byte, not newline\n\n");

    printf("Miscellaneous:\n");
    printf("\t-s, --no-messages         suppress error messages\n");
    printf("\t-v, --invert-match        select non-matching lines\n");
    printf("\t-V, --version             display version information and exit\n");
    printf("\t--help                    display this help text and exit\n\n");

    printf("Output control:\n");
    printf("\t-m, --max-count=NUM       stop after NUM selected lines\n");
    printf("\t-b, --byte-offset         print the byte offset with output lines\n");
    printf("\t-n, --line-number         print line number with output lines\n");
    printf("\t--line-buffered           flush output on every line\n");
    printf("\t-H, --with-filename       print file name with output lines\n");
    printf("\t-h, --no-filename         suppress the file name prefix on output\n");
    printf("\t\t--label=LABEL           use LABEL as the standard input file name prefix\n");
    printf("\t-o, --only-matching       show only nonempty parts of lines that match\n");
    printf("\t-q, --quiet, --silent     suppress all normal output\n");
    printf("\t--binary-files=TYPE       assume that binary files are TYPE;\n");
    printf("\t\t\t\tTYPE is 'binary', 'text', or 'without-match'\n");
    printf("\t-a, --text                equivalent to --binary-files=text\n");
    printf("\t-I                        equivalent to --binary-files=without-match\n");
    printf("\t-d, --directories=ACTION  how to handle directories;\n");
    printf("	                        ACTION is 'read', 'recurse', or 'skip'\n");
    printf("\t-D, --devices=ACTION      how to handle devices, FIFOs and sockets;\n");
    printf("	                        ACTION is 'read' or 'skip'\n");
    printf("\t-r, --recursive           like --directories=recurse\n");
    printf("\t-R, --dereference-recursive  likewise, but follow all symlinks\n");
    printf("\t--include=GLOB            search only files that match GLOB (a file pattern)\n");
    printf("\t--exclude=GLOB            skip files and directories matching GLOB\n");
    printf("\t--exclude-from=FILE       skip files matching any file pattern from FILE\n");
    printf("\t--exclude-dir=GLOB        skip directories that match GLOB\n");
    printf("\t-L, --files-without-match print only names of FILEs with no selected lines\n");
    printf("\t-l, --files-with-matches  print only names of FILEs with selected lines\n");
    printf("\t-c, --count               print only a count of selected lines per FILE\n");
    printf("\t-T, --initial-tab         make tabs line up (if needed)\n");
    printf("\t-Z, --null                print 0 byte after FILE name\n\n");
    printf("Context control:\n");
    printf("\t-B, --before-context=NUM  print NUM lines of leading context\n");
    printf("\t-A, --after-context=NUM   print NUM lines of trailing context\n");
    printf("\t-C, --context=NUM         print NUM lines of output context\n");
    printf("\t-NUM                      same as --context=NUM\n");
    printf("\t--color[=WHEN],\n");
    printf("\t--colour[=WHEN]           use markers to highlight the matching strings;\n");
    printf("\t		                    WHEN is 'always', 'never', or 'auto'\n");
    printf("\t-U, --binary              do not strip CR characters at EOL (MSDOS/Windows)\n\n");
    printf("When FILE is '-', read standard input.  With no FILE, read '.' if\n");
    printf("recursive, '-' otherwise.  With fewer than two FILEs, assume -h.\n");
    printf("Exit status is 0 if any line (or file if -L) is selected, 1 otherwise;\n");
    printf("if any error occurs and -q is not given, the exit status is 2.\n\n");
    return;
    }
int isdirectory(char *path) {
    DIR *d = opendir(path);
    if(d != NULL)
        return 1;
    return 0;
}

