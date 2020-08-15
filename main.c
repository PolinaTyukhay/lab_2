#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#define NAME 256
#define LONG 3

/*int if_d(char c) {
	if (c == 'd') {
		return(2);
	}
	else
	{
		return(0);
	}
}
int if_a(char c) {
	if (c == 'a') {
		return(1);
	}
	else
	{
		return(0);
	}
}*/

 
int i_buf=0, len_buf=0;
char buf[LONG];
FILE* f;


char get_sym() {
	if ((len_buf == 0)||(i_buf ==len_buf)) {
		len_buf=fread(buf, sizeof(char), LONG, f);
		if (len_buf != LONG) {
			if (!feof(f)) {
				printf("File read error. %d", ferror(f));
				fclose(f);
				exit(1);
			}
			if (len_buf == 0) {
				buf[0] = '\0';
			}
		}
		i_buf = 0;
	}
	return(buf[i_buf++]);
}

int check(char* FileName) {
	FILE* st;
	int cnt_t = 0, tst = 0, sym;
	
	errno_t err = fopen_s(&st, FileName, "r");
	if (err)
	{
		printf("problems accessing  %s: %d\n", FileName, errno);

		return 0;
	}
	if (fopen_s(&st, FileName, "r") != 0)
	{
		printf("file open error %s: %d\n", FileName, errno);
		return 0;
	}
	return(1);
}
int main(){

	char name[NAME];
	printf("file name : ");
	fseek(stdin, 0, SEEK_SET);
	gets_s(name, 255);
	char old[NAME];
	printf("\nold str : ");
	fseek(stdin, 0, SEEK_SET);
	gets_s(old, 255);
	char new[NAME];
	printf("\nnew str : ");
	fseek(stdin, 0, SEEK_SET);
	gets_s(new, 255);
	char scnd_name[NAME];
	printf("\n name for new file : ");
	fseek(stdin, 0, SEEK_SET);
	gets_s(scnd_name, 255);
	printf("%s \t %s \t %s \t %s \n", name, old, new, scnd_name);
	FILE* new_file;
	fopen_s(&new_file, scnd_name, "w");

	int res;
	res = check(name);
	if (res == 0){
		exit(1);
	}
    fopen_s(&f, name, "rt");
	unsigned char c=0;
	int i=0;
	while ((c = get_sym()) != '\0') {
		if (old[i] == c) {
			i++;
			if (old[i] == '\0') {
				//printf("%s", new);
				fprintf_s(new_file, "%s", new);
				i = 0;
			}
		}
		else {
			for (int j = 0; j < i; j++)
			{
				//printf("%c", old[j]);
				fprintf_s(new_file, "%c", old[j]);
			}
			i = 0;
			//printf("%c", c);
			fprintf_s(new_file, "%c", c);
		}
		
	}
	for (int j = 0; j < i; j++)
	{
		//printf("%c", old[j]);
		fprintf_s(new_file, "%c", old[i]);
	}
	fclose(f);
	



}