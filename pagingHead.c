#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define NONE 1337
#define SIZE 1095
#define VM_SIZE 28
#define ROW 7	//Rader i virtuella minnet
#define COL 4	//Kolumner i virtuella minnet
#define ROWPRIMEM 4//Rader i primära minnet


char** createVM(){
	char** VM = calloc(ROW, sizeof(char*));
	VM[0] = "abcd";
	VM[1] = "efgh";
	VM[2] = "ijkl";
	VM[3] = "mnop";
	VM[4] = "qrst";
	VM[5] = "uvwx";
	VM[6] = "yz .";
	return VM;
	
	}
	
int menu(){
    printf("\nMenu:\n");
    printf("1. Exekvera program1\n");
    printf("2. Exekvera valfri bokstav\n");
    printf("3. Skriv ut sidtabell och primärminne\n");
    printf("4. Avsluta\n");
    return 0;
	}

void priMem(char **VM, int *ST, int row, char** PM, int rest){
	int x=NONE;
	int y = 0;
	int b=0;
	if(*(ST+row)==0){//Om bokstaven inte finns i primärminnet

		for(int i=0; i<ROW; i++){//Kollar om en sida i Primärminnet ska bytas ut(FIFO)
			if(*(ST+i)==1){
				*(ST+i)=2;
				}
			else if(*(ST+i)==2){
				*(ST+i)=3;
				}
			else if(*(ST+i)==3){
				*(ST+i)=4;
				}
			else if(*(ST+i)==4){
				*(ST+i)=0;
				x = i;
				y = 1;
				}

		}
		if(y!=1){	//Ingen sida i primärminnet behöver bytas ut. Lägger till ny sida
			for(int i=0; i<ROWPRIMEM; i++){
				if(PM[i][i]=='_'&&b!=1){
					PM[i]=VM[row];
					b=1;
				}
			}
		}

		*(ST+row)=1;
	for(int i=0; i<ROWPRIMEM; i++){//Om sida behöver bytas ut(FIFO)
			if(PM[i]==VM[x] && y==1){
				PM[i]=VM[row];
				}
			}
}
	printf("%c", VM[row][rest]);//Skriver ut bokstav
}

void execProg1(char** VM, char** PM, int* ST){
	FILE *file = fopen("Program1.txt", "rt");//Öppnar filen Program1.txt
	int number[SIZE];
	int a=0, b=0;
	if(file == NULL){
		printf("\nWarning: Det gick inte att läsa filen");
		exit(0);
		}
		while(a < SIZE){
			fscanf(file, "%d,", &number[a]);//Läser in siffror från fil
			int rest = number[a]%COL;//Räknar ut vilken rad och kolumn bokstaven ligger på i virtuellaminnet.
			int row = number[a]/COL;
			priMem(VM, ST, row, PM, rest);//Lägger till sidan med bokstaven i primärminnet om den inte finns
			a++;
			b++;
		}
	fclose(file);//Stränger fil
	printf("\n\nInläsning av fil klar\n");
	}

void bokstav(char** VM, char** PM, int* ST){
		int x=0;
		int a;
		int b;
		printf("Sidnummer(0-6):");//Inläsning av sidnummer och offset
		scanf("%d", &a);
		while(a>ROW-1||a<0){
		printf("Inkorrekt val\n");
		printf("Sidnummer(0-6):");
		scanf("%d", &a);
		}
		printf("Offset(0-3):");
		scanf("%d", &b);
		while(b>COL-1||b<0){
		printf("Inkorrekt val\n");
		printf("Offset(0-3):");	
		scanf("%d", &b);
		}
		char c= VM[a][b];
		for(int i=0; i<ROWPRIMEM;i++){//Kontrollerar om bokstaven finns i primärminnet
			for(int j=0; j<ROWPRIMEM;j++){
				if(PM[i][j]==VM[a][b]){
					printf("%c", PM[i][j]);
					x=1;
				}
			}
		}
		if(x==0)priMem(VM, ST, a, PM, b);//Lägger till sida med bokstav vid behov
}

void skriv(char** VM, char** PM, int* ST){
	printf("\n");
	printf("Primärminne:\n");	//Utskrift av primärminne
	for(int i=0; i<ROWPRIMEM; i++){
		printf("%d   ", i);
			for(int j=0; j<4;j++){
						printf("||   %c", PM[i][j]);
					}
					printf("||\n");
				}
				printf("\n\n");
	printf("Sidtabell:\n");
	for(int i=0; i<ROW; i++){	//Utskrift av sidtabell
		if(ST[i]!=0){
			for(int k=0; k<ROWPRIMEM; k++){
				if(VM[i]==PM[k]){
				printf("%d  ||  %d  ||\n", i, k);
				}
			}
			}
		else printf("%d  ||  M  ||\n", i);
		}
}
			


