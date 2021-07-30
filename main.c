// Name : Tarun Radheshyam Tapadiya
// Div : 2
// MIS : 111903112
// Project Name : Grep
#include <stdio.h>
#include <stdlib.h>
#include"function.h"
#include"list.h"
#include<unistd.h>
#include<ctype.h>
int main(int argc, char* argv[]) {
    FILE *fp, *fp1;
    char line[1024], word[1024], d_name[1000], line1[1000];
    char *str, *str1, *str2;
    int iflag = 0, cflag = 0, vflag = 0, wflag = 0, oflag = 0, count = 0, wordc = 0, casesen = 0, nflag = 0, count1 = 0, rflag = 0;
    int choice = 0, lflag = 0, i = 1, flag = 0, j = 0, qflag = 0, mflag = 0, Hflag = 0, hflag = 0, len = 0, bflag = 0, dflag = 0;
    int print_flag = 0, fflag = 0, line_no = 0, file_flag = 0, line_no1 = 0, count2 = 0, max_count;
    if(strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0) {
        printversion();
        return 0;
    }
    if(strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }
    while((choice = getopt(argc, argv, ":ivHhowcnbflm:rq")) != -1) {
        switch(choice) {
            case 'i'://case insensitive search
                iflag = 1;
                casesen = 1;
                break;
            case 'v'://invert match
                vflag = 1;
                break;
            case 'c'://count matched lines
                cflag = 1;
                break;
            case 'w'://search for word
                wflag = 1;
                wordc = 1;
                break;
            case 'o'://printing matched word
                oflag = 1;
                break;
            case 'n'://printing line numbers and line with matched pattern
                nflag = 1;
                break;
            case 'r'://recursively searching for patterns in all files
                rflag = 1;
                break;
            case 'l'://printing file name if pattern is found
                lflag = 1;
                break;
            case 'q'://exiting from program
                qflag = 1;
                break;
            case 'm':
                mflag = 1;
                max_count = atoi(optarg);
                if(max_count < 0)
                    max_count = 0;
                if((max_count >= 'a' && max_count <= 'z') || (max_count >= 'A' && max_count <= 'Z')) {
                    printf("grep : invalid max count\n");
                    exit(0);
                }
                char *temp = argv[1];// considering argv[1] contains all the commands
                char *x = &(temp[strlen(temp) - 1]);
                if(atoi(x) == 0) {
                    printf("grep : invalid max count\n");
                    exit(0);
                }
                break;
            case 'H'://printing file name with output
                Hflag = 1;
                if(hflag)
                    hflag = 0;
                break;
            case 'h'://no filename
                hflag = 1;
                if(Hflag)
                    Hflag = 0;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'f':
                fflag = 1;
                break;
            default:
                flag = 1;
                break;
        }
    }
    list l;
    init(&l);
    if(choice == -1)
        flag = 1;
    if(qflag) {  // If qflag comes, exit from the program
        exit(0);
    }
    word[0] = '\0';
    while(i < argc) {
        if(isfile(argv[i]) && !iscommand(argv[i])) {
            if(iscommand(argv[i - 1])) {
                strcpy(word, argv[i - 1]);
            }
            add(&l, argv[i]);
            j++;
        }
        else if(!isfile(argv[i]) && !iscommand(argv[i]))
            if(isdirectory(argv[i])) {
                if(rflag)
                    listing(argv[i], &l);// listing all the readable files from directory and adding into linked list
                dflag = 1;
                strcpy(d_name, argv[i]);
            }
            else if(fflag)
                add(&l, argv[i]);
            else {
                if(word[0] == '\0')
                    strcpy(word, argv[i]);
                else
                    add(&l, argv[i]);
            }
        else if(iscommand(argv[i])) {
            flag = 0;
            if(strstr((argv[i]), "f")) {
                str2 = f_flag(argv[i]);
                if(str2[0] != '\0') {
                    printf("grep: %s: No Such File or Directory", str2);
                    exit(0);
                }
                else {
                    add(&l, argv[i + 1]);
                    i++;
                }
            }
        }

        i++;
    }
    if(fflag) {
        if(argc < 4)
            exit(0);
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        str1 = remov(&l);
        fp1 = fopen(str1, "r");
        if(fp1 == NULL) {
            printf("grep: %s: No Such File or Directory\n", str1);
            return 0;
        }
        while(getline(fp1, line1))
            line_no1++;
        fclose(fp1);
        int k = max_count;
        while(!isempty(l)) {
                str = remov(&l);
                fp = fopen(str, "r");
                if(fp == NULL) {
                    printf("grep: %s: No Such File or Directory\n", str);
                    continue;
                }
                max_count = k;
                len = 0;
                file_flag = 0;
                line_no = 0;
                while(getline(fp, line)) {
                    fp1 = fopen(str1, "r");
                    line_no++;
                    while(getline(fp1, line1)) {
                        count = 0;
                        if(search(line1, line, casesen, wordc) && !vflag) {
                            if(lflag) {
                                if(!file_flag)//to check if filename is already printed or not
                                    printf("%s\n", str);
                                file_flag = 1;
                                break;
                            }
                            if(Hflag && !cflag) {
                                if(!print_flag)
                                    printf("%s:", str);
                            }

                            count++;
                            if(!print_flag)
                                max_count--;
                            if(!cflag && nflag)
                                if(!print_flag)// this is to indicate that the line is already been printed or matched earlier
                                    printf("%d:", line_no);
                            if(!cflag && bflag)
                                if(!print_flag)
                                    printf("%d:", len);
                            if(!cflag && !oflag) {
                                if(!print_flag) {
                                    puts(line);
                                    print_flag = 1;
                                }
                            }
                            if(!cflag && oflag)
                                printf("%s\n", line1);
                        }
                        if(vflag && !search(line1, line, casesen, wordc))
                            count2++;
                    }
                    if(vflag) {
                        if(count2 == line_no1) {
                            if((!cflag && !lflag) && oflag)//Exit because o and v are compliment to each other
                                exit(0);
                            if(lflag) {
                                if(!file_flag)
                                    printf("%s\n", str);
                                file_flag = 1;
                                break;
                            }
                            if(Hflag && !cflag) {
                                if(!print_flag)
                                    printf("%s:", str);
                            }
                            count++;
                            if(!print_flag)
                                max_count--;
                            if(!cflag && nflag)
                                if(!print_flag)
                                    printf("%d:", line_no);
                            if(!cflag && bflag)
                                if(!print_flag)
                                    printf("%d:", len);
                            if(!cflag && !oflag) {
                                if(!print_flag) {
                                    puts(line);
                                    print_flag = 1;
                                }
                            }
                        }
                    }
                    count2 = 0;
                    len = len + strlen(line) + 1;
                    print_flag = 0;
                    count1 += count;
                    fclose(fp1);
                    if(mflag) {
                        if(!max_count) {
                            if(cflag && !lflag) {
                                if(Hflag)
                                    printf("%s:", str);
                                printf("%d\n", count1);
                            }
                            break;
                            //exit(0);
                        }
                    }
                }
                if(cflag && !lflag) {
                    if(Hflag)
                        printf("%s:", str);
                    printf("%d\n", count1);
                }
                fclose(fp);
            }

            return 0;
        }
    if(mflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        int k = max_count;
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            line_no1 = line_no = count = count1 = count2 = len = 0;
            max_count = k;
            while(getline(fp, line)) {
                line_no++;
                if(search(word, line, casesen, wordc) && !vflag) {
                    if(lflag) {
                        printf("%s\n", str);
                        break;
                    }
                    count++;
                    max_count--;
                    if(Hflag && !cflag)
                        printf("%s:", str);
                    if(!cflag && nflag)
                        printf("%d:", line_no);
                    if(!cflag && bflag) {
                        printf("%d:", len);
                    }
                    if(!cflag) {
                        if(oflag) {
                            o_flag(word, line, casesen);
                        }
                        else
                            printf("%s\n", line);
                    }
                }
                else if(!search(word, line, casesen, wordc) && vflag) {
                    if(!cflag && !lflag && oflag)
                        exit(0);
                    if(lflag) {
                        printf("%s\n", str);
                        break;
                    }
                    count++;
                    max_count--;
                    if(!cflag && Hflag)
                        printf("%s:", str);
                    if(!cflag && nflag)
                            printf("%d:", line_no);
                    if(!cflag && bflag) {
                        printf("%d:", len);
                    }
                    if(!cflag)
                        printf("%s\n", line);
                }
                len = len + strlen(line) + 1;
                if(!max_count) {
                    if(cflag) {
                        if(Hflag)
                            printf("%s:", str);
                        printf("%d\n", count);
                    }
                    //exit(0);
                    break;
                }
            }
            fclose(fp);
            count = line_no = len = 0;
        }
        return 0;
    }
    if(rflag) {
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            len = count = count1 = 0;
            while(getline(fp, line)) {
                count++;
                if(search(word, line, casesen, wordc) && !vflag) {
                    if(lflag) {
                        printf("%s\n", str);
                        break;
                    }
                    count1++;
                    if(!hflag && !cflag)
                        printf("%s:", str);
                    if(!cflag && nflag)
                        printf("%d:", count);
                    if(!cflag && bflag) {
                        printf("%d:", len);
                    }
                    if(!cflag) {
                        if(oflag)
                            o_flag(word, line, casesen);
                        else
                            printf("%s\n", line);
                    }
                }
                else if(search(word, line, casesen, wordc) == 0 && vflag) {
                    if(oflag && (!cflag && !lflag)) // Exiting if c and l flag are not present because -o prints word not line
                        exit(0);
                    else {
                        if(lflag) {
                            printf("%s\n", str);
                            break;
                        }
                        count1++;
                        if(!hflag && !cflag)
                            printf("%s:", str);
                        if(!cflag && nflag)
                            printf("%d:", count);
                        if(!cflag && bflag) {
                            printf("%d:", len);
                        }
                        if(!cflag)
                            printf("%s\n", line);
                    }
                }
                len = len + strlen(line) + 1;
            }
            if(cflag) {
                if(!hflag)
                    printf("%s:", str);
                printf("%d\n", count1);
            }
            fclose(fp);
            count = count1 = 0;
            len = 0;
        }
        return 0;
    }

    if(lflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc) && !vflag) {
                    printf("%s\n", str);
                    break;
                }
                else if(search(word, line, casesen, wordc) == 0 && vflag) {
                    printf("%s\n", str);
                    break;
                }
            }
            fclose(fp);
        }
        return 0;
    }
    if(cflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            count1 = 0;
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc) && !vflag)
                    count1++;
                else if(vflag && !search(word, line, casesen, wordc)) {
                    if(oflag) {
                        printf("%d\n", count1);
                        exit(0);
                    }
                    count1++;
                }
            }
            if(Hflag)
                printf("%s:", str);
            printf("%d\n", count1);
            fclose(fp);
        }
        return 0;
    }
    if(vflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        if(oflag)
            exit(0);
        line_no = len = 0;
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            line_no = len = 0;
            while(getline(fp, line)) {
                line_no++;
                if(search(word, line, casesen, wordc) == 0) {
                    if(Hflag)
                        printf("%s:", str);
                    if(nflag)
                        printf("%d:", line_no);
                    if(bflag)
                        printf("%d:", len);
                    printf("%s\n", line);
                }
                len = len + strlen(line) + 1;
            }
            fclose(fp);
        }
        return 0;
    }
    if(nflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            line_no = len = 0;
            while(getline(fp, line)) {
                line_no++;
                if(search(word, line, casesen, wordc)) {
                    if(Hflag)
                        printf("%s:", str);
                    printf("%d:", line_no);
                    if(bflag) {
                        printf("%d:", len);
                    }
                    if(!oflag)
                        printf("%s\n", line);
                    if(oflag)
                        o_flag(word, line, casesen);
                }
                len = len + strlen(line) + 1;
            }
            fclose(fp);
        }
        return 0;
    }
    if(bflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        count = 0;
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            count = 0;
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc)) {
                    if(Hflag)
                        printf("%s:", str);
                    printf("%d:", count);
                    if(oflag)
                        o_flag(word, line, casesen);
                    if(!oflag)
                        printf("%s\n", line);
                }
                count = count + strlen(line) + 1;
            }
            fclose(fp);
        }
        return 0;
    }
    if(oflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc)) {
                    if(Hflag)
                        printf("%s:", str);
                    o_flag(word, line, casesen);
                }
            }
            fclose(fp);
        }
        return 0;
    }
    if(Hflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc)) {
                    printf("%s:", str);
                    puts(line);
                }
            }
            fclose(fp);
        }
        return 0;
    }
    if(hflag) {
         if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc))
                    printf("%s\n", line);
            }
        }
        return 0;
    }
    if(wflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc))
                    printf("%s\n", line);
            }
            fclose(fp);
        }
        return 0;
    }
    if(iflag) {
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("grep: %s: No Such File or Directory\n", str);
                continue;
            }
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc))
                    puts(line);
            }
            fclose(fp);
        }
        return 0;
    }
    if(flag) {//If no command is given like -l, -n etc;
        if(!rflag && dflag) {
            printf("grep: %s: Is a Directory\n", d_name);
            return 0;
        }
        while(!isempty(l)) {
            str = remov(&l);
            fp = fopen(str, "r");
            if(fp == NULL) {
                printf("%s: No Such File or Directory", str);
                continue;
            }
            while(getline(fp, line)) {
                if(search(word, line, casesen, wordc))
                    printf("%s\n", line);
            }
        }
        return 0;
    }
    return 0;
}
