#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#define NAME 256
#define LONG 512



 
int i_buf=0, len_buf=0; // счет и длинна буфера 
char buf[LONG];

int i_Tbuf = 0, len_Tbuf = 0; // счет и длинна буфера 
char Tbuf[LONG];

FILE* f;
FILE* new_file;


char get_sym() {// получение символа 
	printf("len_Tbuf: %d , i_Tbuf:%d\n",len_Tbuf,i_Tbuf);
	if ((len_Tbuf == 0) || (i_Tbuf == len_Tbuf)) { 
		if (len_Tbuf != 0) {
			len_Tbuf = 0;
			i_Tbuf = 0;
			printf("len_Tbuf: %d , i_Tbuf:%d\n", len_Tbuf, i_Tbuf);
		}
	}
	else {
		printf("Tbuf > %c %x\n", Tbuf[i_Tbuf], Tbuf[i_Tbuf]);
	    return(Tbuf[i_Tbuf++]);
	}
	
	if ((len_buf == 0)||(i_buf ==len_buf)) { // либо начало либо кoнец 
		len_buf=fread(buf, sizeof(char), LONG, f); // считывает с места где остановился 
		if (len_buf != LONG) {  //если не дошел до конца 
			if (!feof(f)) {// либо ошибка 
				printf("File read error. %d", ferror(f));
				fclose(f);
				fclose(new_file);
				exit(1);
			}
			if (len_buf == 0) {// либо конец
				buf[0] = '\0';
			}
		}
		i_buf = 0;
	}
	return(buf[i_buf++]);
}

int check(char* FileName) {
	FILE* st;
	
	
	errno_t err = fopen_s(&st, FileName, "r");
	if (err)// 
	{
		printf("problems accessing  %s: %d\n", FileName, errno);

		return 0;
	}
	/*if (fopen_s(&st, FileName, "r") != 0)
	{
		printf("file open error %s: %d\n", FileName, errno);
		return 0;
	}*/
	return(1);
}
int main(int argc, char** argv){
	
	setlocale(LC_ALL, "Rus");
	int ii;

	//printf("%d\n", argc);
	if (argc !=5 ) {
		puts("Неверное количество параметров");
		puts("параметры запуска :lab_2.exe file_in str1 str2 file_out");
		exit(1);
	}
	for (ii = 0; ii < argc; ii++) {
		if (strlen(argv[ii]) > NAME) {
			printf("параметр %d слишком длинный ", ii - 1);
			exit(1);
		}
	}
	char name[NAME];
	char old[NAME];
	char new[NAME];
	char scnd_name[NAME];
	strcpy_s (name, strlen(argv[1])+1, argv[1]); 
	strcpy_s(old, strlen(argv[2]) + 1, argv[2]);
	strcpy_s(new, strlen(argv[3]) + 1, argv[3]);
	strcpy_s(scnd_name, strlen(argv[4]) + 1, argv[4]);
	//printf("%s \t %s \t %s \t %s \n", name, old, new, scnd_name);
	
	fopen_s(&new_file, scnd_name, "w");

	int res;
	int d = 0;
	res = check(name);
	if (res == 0){
		exit(1);
	}
    fopen_s(&f, name, "rt");
	unsigned char c=0;
	int i=0;
	while ((c = get_sym()) != '\0') {
		if (old[i] == c) {//если совпадает проверять 
			i++;
			if (old[i] == '\0') {// если совпадает до конца печатать 
				//printf("%s", new);
				fprintf_s(new_file, "%s", new);
				i = 0;
			}
		}
		else {
			printf("%c!=%c\n",old[i],c);
			if (i > 0) {
				fprintf_s(new_file, "%c", old[0]);
				printf("out>: %c\n", old[0]);
				d = 0;
				if (i_Tbuf == len_Tbuf ) {
						d = -1;
						
						if (len_Tbuf != 0) { 
							len_Tbuf = 0;
							i_Tbuf = 0;
							printf("len_Tbuf: %d , i_Tbuf:%d\n", len_Tbuf, i_Tbuf);
						}
			    }
				for (int j = 1; j < i; j++)
				{

					Tbuf[i_Tbuf + j+d] = old[j];
					len_Tbuf++;
					printf(">Tbuf: %c %d\n", old[j], i_Tbuf + j + d);

				}
				Tbuf[i_Tbuf + i+d] = c;
				printf(">Tbuf: %c %d\n", c, i_Tbuf + i + d);
				len_Tbuf++;
				
				i = 0;
			
			}
			else {
				fprintf_s(new_file, "%c", c);
				printf("out: %c\n",c);
			}
		}
		
	}
	for (int j = 0; j < i; j++)// если совпадает часть но конец файла => вывести старую 
	{
		//printf("%c", old[j]);
		fprintf_s(new_file, "%c", old[i]);
		printf("out_2: %c\n", old[i]);
	}
	fclose(f);
	fclose(new_file);
	

	printf("it's all");

}