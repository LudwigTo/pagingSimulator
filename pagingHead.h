#ifndef NY_H
#define NY_H


char** createVM();
int menu();
void printArr(char **array);
void priMem(char **VM, int **ST, int row, char** PM, int rest);
void execProg1(char** VM, char** PM, int* ST);
void bokstav(char** VM, char** PM, int* ST);
void skriv(char** VM, char** PM, int* ST);


#endif
