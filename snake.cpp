#include <iostream>
#include<string>
#include "definitions.hpp"



using namespace std;


string name_of_user = "";
int pl,start_s,stop_s;
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

namespace saxenism
{
    class Score
    {
    protected:
        double time_score;
        int high_score;
    public:
        void set_values(double t, int sc)
        {
            time_score = t;
            high_score = sc;
        }
    };

    class User:protected Score
    {protected:
        std::string user_name;
    public:
        User(){};
        User(std::string name, double time, int score)
        {
            user_name = name;
            time_score = time;
            high_score = score;
        }

        void store();
        void retrieve();
        bool retrieve (std::string);
        void update();
        void challenge_score(User*);// To maintain the High Score PS:This is not to display the high score. HIGH SCORE IS DISPLAYED AUTOMATICALLY WHEN A PLAYER FINISHES PLAYING.
        std::string get_Name(){return this->user_name;}// Just a Utility to get the user_name outside of the class

    };

    void User::challenge_score(User *hs)
{
    User High_Scorer;
    std::fstream fin;
    std::string temp;
    fin.open("HS.csv",std::ios::in|std::ios::app);
    fin.seekg(0,std::ios::end);
    if(fin.tellg()==0)
    {
        {
            std::fstream fin1;
            fin1.open("HS.csv",std::ios::out);
            fin1<<hs->user_name<<","<<hs->time_score<<","<<hs->high_score<<"\n";
            fin1.close();

        }

    }
    else
    {   fin.seekg(0,std::ios::beg);
        getline(fin,temp,',');
        High_Scorer.user_name=temp;
        getline(fin,temp,',');
        std::stringstream ss(temp);
        ss >> High_Scorer.high_score;
        getline(fin,temp,'\n');
        std::stringstream ss1(temp);
        ss1>>High_Scorer.high_score;
        if(High_Scorer.high_score < hs->high_score)
        {
            std::cout<<"\t\t\tCONGRATULATION\n\t\tYOU ARE THE HIGHEST SCORER!"<<std::endl;
            {
            std::fstream fin1;
            fin1.open("HS.csv",std::ios::out);
            fin1<<hs->user_name<<","<<hs->time_score<<","<<hs->high_score<<"\n";
            fin1.close();
            }

        }
        else if(High_Scorer.high_score == hs->high_score)
        {
            if(High_Scorer.time_score > hs->time_score)
            {
                std::cout<<"\t\t\tCONGRATULATION\n\t\tYOU ARE THE HIGHEST SCORER!"<<std::endl;
                {
                    std::fstream fin1;
                    fin1.open("HS.csv",std::ios::out);
                    fin1<<hs->user_name<<","<<hs->time_score<<","<<hs->high_score<<"\n";
                    fin1.close();
                }

            }
            else
            {
                std::cout<<"\tHIGHEST SCORER IS "<<High_Scorer.user_name<<" WITH SCORE "<<High_Scorer.high_score<<" AND TIME AVERAGE "<<High_Scorer.time_score<<std::endl;
            }
        }
        else
        {
            std::cout<<"\tHIGHEST SCORER IS "<<High_Scorer.user_name<<" WITH SCORE "<<High_Scorer.high_score<<" AND TIME AVERAGE "<<High_Scorer.time_score<<std::endl;
        }
    }
    std::cout<<"Press any key.......";
    _getch();
    fin.close();
}



    void User::store()
    {
        std::fstream fin;
        fin.open("users.csv", std::ios::app);
        fin << user_name << "," << time_score << "," << high_score << "\n";
        fin.close();
        //challenge_score(this);
    }
    void User::retrieve()
    {
        std::fstream fin;
        fin.open("users.csv", std::ios::in);
        std::string temp;
        std::cout<<"\t\t\SCOREBOARD"<<std::endl;
        std::cout<<"NAME\t\tTIME\t\tSCORE"<<std::endl;
        while(fin)
    {
        std::getline(fin,temp,',');
        std::cout<<temp<<"\t\t";
        std::getline(fin,temp,',');
        std::cout<<temp<<"\t\t";
        std::getline(fin,temp,'\n');
        std::cout<<temp<<"\n";
    }
    fin.close();

    }

    bool User::retrieve(std::string name)
{
    std::fstream fin;
    fin.open("users.csv",std::ios::in);
    std::string temp;
    while(fin)
    {
        std::getline(fin,temp,',');
        if(temp==name)
            return true;
        else
            std::getline(fin,temp,'\n');
    }
    return false;
    fin.close();
}

void User::update()
{
    std::fstream fin,fout;
    fin.open("users.csv",std::ios::in);
    fout.open("usersnew.csv",std::ios::out);
    std::string temp;
    int  i=0,j=0;

    while(fin)
    {
        i++;
        std::getline(fin,temp,',');
        if(temp==user_name)
            break;
        else
            std::getline(fin,temp,'\n');
    }
    fin.close();
    fin.open("users.csv",std::ios::in);
    while(fin)
        {
         j++;
        if(i==j)
        {
            std::getline(fin,temp,'\n');
            fout<<user_name<<","<<time_score<<","<<high_score<<"\n";
        }
        else
        {
            std::getline(fin,temp,'\n');
            fout<<temp<<'\n';

        }
    }
    fin.close();
    fout.close();
    remove("users.csv");
    rename("usersnew.csv","users.csv");
    //challenge_score(this);
}
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

class Human{
	public:
		int x,y;

		int login(){
		int x=rand()%10,y=rand()%10;
		cout<<x<<"+"<<y<<endl;	
		return x+y;	
		}
	public:
		string signUp()
		{
			string spy[10];
			spy[0]="abcde";
			spy[1]="aCbde";
			spy[2]="pAqwer";
			spy[3]="ASDew";
			spy[4]="QwerTy";
			spy[5]="cpp";
			spy[6]="asasasa";
			spy[7]="aqwsSDS";
			spy[8]="poiuyt";
			spy[9]="qwsxZ";
			string pq= spy[rand() % 10];
			cout<<pq<<endl;
			return pq;
		}
	
	
};
class Snake : public Point{
	private:
		Point * cell[MAXSIZE];
		int size;
		char dir;
		Point fruit;
		int state=0;
		int started=0;
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
			cout<<"SELECT YOUR LEVEL"<<endl;
			SetConsoleTextAttribute(console,15);
			cout<<"1.BASIC"<<endl;
			SetConsoleTextAttribute(console,14);
			cout<<"2.MEDIUM"<<endl;
			SetConsoleTextAttribute(console,13);
			cout<<"3.HARD"<<endl;
			SetConsoleTextAttribute(console,4);
			cout<<"4.INSANE"<<endl;
			SetConsoleTextAttribute(console,15);

		}
		void Move(){
			system("cls");
			if(state==0)
			{
				if(!started)
				{
				welcomeScreen();
				cin>>pl;
				cout<<"Press any key to start"<<endl;
				cout << "Press p to pause the game at anytime.\n";
                cout << "Press e to exit the game at anytime.\n";
				getch();
				started=1;
				state=1;
				size=1;
				}
				else{


                    cout<<"Press any key to start"<<endl;
					int high_score = size - 1;
					cout<<"Your Score is: "<<high_score<<endl;
					stop_s=clock();
					cout<<"Total time spent by you playing this game is:"<<endl;
					double time_score = (stop_s-start_s)/double(CLOCKS_PER_SEC);
					cout<< time_score <<"Seconds" << endl;
                    saxenism::User UserObj(name_of_user, time_score, high_score);
					if(!(UserObj.retrieve(name_of_user)))
                    {
                        UserObj.store();
                    }
                    else
                    {
                        UserObj.update();
                    }
                    UserObj.retrieve();

				getch();
				state=1;
				size=1;
				}
			}
						//making snake body follow its head

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
			if(pl==1)
			Sleep(100);
			else if(pl==2)
			Sleep(75);
			else if(pl==3)
			Sleep(50);
			else if(pl==4)
			Sleep(25);
			else
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
	 start_s=clock();
	Human human;		
	label:
	system("cls");
	cout<<"WELCOME TO THE WORLD OF SNAKES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	cout<<"1.REGISTER"<<endl;
	cout<<"2.LOGIN"<<endl;
	cout<<"3.INSTRUCTIONS"<<endl;
	cout<<"4.EXIT"<<endl;
	string p,s,q,w;
	int x;
	cin>>x;
	if(x==1){

			system("cls");
  			ofstream fout;
  			cout<<"ENTER YOUR USERNAME"<<endl;
  			cin>>s;
  			name_of_user = s;
  			cout<<"ENTER YOUR PASSWORD"<<endl;
            cin>>p;
  			s=s+p;
  			ifstream fin;
  			string line;
  			int offset=0;
  			fin.open("myfile.txt");
  			if(fin.is_open())
  			{
  				while(!fin.eof())
  				{
  					getline(fin,line);
					if(line.find(s,0)!=-1)
					{
						cout<<"sorry! this username is not available"<<endl;
						cout<<"Press any key to go to Home Page"<<endl;
						char kk;
						cin>>kk;
						goto label;
						//break;
						  }
				}
			}
  			fin.close();
  			string typed="pp",given="qq";
  			while(typed!=given)
  			{
  				cout<<"Plz enter the give Text"<<endl;
  				given=human.signUp();
  				cin>>typed;
  				if(given!=typed)
  				{
  					cout<<"You seem to be a Robot"<<endl;
  					cout<<"Try Again"<<endl;
				  }
  				
			  }
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
  			name_of_user = q;
  			cout<<"ENTER YOUR PASSWORD"<<endl;
  			cin>>w;
  			int hh=0,gg=1;
  			while(hh!=gg)
  			{
			  
  			cout<<"Prove that you are not a Robot"<<endl;
  			cout<<"Find the sum"<<endl;
  			gg=human.login();
  			cin>>hh;
  			if(hh!=gg)
  			{
  				cout<<"Your Sum is Wrong"<<endl;
  				cout<<"try again"<<endl;
			}
			}
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
	else if(x==3){
		cout<<"This is an Old School Snake Game"<<endl;
		cout<<"Rules"<<endl;
		cout<<"Snake will be controlled by th following keys"<<endl;
		cout<<"To move left use key a"<<endl;
		cout<<"To move right use key d"<<endl;
		cout<<"To move up use key w"<<endl;
		cout<<"To move right use key s"<<endl;
		cout<<"Your Goal is to Eat as much fruits as you can"<<endl;
		cout<<"The Game will End once the head of snake will touch any of its body parts"<<endl;
		cout<<"You are READY TO ROCK"<<endl;
		cout<<"press any key to go to Homepage"<<endl;
		getch();
		goto label;
	}
	else{
		cout<<"press 4 to confirm exit or another key to Register or Login"<<endl;
		int p;
		cin>>p;
		if(p==4)
		return 0;
		goto label;
	}


	setcursor(0,0);
	//random no. generation
//	srand((unsigned)time(NULL));

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
            case 'p':
            case 'P':
                system("pause");
                break;
            case 'e':
            case 'E':
                exit(0);
                break;

		}
		snake.Move();
	}while(op!='e');
	return 0;
}
