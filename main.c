#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#define NAME 256
#define LONG 512



 
int i_buf=0, len_buf=0; // ���� � ������ ������ 
char buf[LONG];
FILE* f;
FILE* new_file;


char get_sym() {// ��������� ������� 
	if ((len_buf == 0)||(i_buf ==len_buf)) { // ���� ������ ���� ���� 
		len_buf=fread(buf, sizeof(char), LONG, f); // ��������� � ����� ��� ����������� 
		if (len_buf != LONG) {  //���� �� ����� �� ����� 
			if (!feof(f)) {// ���� ������ 
				printf("File read error. %d", ferror(f));
				fclose(f);
				fclose(new_file);
				exit(1);
			}
			if (len_buf == 0) {// ���� �����
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

	printf("%d\n", argc);
	if (argc !=5 ) {
		puts("�������� ���������� ����������");
		puts("��������� ������� :lab_2.exe file_in str1 str2 file_out");
		exit(1);
	}
	for (ii = 0; ii < argc; ii++) {
		if (strlen(argv[ii]) > NAME) {
			printf("�������� %d ������� ������� ", ii - 1);
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
	printf("%s \t %s \t %s \t %s \n", name, old, new, scnd_name);
	
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
		if (old[i] == c) {//���� ��������� ��������� 
			i++;
			if (old[i] == '\0') {// ���� ��������� �� ����� �������� 
				//printf("%s", new);
				fprintf_s(new_file, "%s", new);
				i = 0;
			}
		}
		else {
			for (int j = 0; j < i; j++)// �� ��������� => ������� ������ 
			{
				//printf("%c", old[j]);
				fprintf_s(new_file, "%c", old[j]);
			}
			i = 0;
			//printf("%c", c);
			fprintf_s(new_file, "%c", c);
		}
		
	}
	for (int j = 0; j < i; j++)// ���� ��������� ����� �� ����� ����� => ������� ������ 
	{
		//printf("%c", old[j]);
		fprintf_s(new_file, "%c", old[i]);
	}
	fclose(f);
	fclose(new_file);
	



}