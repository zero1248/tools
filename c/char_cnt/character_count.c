/*
 * @Author: gaoy
 * @Date: 2022-09-23 10:39:11
 * @LastEditors: gaoy
 * @LastEditTime: 2022-09-23 10:48:34
 * @Description: file content
 */
#include<stdio.h>
#include<string.h>

#define MAX_LEN 1000
unsigned int letter=0, space=0, number=0, other=0;
char s[MAX_LEN];


void count_characters(char *s,unsigned int num){

    unsigned int i = 0;
    for(i=0;i<num;i++){
        if((s[i]>='a'&&s[i]<='z') || (s[i]>='A'&&s[i]<='Z')){
            letter++;
        }
        else if(s[i]>='0'&&s[i]<='9'){
            number++;
        }
        else if(s[i]==' '){
            space++;
        }
        else{
            other++;
        }
    }
}

int main(void){

	unsigned int n;

	printf("Input the string to be counted:\n");

	fgets(s, MAX_LEN, stdin);
	n = strlen(s);
	count_characters(s, n);

	printf("letter num = %d.\n number num  = %d.\n space num = %d.\n other num = %d.\n", 
        letter,
        number,
        space,
        other);

    return 0;
}
