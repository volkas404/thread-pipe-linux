#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc , char* argv[]){
	int chan;
	int chansong[2];
	char chanyeu[100];
	pipe(chansong);
	chan=fork();
	if(chan>0){
		printf("1.cha viet %s vao duong ong\n",argv[1]);
		write(chansong[1],argv[1],strlen(argv[1]));
		wait(NULL);
		read(chansong[0],chanyeu,100);
		printf("4.cha doc %s=%s tu duong ong\n",argv[1],chanyeu);
	}
	if(chan==0){
		char chandoi[100];
		int ghetcuocsong1=0;
		float ghetcuocsong2=0;
		char *ghetyeu1,*ghetyeu2;
		read(chansong[0],chandoi,strlen(argv[1]));
		chandoi[strlen(argv[1])]='\0';
		for(int i=0;i<strlen(argv[1]);i++){
			if(chandoi[i]=='+'){
				ghetyeu1=strtok(chandoi,"+");
				ghetyeu2=strtok(NULL,chandoi-2);
				ghetcuocsong1=atoi(ghetyeu1)+atoi(ghetyeu2);
			}
			if(chandoi[i]=='-'){
				ghetyeu1=strtok(chandoi,"-");
				ghetyeu2=strtok(NULL,chandoi-2);
				ghetcuocsong1=atoi(ghetyeu1)-atoi(ghetyeu2);
			}
			if(chandoi[i]=='*'){
				ghetyeu1=strtok(chandoi,"*");
				ghetyeu2=strtok(NULL,chandoi-2);
				ghetcuocsong1=atoi(ghetyeu1)*atoi(ghetyeu2);
			}
			if(chandoi[i]=='/'){
				ghetyeu1=strtok(chandoi,"/");
				ghetyeu2=strtok(NULL,chandoi-2);
				ghetcuocsong2=(atoi(ghetyeu1)*1.0)/atoi(ghetyeu2);
			}
		}
		printf("2.con doc %s tu duong ong\n",argv[1]);
		if(ghetcuocsong1!=0){
			printf("3.con viet %s=%d vao duong ong\n",argv[1],ghetcuocsong1);
			sprintf(ghetyeu1,"%d",ghetcuocsong1);
			write(chansong[1],ghetyeu1,100);
		}
		if(ghetcuocsong2!=0){
			printf("3.con viet %s=%f vao duong ong\n",argv[1],ghetcuocsong2);
			sprintf(ghetyeu1,"%f",ghetcuocsong2);
			write(chansong[1],ghetyeu1,100);
		}
	}
}