#include <stdio.h>
#include <string.h>
#include "pagingHead.h"
#include <stdlib.h>

#define ROW 7	//Rader i virtuella minnet
#define ROWPRIMEM 4//Rader i primära minnet

	
int main(){
	char** VM;//Virtuellt minne
	char** PM= calloc(ROWPRIMEM, sizeof(char*));//Primärminne
	int* ST= calloc(ROW, sizeof(int*));//Sidtabell
	for(int i=0; i<ROW; i++)PM[i]="____";
	for(int i=0; i<ROW; i++)ST[i]=0;
	
	
	int choice;//Val
	do{
		menu();
		printf("\nVal(1-4): ");
		scanf("%d", &choice);
		while(choice<1||choice>4){
			printf("Ditt är inkorrekt");
			printf("\nVal(1-4): ");
			scanf("%d", &choice);				
		}
		VM = createVM();

		printf("\n");
		
		if(choice==1){
			execProg1(VM, PM, ST);//Exikvering av program 1.txt
			for(int i=0; i<ROW; i++)PM[i]="____";
			for(int i=0; i<ROW; i++)ST[i]=0;
			}
		
		if(choice==2){
			bokstav(VM, PM, ST);//Lägger bokstav med sida i primärminne
			}
		
		if(choice==3){
			skriv(VM, PM, ST);//Skriv ut sidtabell och primärminne
			}
		}while(choice!=4);
		return 0;
	}
		
