#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <filestrings.h>
#include <ctype.h>

/* Function that read's a string from the keyboard */
char *readString(){
	char *string = NULL;
	int n = 0;

		/* Loop that will get the string */
		do{
			/* Allocating one byte */
			string = (char*)realloc(string,sizeof(char)*(n+1));
			/* Reading a char from the file */
			string[n++] = (char) fgetc(stdin);			
		}while(string[n-1] != '\n');
		/* Putting a \0 on at the end of the string */
		string[n-1] = '\0';

	return string;	
}

/* Function that read's a field from the given file */
unsigned char *readField(FILE *file){
	unsigned char *field = NULL;
	int n = 0;

		/* Loop that will get the string */
		do{
			/* Allocating one unsigned byte */
			field = (unsigned char*)realloc(field,sizeof(unsigned char)*(n+1));
			/* Reading a unsigned char from the file */
			field[n++] = (unsigned char) fgetc(file);			
		}while(field[n-1] != ';' && field[n-1] != '\n');
		/* Putting a \0 on at the end of the string */
		field[n-1] = '\0';

	return field;	
}

/* Function that read's a field from the given binary file */
unsigned char *readFieldBinary(FILE *file,int sizeIndicator){
	unsigned char *field = NULL;
	int n = 0;

		/* Loop that will get the string */
		do{
			/* Allocating one unsigned byte */
			field = (unsigned char*)realloc(field,sizeof(unsigned char)*(n+1));
			/* Reading a unsigned char from the file */
			fread(&field[n++],sizeof(unsigned char),1,file);
		}while(field[n-1] != '\n' && field[n-1] != EOF && n < sizeIndicator);
		/* Putting a \0 on at the end of the string */
		field[n-1] = '\0';
	return field;	
}

/* Function that upper case every character in the string */
void strUpper(unsigned char *string){
	int i,size = strlen((char*)string);
	for(i = 0 ; i < size ; i++) string[i] = toupper(string[i]);
}

/* Returns file size */
int fileSize(FILE *file){
	int size;
	fseek(file,0,SEEK_END);
	size = (int) ftell(file);
	rewind(file);

	return size;
}