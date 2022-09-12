#include<bits/stdc++.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctime>
using namespace std;
using LL=long long;
char m[32][32];
LL ans=0;
int N,M; 
int fx,fy;
int lx,ly;
const int LEN=1e4+10; 
int snk_x[LEN],snk_y[LEN];
int sfront,srear; 
void gotoxy(int x,int y){
	COORD point;
	point.X=y; point.Y=x; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),point);
}
void init_map(){
	memset(m,'#',sizeof(m));
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			m[i][j]=' '; 
	for (LL i=1; i<=10; i++){
		LL x=rand()%N+1;
		LL y=rand()%M+1;
		m[x][y]='#';
	}
}
void init_food(){
	m[fx][fy]='o';
}
void init_snake(){
	for(int i=srear;i<=sfront;i++){
		int px=snk_x[i],py=snk_y[i] ;
		m[px][py]='*';
	}	
}
void snake_move(char dct){
	int head_x=snk_x[sfront],head_y=snk_y[sfront];
	int rx=snk_x[srear],ry=snk_y[srear];
	int next_x,next_y;
	if(dct=='w')  next_x=head_x-1, next_y=head_y;
	if(dct=='s')  next_x=head_x+1, next_y=head_y;
	if(dct=='a')  next_x=head_x, next_y=head_y-1;
	if(dct=='d')  next_x=head_x, next_y=head_y+1;
	sfront++;  snk_x[sfront]=next_x; snk_y[sfront]=next_y;
	srear++; 
	gotoxy(rx,ry); cout<<' ';
} 
void creatFood(){
	srand(time(0));
	fx=rand()%N+1;
	fy=rand()%M+1;
	lx=rand()%N+1;
	ly=rand()%M+1;
}
void dropFood(){
	creatFood();
	gotoxy(lx,ly);	cout<<'L'; 
	gotoxy(fx,fy);	cout<<'o'; 
}
void drawSnake(){
	for(int i=srear;i<=sfront;i++){
		int x=snk_x[i],y=snk_y[i];
		gotoxy(x,y);
		cout<<"*";
	}
	int hx=snk_x[sfront],hy=snk_y[sfront];
	gotoxy(hx,hy);
	cout<<"@";
} 
int foodCanEat(){
	for(int i=sfront;i>=srear;i--){
		int xi=snk_x[i],yi=snk_y[i];
		if(xi==fx && yi==fy){
			return 1;
		}else if (xi==lx && yi==ly){
			return 2;
		}
	}
	return 0;
}
void eatFood(){
	sfront++; snk_x[sfront]=fx; snk_y[sfront]=fy;
}
int meetWall(){
	int hx=snk_x[sfront],hy=snk_y[sfront];
	if( m[hx][hy]=='#' ) return 1;
	return 0;
}
void drawMap(){
	for(int i=0;i<=N+1;i++)
	{
		for(int j=0;j<=M+1;j++)
			cout<<m[i][j];
		cout<<endl;
	} 
}
void init_set(){
	N=20,M=20;
	
	sfront=2; srear=0;
	snk_x[0]=10,snk_y[0]=10;
	snk_x[1]=10,snk_y[1]=11;
	snk_x[2]=10,snk_y[2]=12;
	
	creatFood();
}
int main(){
	cout<<"小周周力献  贪吃蛇 V1.1.1 PC版 \n";
	cout<<"方向键或“ASDW”“asdw”操作\n";
	cout<<"请按任意键开始!\n"; 
	system("pause");
	system("cls");
	srand((unsigned int)(time(NULL)));
	init_set();
	init_map();	
	drawMap(); 
	drawSnake();
	dropFood();
	bool flag=0; 
	while(1){
		if(meetWall()==1) {
			flag=1;
			break;
		}
		if(kbhit()){
			char ch=getch();
			if(ch=='a'||ch=='A'||ch==75)	snake_move('a'); 	
			if(ch=='d'||ch=='D'||ch==77)	snake_move('d');
			if(ch=='s'||ch=='S'||ch==80)	snake_move('s');
			if(ch=='w'||ch=='W'||ch==72)	snake_move('w');
			drawSnake();
		}
		if(foodCanEat()!=0) {
			if (foodCanEat()==1){
				eatFood();
				dropFood();
				ans++;	
			}else{
				eatFood();
				dropFood();
				ans+=2;
			}
		}	
	} 
	if (flag){
		gotoxy(N+2,0);
		cout<<"死亡！分数:"<<ans<<" 请按任意键退出\n";
		system("pause");
	}
}
