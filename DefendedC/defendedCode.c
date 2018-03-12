/* 
 * File: defendedCode.c
 * Team: NullPointerDejection
 * Authors: Louis A. Sorensen, Avery Scheiwiller, Devan Gifford
 * Compiled with: GNU MinGW-w64 6.3.0
 * Defends Against: Buffer overflow, files from outside program directory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "sha256.h"

void cleanBuffers(char *buf);
int checkName(char *name, int bufSize);
int checkInt(char *numStr, int bufSize);
FILE* checkFile(char *fileName, int bufSize, int inOut);
int checkPwd(char *pwd, int bufSize, char *salt, int saltSize, FILE *errFile);
int comparePwd(char *pwd, int bufSize, char *salt, int saltSize, unsigned char *savedHash,  FILE *errFile);
void hashPwd(char *pwd, int bufSize, unsigned char *hash);

int main(void) 
{
    char fName[52], lName[52], numA[13], numB[13], in[52], out[52], pwd[52];
    unsigned char savedHash[SHA256_BLOCK_SIZE];
    int valA, valB;
    FILE *input, *output;
    
    printf("Please enter a first name (Only alphabetic chars, length <= 50): ");
    fgets(fName, sizeof(fName), stdin);
    cleanBuffers(fName);
    while(checkName(fName, sizeof(fName)) == 0)
    {
        printf("Please enter a valid first name: ");
        fgets(fName, sizeof(fName), stdin);
        cleanBuffers(fName);
    }
    
    printf("Please enter a last name (Only alphabetic chars, length <= 50): ");
    fgets(lName, sizeof(lName), stdin);
    cleanBuffers(lName);
    while(checkName(lName, sizeof(lName)) == 0)
    {
        printf("Please enter a valid last name: ");
        fgets(lName, sizeof(lName), stdin);
        cleanBuffers(lName);
    }
    
    printf("Please enter first integer (Only digits ['-' ok at start], -2147483648 to 2147483647): ");
    fgets(numA, sizeof(numA), stdin);
    cleanBuffers(numA);  
    while(checkInt(numA, sizeof(numA)) == 0)
    {
        printf("Please enter a valid integer: ");
        fgets(numA, sizeof(numA), stdin);
        cleanBuffers(numA);  
    }   
    valA = strtol(numA, NULL, 10);
    
    printf("Please enter second integer (Only digits ['-' ok at start], -2147483648 to 2147483647): ");
    fgets(numB, sizeof(numB), stdin);
    cleanBuffers(numB);
    while(checkInt(numB, sizeof(numB)) == 0)
    {
        printf("Please enter a valid integer: ");
        fgets(numB, sizeof(numB), stdin);
        cleanBuffers(numB);  
    }
    valB = strtol(numB, NULL, 10);
    
    printf("Please enter input file (Must be in same directory as this program, <= 50 chars): ");
    fgets(in, sizeof(in), stdin);
    cleanBuffers(in);
    while((input = checkFile(in, sizeof(in), 0)) == NULL)
    {
        printf("Please enter a valid input file: ");
        fgets(in, sizeof(in), stdin);
        cleanBuffers(in); 
    }
    
    printf("Please enter output file (Must be in same directory as this program, <= 50 chars): ");
    fgets(out, sizeof(out), stdin);
    cleanBuffers(out);
    while((output = checkFile(out, sizeof(out), 1))== NULL)
    {
        printf("Please enter a valid output file: ");
        fgets(out, sizeof(out), stdin);
        cleanBuffers(out); 
    }
    
    printf("Please enter a password (length must be > 7 and < 51): ");
    fgets(pwd, sizeof(pwd), stdin);
    cleanBuffers(pwd);
    while(checkPwd(pwd, sizeof(pwd), fName, sizeof(fName), output) == 0)
    {
        printf("Please enter a password (length must be > 7 and < 51): ");
        fgets(pwd, sizeof(pwd), stdin);
        cleanBuffers(pwd);
    }
    
    printf("Please enter created password to continue: ");
    fgets(pwd, sizeof(pwd), stdin);
    cleanBuffers(pwd);
    while(comparePwd(pwd, sizeof(pwd), fName, sizeof(fName), savedHash, output) == 0)
    {
        printf("Wrong password. Please enter password to continue: ");
        fgets(pwd, sizeof(pwd), stdin);
        cleanBuffers(pwd);
    }
    
    long long sumNum = (long long) valA + valB;
    long long prodNum = (long long) valA * valB;
    
    char sum[256], prod[256];
    _ui64toa(sumNum, sum, 10);
    _ui64toa(prodNum, prod, 10);
    
    fprintf(output, "Name: %s, %s.\nSum: %s Product: %s\n", lName, fName, sum, prod);
    
    //Note: This used code from https://www.geeksforgeeks.org/c-program-copy-contents-one-file-another-file/
    char c = fgetc(input);
    while(c != EOF)
    {
        fputc(c, output);
        c = fgetc(input);
    }
    
    fclose(input);
    fclose(output);
    
    printf("Press ENTER key to close program\n");  
    getchar(); 
}

//Note: This used info/partial code from https://forum.pellesc.de/index.php?topic=6699.0
void cleanBuffers(char *buf)
{
    if(!strchr(buf, '\n'))
        while(fgetc(stdin) != '\n')/*Discard*/;
    else
        strtok(buf, "\n");
}

int checkName(char *name, int bufSize)
{
    int index = 0;
    
    if(strnlen(name, bufSize) > 50)
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
    int index, size = strnlen(numStr, bufSize);
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

//Note: a portion of this code was taken from https://wiki.sei.cmu.edu/confluence/display/c/FIO03-C.+Do+not+make+assumptions+about+fopen%28%29+and+file+creation
//and modified for use here.
FILE* checkFile(char *fileName, int bufSize, int inOut)
{
    FILE *file;
    char *par;
    
    if(strnlen(fileName, bufSize) > 50)
    {
        printf("Filename exceeds 50 characters.\n");
        file = NULL;
        return file;
    }
    
    if(strstr(fileName, "..") != NULL || strchr(fileName, '/') != NULL || strchr(fileName, '\\') != NULL )
    {
        printf("Invalid characters in filename. Please input filename in this directory only, no paths allowed.\n");
        file = NULL;
        return file;        
    }
    
    if(inOut == 0)
        par = "r";
    else
        par = "w";
    
<<<<<<< HEAD
    int res = fopen_s(&file, fileName, par);
=======
    errno_t res = fopen_s(&file, fileName, par);
>>>>>>> 8c0b72648b6657b26bc812e6b54783dac9ff0729
    if(res != 0)
    {
        file = NULL;
        printf("Invalid filename. File must be in the same directory as this program.\n");
        return file;
    }
    return file;
}

int checkPwd(char *pwd, int bufSize, char *salt, int saltSize, FILE *errFile)
{
    int length = strnlen(pwd, bufSize);
    
    if(length > 50 || length < 8 )
    {
        printf("Password length < 8 or > 50.\n");
        return 0;
    }
    else
    {
        FILE *pass;
        unsigned char hash[SHA256_BLOCK_SIZE], saltHash[SHA256_BLOCK_SIZE];
        int res = fopen_s(&pass, "password.txt", "w");
        if(res != 0)
        {
            pass = NULL;
            printf("Error accessing password.txt. Writing error to output file.");
            fprintf(errFile, "File error: %d", res);
            exit(0);
        }
        
        hashPwd(salt, saltSize, saltHash);
        char saltedPwd[bufSize + sizeof(saltHash)];
        strncpy(saltedPwd, pwd, bufSize);
        strncat(saltedPwd, (char *)saltHash, sizeof(saltHash));
        hashPwd(saltedPwd, bufSize, hash);
        
        fwrite(hash, sizeof(hash[0]), (sizeof(hash)/sizeof(hash[0])), pass);
        
        fclose(pass);
        return 1;
    }
}

int comparePwd(char *pwd, int bufSize, char *salt, int saltSize, unsigned char *savedHash,  FILE *errFile)
{
    FILE *pass;
    unsigned char hash[SHA256_BLOCK_SIZE], saltHash[SHA256_BLOCK_SIZE];
    int res = fopen_s(&pass, "password.txt", "r");
    if(res != 0)
    {
        pass = NULL;
        printf("Error accessing password.txt. Writing error to output file.");
        fprintf(errFile, "File error: %d", res);
        exit(0);
    }
    else
    {
        hashPwd(salt, saltSize, saltHash);
        char saltedPwd[bufSize + sizeof(saltHash)];
        strncpy(saltedPwd, pwd, bufSize);
        strncat(saltedPwd, (char *)saltHash, sizeof(saltHash));
        hashPwd(saltedPwd, bufSize, hash);
        
        int ch = fgetc(pass), ind = 0;
        while(ch != EOF)
        {
            savedHash[ind++] = (unsigned char) ch;
            ch = fgetc(pass);
        }
        
        
        for(int i = 0; i < SHA256_BLOCK_SIZE; i++)
        {
            if(savedHash[i] != hash[i])
            {  
                fclose(pass);
                return 0;
            }
        }
        fclose(pass);
        return 1;
    }
}

void hashPwd(char *pwd, int bufSize, unsigned char *hash)
{
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (unsigned char*) pwd, bufSize);
    sha256_final(&ctx, hash);
}
