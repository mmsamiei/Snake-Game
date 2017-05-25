#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>


int mar[46][2]; // keeping snake
char Getkey(int &);// Get char command
void setfood();    //set food
void init();
void docommand(char c,int i);
void move();
void gnl();        //go next level
void gbol();       //go began of level
int far *scr=(int far *)0XB8000000;
int live=3,last=0,co,D,food=1,x,y,level=1;
int fc=0X00;    //food color
int sc=0X04;    //snake color
int wc=0X77;    //wall color

				//**	main	**

int main(){
int i=0;
init();
while(live!=0){
	if(kbhit()){
		char c=Getkey(i);
		docommand(c,i);
	}
	move();
}
getch();
return 0;
}

//				GETKEY

char Getkey(int& c)
{
char I=getch();
if(I==0)
	{
	I=getch();
	c=1;
	}
else
	c=0;
return I;
}

//				init

void init(){
for(int i=0;i<46;i++){  //yek bug ajib dasht agar inro bardaram!
	mar[i][0]=12;
	mar[i][1]=40;
}
//last=0;
co=4;
D=1;
for(int j=0;j<2000;j++)
	*(scr+j)=0x00*256+32;
for(int q=0;q<81;q++)
	*(scr+80*24+q)=0x40*256+32;
*(scr+80*24+1)=0x40*256+'l';
*(scr+80*24+2)=0x40*256+'e';
*(scr+80*24+3)=0x40*256+'v';
*(scr+80*24+4)=0x40*256+'e';
*(scr+80*24+5)=0x40*256+'l';
*(scr+80*24+6)=0x40*256+level+'0';

*(scr+80*24+11)=0x40*256+'l';
*(scr+80*24+12)=0x40*256+'i';
*(scr+80*24+13)=0x40*256+'v';
*(scr+80*24+14)=0x40*256+'e';
*(scr+80*24+15)=0x40*256+':';
*(scr+80*24+16)=0x40*256+live+'0';
switch(level){
	case 1:
		break;
	case 2:
		for(int w=0;w<79;w++){
			*(scr+w)=wc*256+32;
			*(scr+23*80+w)=wc*256+32;
		}
		for(w=0;w<24;w++){
			*(scr+w*80+0)=wc*256+32;
			*(scr+w*80+79)=wc*256+32;
		}
		break;
	case 3:
		for(w=0;w<79;w++){
			*(scr+w)=wc*256+32;
			*(scr+23*80+w)=wc*256+32;
		}
		for(w=0;w<24;w++){
			*(scr+w*80+0)=wc*256+32;
			*(scr+w*80+79)=wc*256+32;
		}
		for(w=20;w<60;w++){
			*(scr+11*80+w)=wc*256+32;
			*(scr+13*80+w)=wc*256+32;

		}
		break;
	case 4:
		for(w=0;w<79;w++){
			*(scr+w)=wc*256+32;
			*(scr+23*80+w)=wc*256+32;
		}
		for(w=0;w<24;w++){
			*(scr+w*80+0)=wc*256+32;
			*(scr+w*80+79)=wc*256+32;
		}
		for(w=20;w<60;w++){
			*(scr+11*80+w)=wc*256+32;
			*(scr+13*80+w)=wc*256+32;

		}
		for(w=20;w<60;w++){
			*(scr+17*80+w)=wc*256+32;
			*(scr+19*80+w)=wc*256+32;

		}
		break;
}
setfood();
}
//
//				SETFOOD
void setfood(){
if(food>10){
	gnl();
	return;
}
fc=fc+0X10;
if(fc>0x70)fc=0x10;
srand(time(NULL));
x=rand()%24;
y=rand()%80;
while(*(scr+80*x+y)/256 != 0x00){
	x=rand()%24;
	y=rand()%79;
	}
*(scr+80*x+y)=fc*256+food+'0';
if(food==10)*(scr+80*x+y)=fc*256+'0';
}

//				DOCOMMAND

void docommand(char c,int i){
int td=D;
if(c==27) live=0;
if(i){	switch(c){
		case 'H':
			D=0;
			break;
		case 'P':
			D=2;
			break;
		case 'M':
			D=1;
			break;
		case 'K':
			D=3;
			break;
	}
	if(abs(td-D)==2 && last==1){
		live--;
		*(scr+80*24+16)=0x40*256+live+'0';
	}
}
}

//				move!

void move(){
	*(scr+80*mar[last][0]+mar[last][1])=32;
	for(int i=last;i>0;i--){
	mar[i][0]=mar[i-1][0];
	mar[i][1]=mar[i-1][1];
	}
	switch(D){
		case 0: //up
			mar[0][0]=(mar[0][0]-1)%24;
			if(mar[0][0]<0)mar[0][0]+=24;
			break;
		case 1: //right
			mar[0][1]=(mar[0][1]+1)%80;
			if(mar[0][1]>79)mar[0][1]+=80;
			break;
		case 2: //down
			mar[0][0]=(mar[0][0]+1)%24;
			if(mar[0][0]>25)mar[0][0]-=25;
			break;
		case 3: //left
			mar[0][1]=(mar[0][1]-1)%80;
			if(mar[0][1]<0)mar[0][1]+=80;
			break;

	}
		if(*(scr+80*mar[0][0]+mar[0][1])/256 == sc){
			live--;
			*(scr+80*24+16)=0x40*256+live+'0';
			gbol();
			return;
		}
		if(*(scr+80*mar[0][0]+mar[0][1])/256 == wc){
			live--;
			*(scr+80*24+16)=0x40*256+live+'0';
			gbol();
			return;
		}
		if(*(scr+80*mar[0][0]+mar[0][1])/256 == fc){
			last+=food;
			food++;
			setfood();
		}
		*(scr+80*mar[0][0]+mar[0][1])=sc*256+'*';
		if(level<4)delay(120 - (level)* 20);
		else delay(50);
}

void gnl(){
level++;
live++;
sc=sc+0x01;
last=0;
food=1;
fc=0x00;
init();
}
void gbol(){
init();
}