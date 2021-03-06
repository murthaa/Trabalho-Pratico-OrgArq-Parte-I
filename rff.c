#include <stdlib.h>
#include <stdio.h>
#include <filestrings.h>
#include <string.h>
#include <rff.h>

/*
	Write sequence on the output file:
	Fixed Fields: ticket->doc->initialTime->updatedTime
	Variable Fields: domain,name,city,state
*/

/* Struct that contains a variable size register with fixed number of fields */
typedef struct rff{
	int ticket;
	unsigned char doc[20];
	unsigned char initalTimestamp[20];
	unsigned char updatedTimestamp[20];
	unsigned char *domain;
	unsigned char *name;
	unsigned char *city;
	unsigned char *state;
}RFF;

/* Funtion that free's the memory of a register content */
void freeRegisterContent(RFF *reg){
	(reg)->ticket = 0;
	(reg)->doc[0] = '\0';
	(reg)->initalTimestamp[0] = '\0';
	(reg)->updatedTimestamp[0] = '\0';
	free((reg)->domain);
	free((reg)->name);
	free((reg)->city);
	free((reg)->state);
}

/* Function that will print only one register */
void printRegister_RFF(RFF reg,int n){
	printf("Register Nº%d.\n", n+1);
	printf("DOMAIN: %s\n", reg.domain);
	printf("DOCUMENT: %s\n", reg.doc);
	printf("NAME: %s\n", reg.name);
	printf("STATE: %s\n", (unsigned char*) reg.state);
	printf("CITY: %s\n", reg.city);
	printf("INITIAL TIMESTAMP: %s\n", reg.initalTimestamp);
	printf("UPDATED TIMESTAMP: %s\n", reg.updatedTimestamp);
	printf("TICKET: %d\n\n", reg.ticket);
}

/* Function that read's and recovers one register of the given file */
RFF readOneBinary_RFF(FILE *file){
	RFF aux;
	int sizeIndicator;

		/* In this segment we simply read the fields sometimes using the size indicator */
		fread(&(aux.ticket),sizeof(int),1,file);
		fread(aux.doc,sizeof(unsigned char),20,file);
		fread(aux.initalTimestamp,sizeof(unsigned char),20,file);
		fread(aux.updatedTimestamp,sizeof(unsigned char),20,file);
		fread(&sizeIndicator,sizeof(int),1,file);
		aux.domain = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
		fread(aux.domain,sizeof(unsigned char),sizeIndicator,file);
		fread(&sizeIndicator,sizeof(int),1,file);
		aux.name = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
		fread(aux.name,sizeof(unsigned char),sizeIndicator,file);
		fread(&sizeIndicator,sizeof(int),1,file);
		aux.city = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
		fread(aux.city,sizeof(unsigned char),sizeIndicator,file);
		fread(&sizeIndicator,sizeof(int),1,file);
		aux.state = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
		fread(aux.state,sizeof(unsigned char),sizeIndicator,file);

	return aux;
}

/* Print an register that match the position and the criteria given by the user */
void printViaPosField_RFF(char *fileName,int pos,int op){
	FILE *file = fopen(fileName,"r+");
	int i,sizeIndicator;
	RFF aux;

		if(pos-1 < 0){
			printf("Out of reach, position given is out of bounds.\n");
			return;
		}

		/* Controls the recovery of a register */
		switch(op){
			/* Sequential search in all of the cases because of the variable size fields */
			case 1:
					i = 1;
					while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}
					/* Jumping trough registers */
						fseek(file,64,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						i++;
					}

					aux = readOneBinary_RFF(file);
					printf("DOMAIN: %s\n", aux.domain);
					freeRegisterContent(&aux);
			break;
			case 2:
				i = 1;
					while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}

					/* Jumping trough registers */
						fseek(file,64,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						i++;
					}

					aux = readOneBinary_RFF(file);
					printf("DOCUMENT: %s\n", aux.doc);
					freeRegisterContent(&aux);

			break;
			case 3:
				i = 1;
					while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}
					/* Jumping trough registers */
						fseek(file,64,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						i++;
					}

					aux = readOneBinary_RFF(file);
					printf("NAME: %s\n", aux.name);
					freeRegisterContent(&aux);
			break;
			case 4:
				i = 1;
					while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}
					/* Jumping trough registers */
						fseek(file,64,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						i++;
					}

					aux = readOneBinary_RFF(file);
					printf("STATE: %s\n", aux.state);
					freeRegisterContent(&aux);

			break;
			case 5:
				i = 1;
					while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}
					/* Jumping trough registers */
						fseek(file,64,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						i++;
					}

					aux = readOneBinary_RFF(file);
					printf("CITY: %s\n", aux.city);
					freeRegisterContent(&aux);
			break;
			case 6:
				i = 1;
					while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}
					/* Jumping trough registers */
						fseek(file,64,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						i++;
					}

					aux = readOneBinary_RFF(file);
					printf("INITIAL TIMESTAMP: %s\n", aux.initalTimestamp);
					freeRegisterContent(&aux);

			break;
			case 7:
				i = 1;
					while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}
					/* Jumping trough registers */
						fseek(file,64,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						fread(&sizeIndicator,sizeof(int),1,file);
						fseek(file,sizeIndicator,SEEK_CUR);
						i++;
					}

					aux = readOneBinary_RFF(file);
					printf("UPDATED TIMESTAMP: %s\n", aux.updatedTimestamp);
					freeRegisterContent(&aux);

			break;
			case 8:
				i = 1;
				while(i < pos){
					if(!feof(file)){
						printf("Out of reach, position given is out of bounds.\n");
						return;
					}
					/* Jumping trough registers */
					fseek(file,64,SEEK_CUR);
					fread(&sizeIndicator,sizeof(int),1,file);
					fseek(file,sizeIndicator,SEEK_CUR);
					fread(&sizeIndicator,sizeof(int),1,file);
					fseek(file,sizeIndicator,SEEK_CUR);
					fread(&sizeIndicator,sizeof(int),1,file);
					fseek(file,sizeIndicator,SEEK_CUR);
					fread(&sizeIndicator,sizeof(int),1,file);
					fseek(file,sizeIndicator,SEEK_CUR);
					i++;
				}

				aux = readOneBinary_RFF(file);
				printf("TICKET: %d\n", aux.ticket);
				freeRegisterContent(&aux);
			break;
		}

		fclose(file);
}

/* Print an register that match the position give by the user */
void printViaPosition_RFF(char *fileName,int pos){
	FILE *file = fopen(fileName,"r+");
	int i=1,sizeIndicator;
	RFF aux;


		if(pos-1 < 0){
			printf("Out of reach, position given is out of bounds.\n");
			return;
		}

		while(i < pos){
			if(!feof(file)){
				printf("Out of reach, position given is out of bounds.\n");
				return;
			}
			/* Jumping trough registers */
			fseek(file,64,SEEK_CUR);
			fread(&sizeIndicator,sizeof(int),1,file);
			fseek(file,sizeIndicator,SEEK_CUR);
			fread(&sizeIndicator,sizeof(int),1,file);
			fseek(file,sizeIndicator,SEEK_CUR);
			fread(&sizeIndicator,sizeof(int),1,file);
			fseek(file,sizeIndicator,SEEK_CUR);
			fread(&sizeIndicator,sizeof(int),1,file);
			fseek(file,sizeIndicator,SEEK_CUR);
			i++;
		}

		aux = readOneBinary_RFF(file);
		printRegister_RFF(aux,pos-1);
		freeRegisterContent(&aux);

	fclose(file);
}

/* Print all the registers that match the criteria given by the user */
void printViaField_RFF(char *fileName,int op, char *stringKey){
	FILE *file = fopen(fileName,"rb+");
	int i = 0,sizeIndicator,setBack,size = fileSize(file),flag;
	int intKey = atoi(stringKey);
	RFF aux;

		/* Controls the recovery of a register */
		switch(op){
			/* Sequential search in all of the cases because of the variable size fields */
			case 1:
				/* Loop that will iterate until the end of the file */
				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					aux.domain = NULL;
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fseek(file,4,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					aux.domain = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
					fread(aux.domain,sizeof(unsigned char),sizeIndicator,file);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					strUpper(aux.domain);
					strUpper((unsigned char *)stringKey);

					if(!strcmp(stringKey,(char*)aux.domain)){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						free(aux.domain);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}else free(aux.domain);
					i++;
				}
				if(flag != -1) printf("The key was not found in the file.\n");



			break;
			case 2:
				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fseek(file,4,SEEK_CUR);
					fread(aux.doc,sizeof(unsigned char),20,file);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					strUpper(aux.doc);
					strUpper((unsigned char *)stringKey);

					if(!strcmp(stringKey,(char*)aux.doc)){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}
					i++;
				}
				if(flag != -1) printf("The key was not found in the file.\n");


			break;
			case 3:
				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fseek(file,4,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					aux.name = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
					fread(aux.name,sizeof(unsigned char),sizeIndicator,file);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					strUpper(aux.name);
					strUpper((unsigned char *)stringKey);

					if(!strcmp(stringKey,(char*)aux.name)){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						free(aux.name);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}else free(aux.name);
					i++;
				}
				if(flag != -1) printf("The key was not found in the file.\n");



			break;
			case 4:
				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fseek(file,4,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					aux.city = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
					fread(aux.city,sizeof(unsigned char),sizeIndicator,file);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);


					strUpper(aux.city);
					strUpper((unsigned char *)stringKey);

					if(!strcmp(stringKey,(char*)aux.city)){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						free(aux.city);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}else free(aux.city);
					i++;

				}
				if(flag != -1) printf("The key was not found in the file.\n");



			break;
			case 5:

				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fseek(file,4,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					aux.state = (unsigned char*)malloc(sizeof(unsigned char)*sizeIndicator);
					fread(aux.state,sizeof(unsigned char),sizeIndicator,file);

					strUpper(aux.state);
					strUpper((unsigned char *)stringKey);

					if(!strcmp(stringKey,(char*)aux.state)){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						free(aux.state);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}else free(aux.state);
					i++;
				}
				if(flag != -1) printf("The key was not found in the file.\n");


			break;
			case 6:
				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fseek(file,4,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fread(aux.initalTimestamp,sizeof(unsigned char),20,file);
					fseek(file,20,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					strUpper(aux.initalTimestamp);
					strUpper((unsigned char *)stringKey);

					if(!strcmp(stringKey,(char*)aux.initalTimestamp)){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}
					i++;
				}
				if(flag != -1) printf("The key was not found in the file.\n");


			break;
			case 7:
				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fseek(file,4,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fread(aux.updatedTimestamp,sizeof(unsigned char),20,file);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					strUpper(aux.updatedTimestamp);
					strUpper((unsigned char *)stringKey);

					if(!strcmp(stringKey,(char*)aux.updatedTimestamp)){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}
					i++;
				}
				if(flag != -1) printf("The key was not found in the file.\n");


			break;
			case 8:
				while(ftell(file) != size){
					/* Offset to get back in case the actual register is valid */
					setBack = 80;
					/* In this segment we simply read the fields sometimes using the size indicator */
					fread(&aux.ticket,sizeof(int),1,file);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);
					fseek(file,20,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					fread(&sizeIndicator,sizeof(int),1,file);
					setBack += sizeIndicator;
					fseek(file,sizeIndicator,SEEK_CUR);

					if(intKey == aux.ticket){
						/* Getting back to the valid register */
						flag = -1; /* Set that were found register */
						fseek(file,-(setBack),SEEK_CUR);
						aux = readOneBinary_RFF(file);
						printRegister_RFF(aux,i);
						freeRegisterContent(&aux);
					}
					i++;
				}
				if(flag != -1) printf("The key was not found in the file.\n");
			break;
		}

		fclose(file);
}

/* Function that print all the registers that were recovered one by one and by the demand of the user */
void printAll_RFF(char *fileName){
	FILE *file = fopen(fileName,"r+");
	int i = 0,op,size = fileSize(file);
	RFF auxReg;

		/* Loop of all the registers */
		while(ftell(file) != size){
			auxReg = readOneBinary_RFF(file);
			printRegister_RFF(auxReg,i);
			freeRegisterContent(&auxReg);
			printf("Press: [0]- Quit.\n       [1]- More registers.\n");
			scanf("%d",&op);
			i++;
			if(!op) break;
		}

	fclose(file);
}

/* Read's a register of type RFF(Fixed number of fields) of the input,
   write's it in the output */
void readAndWrite_RFF(FILE *fpEntry,FILE *fpOut){
	RFF *reg = (RFF*)calloc(sizeof(RFF),1);
	unsigned char *auxString;
	int sizeIndicator;


		if(!feof(fpEntry)){

			/* Read block */
			reg->domain = readField(fpEntry);
			auxString = readField(fpEntry);
			memcpy(reg->doc,auxString,strlen((char*)auxString)+1);
			free(auxString);
			reg->name = readField(fpEntry);
			reg->state = readField(fpEntry);
			reg->city = readField(fpEntry);
			auxString = readField(fpEntry);
			memcpy(reg->initalTimestamp,auxString,strlen((char*)auxString)+1);
			free(auxString);
			auxString = readField(fpEntry);
			memcpy(reg->updatedTimestamp,auxString,strlen((char*)auxString)+1);
			free(auxString);
			fscanf(fpEntry,"%d%*c%*c",&reg->ticket);
			/*---------------------------------------*/

			/* Write block */
			fwrite(&(reg->ticket),sizeof(int),1,fpOut);

			fwrite(reg->doc,sizeof(unsigned char),20,fpOut);

			fwrite(reg->initalTimestamp,sizeof(unsigned char),20,fpOut);

			fwrite(reg->updatedTimestamp,sizeof(unsigned char),20,fpOut);

			sizeIndicator = (strlen((char*)reg->domain)) + 1;
			fwrite(&sizeIndicator,sizeof(int),1,fpOut);
			fwrite(reg->domain,sizeof(unsigned char),sizeIndicator,fpOut);

			sizeIndicator = (strlen((char*)reg->name) + 1);
			fwrite(&sizeIndicator,sizeof(int),1,fpOut);
			fwrite(reg->name,sizeof(unsigned char),sizeIndicator,fpOut);

			sizeIndicator = (strlen((char*)reg->city)) + 1;
			fwrite(&sizeIndicator,sizeof(int),1,fpOut);
			fwrite(reg->city,sizeof(unsigned char),sizeIndicator,fpOut);

			sizeIndicator = (strlen((char*)reg->state)) + 1;
			fwrite(&sizeIndicator,sizeof(int),1,fpOut);
			fwrite(reg->state,sizeof(unsigned char),sizeIndicator,fpOut);
			freeRegisterContent(reg);
			/*-----------------------------------------------------------*/
		}

	free(reg);
}

/* Receives a name of a file read's it and create's a new file using
   fixed number of fields in a variable size register */
char *createNewFile_RFF(char *fileNameEntry){
	FILE *fpEntry = fopen(fileNameEntry,"r+"); /* Pointer of the designated csv file */
	//char *fileNameOut; // = functioNString(); /* Name of the output file */
	FILE *fpOut;
	int size = fileSize(fpEntry);

		fpOut = fopen("out","wb+"); /* Create's a new output file */

		/* Loop that will create the new file */
		while(ftell(fpEntry) != size) readAndWrite_RFF(fpEntry,fpOut);

	fclose(fpEntry);
	fclose(fpOut);

	return "out";
}
