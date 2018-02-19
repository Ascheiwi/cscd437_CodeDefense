/* 
 * File:   main.c
 * Author: Louis A. Sorensen
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void cleanBuffers(char *buf);
int strLength(char *str, int max);
int checkName(char *name, int bufSize);
int checkInt(char *numStr, int bufSize);

int main(void) 
{
    char fName[52], lName[52], numA[13], numB[13], in[51], out[51], pwd[51];
    int valA, valB;
    
    printf("Please enter a first name: ");
    fgets(fName, sizeof(fName), stdin);
    cleanBuffers(fName);
    while(checkName(fName, sizeof(fName)) == 0)
    {
        printf("Please enter a valid first name: ");
        fgets(fName, sizeof(fName), stdin);
        cleanBuffers(fName);
    }
    
    printf("Please enter a last name: ");
    fgets(lName, sizeof(lName), stdin);
    cleanBuffers(lName);
    while(checkName(lName, sizeof(lName)) == 0)
    {
        printf("Please enter a valid last name: ");
        fgets(lName, sizeof(lName), stdin);
        cleanBuffers(lName);
    }
    
    printf("Please enter first digit: ");
    fgets(numA, sizeof(numA), stdin);
    cleanBuffers(numA);  
    while(checkInt(numA, sizeof(numA)) == 0)
    {
        printf("Please enter a valid integer: ");
        fgets(numA, sizeof(numA), stdin);
        cleanBuffers(numA);  
    }   
    valA = strtol(numA, NULL, 10);
    
    printf("Please enter second digit: ");
    fgets(numB, sizeof(numB), stdin);
    cleanBuffers(numB);
    while(checkInt(numB, sizeof(numB)) == 0)
    {
        printf("Please enter a valid integer: ");
        fgets(numB, sizeof(numB), stdin);
        cleanBuffers(numB);  
    }
    valB = strtol(numB, NULL, 10);
    
    printf("Please enter input file: ");
    fgets(in, sizeof(in), stdin);
    cleanBuffers(in);
    
    printf("Please enter output file: ");
    fgets(out, sizeof(out), stdin);
    cleanBuffers(out);
    
    printf("Please enter a password: ");
    fgets(pwd, sizeof(pwd), stdin);
    cleanBuffers(pwd);
    
    printf("%s, %s. %d %d.\n", fName, lName, valA, valB);
    printf("Press ENTER key to close program\n");  
    getchar(); 
}

void cleanBuffers(char *buf)
{
    if(!strchr(buf, '\n'))
        while(fgetc(stdin) != '\n')/*Discard*/;
    else
        strtok(buf, "\n");
}

int strLength(char *str, int max)
{
    int size = 0, index = 0;
    while(str[index] != '\0' && index != max) size++, index++;
    return size;
}

int checkName(char *name, int bufSize)
{
    int index = 0;
    
    if(strLength(name, bufSize) > 50)
    {
        printf("Name exceeds 50 characters.\n");
        return 0;
    }
        
    while(name[index] != '\0' && index != bufSize)
    {
        if(!isalpha(name[index]))
        {
            printf("Invalid characters for name in input.\n");
            return 0;
        }
        index++;
    }
    return 1;
}

int checkInt(char *numStr, int bufSize)
{
    int index, size = strLength(numStr, bufSize);
    long long value;
    
    if(numStr[0] == '-')
        index = 1;
    else
        index = 0;
    
    while(numStr[index] != '\0' && index != bufSize)
    {
        if(!isdigit((int)numStr[index]))
        {
            printf("Invalid characters in input.\n");
            return 0;
        }
        index++;
    }
    
    if((!(size == 11 && numStr[0] != '-')) || (size < 11 && size > 0));
    else
    {
        printf("Integer out of range.\n");
        return 0;
    }
    
    value = strtoll(numStr, NULL, 10);
    
    if(value > INT_MAX || value < INT_MIN)
    {
        printf("Integer out of range.\n");
        return 0;
    }
    
    return 1;    
}