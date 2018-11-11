#include <iostream>
#include<conio.h>
#include<windows.h>
#include<dos.h>
#include<time.h>
#include <fstream>
#include<string>
#define MAXSIZE 100
#define MAXFRAMEX 119
#define MAXFRAMEY 29
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
	CursorPosition.X=x;
	CursorPosition.Y=y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size)
{
	if(size==0)
	size=20;
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible=visible;
	lpCursor.dwSize=size;
	SetConsoleCursorInfo(console, &lpCursor);
}


class Point{
	private:
		int x,y;
	public:
		Point(){
			x=10;
			y=10;
		}
		Point(int x,int y){
		
			this->x=x;
			this->y=y;
		}
		void SetPoint(int x,int y)
		{
			this->x=x;
			this->y=y;	
		}
		int GetX(){
			return x;
		}  
		int GetY()
		{
			return y;
		}
		void MoveUp(){
			y--;
			if(y<0)
			y=MAXFRAMEY;
		}
		void MoveDown(){
			y++;
			if(y>MAXFRAMEY)
			y=0;
		}
		void MoveLeft(){
			x--;
			if(x<0)
			x=MAXFRAMEX;
		} 	
		void MoveRight(){
			x++;
			if(x>MAXFRAMEX)
			x=0;
		}
		void Draw(char ch='O'){
			gotoxy(x,y);
			cout<<ch;
		}
		void Erase(){
			gotoxy(x,y);
			cout<<" ";
		}
		void CopyPos(Point *p){
			p->x=x;
			p->y=y;
		}
		int IsEqual(Point *p)
		{
			if(p->x==x && p->y==y)
			return 1;
			
			return 0;
		}
		void Debug(){
			cout<<"("<<x<<","<<y<<") ";
		}
}; 
class Snake{
	private:
		Point * cell[MAXSIZE];
		int size;
		char dir;
		Point fruit;
		int state=0;
		int started;
	public:
		Snake(){
			size=1;
			cell[0]=new Point(20,20);
			for(int i=1;i<MAXSIZE;i++)
			cell[i]=NULL;
			
			fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
		}
		void AddCell(int x,int y){
			cell[size++]=new Point(x,y);
		}
		void TurnUp(){
			if(dir!='s')
			dir='w';
		}
		void TurnDown(){
			if(dir!='w')
			dir='s';
		}
		void TurnLeft(){
			if(dir!='d')
			dir='a';
		}
		void TurnRight(){
			if(dir!='a')
			dir='d';
		}
		void welcomeScreen(){
			SetConsoleTextAttribute(console,15);
		}
		void Move(){
			//making snake body follow its head
			system("cls");
			if(state==0)
			{
				if(!started)
				{
				welcomeScreen();
				cout<<"Press any key to start"<<endl;
				getch();
				started=1;
				state=1;
				size=1;
				}
				else{
					cout<<"GAME OVER!!!"<<endl;
					cout<<"Press any key to start"<<endl;
					cout<<"Your Score is: "<<size-1<<endl;
				getch();
				state=1;
				size=1;
				}
			}
			for(int i=size-1;i>0;i--)
			{
				cell[i-1]->CopyPos(cell[i]);
			}
			//turning snake's head
			switch(dir){
			case 'w':
				cell[0]->MoveUp();
				break;
			case 's':
				cell[0]->MoveDown();
				break;
			case 'a':
				cell[0]->MoveLeft();
				break;
			case 'd':
				cell[0]->MoveRight();			
				break;		
			}
			if(selfCollision())
			{		
				state=0;
			}
			
			//collision with fruit
			if(fruit.GetX()==cell[0]->GetX() && fruit.GetY()==cell[0]->GetY())
			{
				AddCell(0,0);
				fruit.SetPoint(rand()%MAXFRAMEX,rand()%MAXFRAMEY);
			}
			
			//drawing snake
			for(int i=0;i<size;i++)
			cell[i]->Draw();
			SetConsoleTextAttribute(console,242);
			fruit.Draw('$');
			SetConsoleTextAttribute(console,252);

			//Debug();
			Sleep(100);
		}
		int selfCollision(){
			for(int i=1;i<size;i++)
			if(cell[0]->IsEqual(cell[i]))
			return 1;
		return 0;	
		}
		void Debug(){
			for(int i=0;i<size;i++)
			cell[i]->Debug();
		}
		
};
int main() 
{
	label:
	system("cls");
	cout<<"WELCOME TO THE WORLD OF SNAKES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	cout<<"1.REGISTER"<<endl;
	cout<<"2.LOGIN"<<endl;
	cout<<"3.EXIT"<<endl;
	string s,p,q,w;
	int x;
	cin>>x;
	if(x==1){
	
			system("cls");
  			ofstream fout;
  			cout<<"ENTER YOUR USERNAME"<<endl;
  			cin>>s;
  			cout<<"ENTER YOUR PASSWORD"<<endl;
  			cin>>p;
  			s=s+p;
  			fout.open("myfile.txt",ios::app);
  			fout<<s+"\n";
  			fout.close();
	}
		else if(x==2){
	
			string line;
			system("cls");
  			ifstream fin;
  			int offset=0;
  			cout<<"ENTER YOUR USERNAME"<<endl;
  			cin>>q;
  			cout<<"ENTER YOUR PASSWORD"<<endl;
  			cin>>w;
  			q=q+w;
  			fin.open("myfile.txt");
  			if(fin.is_open())
  			{
  				while(!fin.eof())
  				{
  					getline(fin,line);
					if(line.find(q,0)!=-1)
					{
						cout<<"you are logged in"<<endl;
						offset=1;
						break;
						  }  	
				}
				if(offset==0)
				{
					cout<<"sorry you are unauthorised to use the game!!"<<endl;
					cout<<"Press 1 and enter to go to home page"<<endl;
					//getch();
					char o;
					cin>>o;
					goto label;
								  }  				
			}
  			fin.close();				
	}	
	else{
		cout<<"Please Select a valid Choice"<<endl;
		goto label;
	}
	setcursor(0,0);
	//random no. generation
	srand((unsigned)time(NULL));

	//Testing snake
	Snake snake;
	char op='1';
	do{
		if(kbhit())
		{
			op=getch();
		}
		switch(op){
			case 'w':
			case 'W':
				snake.TurnUp();
				break;
			case 's':
			case 'S':
				snake.TurnDown();
				break;
			case 'a':
			case 'A':
				snake.TurnLeft();
				break;
			case 'd':
			case 'D':
				snake.TurnRight();
				break;						
		}	
		snake.Move();
	}while(op!='e');
	return 0;
}
