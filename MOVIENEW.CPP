//             PROJECT ON MULTIPLEX THEATRE BOOKING SYSTEM
//                       VARUN SIRPAL, XII-D, APS
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<iomanip.h>
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<stdlib.h>
#include<ctype.h>
#include<process.h>

fstream f,f1,f2,f3,f4,f5,f6,f7,f8,f9;

// *******************************************
// CLASS NAME : movie
// DETAILS    : It controls all functioning of
//              data related to movies
//********************************************

class movie
{
	char mno[6];
	char mname[50];
	char lname[20];
	char stime[15];
	int aseat;
  public:
	void create_movie()
	{
		cout<<"\nNEW MOVIE ENTRY...\n";
		cout<<"\nEnter The Movie Code :: ";
		cin>>mno;
		cout<<"\n\nEnter The Name & Type of The Movie :: ";
		gets(mname);
		cout<<"\n\nEnter The Language of Movie :: ";
		gets(lname);
		cout<<"\n\nEnter Show Time :: ";
		gets(stime);
		cout<<"\n\nEnter No. of available seats :: ";
		cin>>aseat;
		cout<<"\n\n\nMovie Created..";
	}

	void show_movie()
	{
		cout<<"\nMovie Code :: "<<mno;
		cout<<"\nMovie Name :: ";
		puts(mname);
		cout<<"\nMovie Language :: ";
		puts(lname);
		cout<<"\nShow Time :: ";
		puts(stime);
		cout<<"\nNo. of Available Seats :: "<<aseat;
	}

	void modify_movie()
	{
		cout<<"\nMovie Code :: "<<mno;
		cout<<"\nModify Movie Name :: ";
		gets(mname);
		cout<<"\nModify Language of Movie :: ";
		gets(lname);
		cout<<"\nModify Show Time :: ";
		gets(stime);
		cout<<"\nModify No. of Available Seats :: ";
		cin>>aseat;
	}
	void modify_seat(int aas)
	{
		aseat=aseat-aas;
	}
	void modify_seat1(int aas)
	{
		aseat=aseat+aas;
	}
	char* retmno()
	{
		return mno;
	}
	char* retmname()
	{
		return mname;
	}
	char* retstime()
	{
		return stime;
	}
	int retaseat()
	{
		return aseat;
	}
	void report()
	{cout<<mno<<setw(20)<<mname<<setw(15)<<lname<<setw(15)<<stime<<setw(15)<<aseat<<endl;}



};         //class ends here

fstream fp,fp1;
movie bk;

//**********************************************************
//	CLASS NAME : MUTLIPLEX
//	DETAILS    : IT CONTROLS OVER ALL FUNCTIONING
//                   OF THE MULTIPLEX CINEMA BOOKING SYSTEM
//**********************************************************

class MULTIPLEX
{
	char array[100], seat[50];
	struct bill_food_court
	{ long bfood,bcourt;
	} b[100];
	struct booking_data
	{
	  int charge,bookingno,noofseats;
	  char name[25],eaddress[30],mobileno[15],date[11],moviename[25],stime[15];
	} d;
	struct cancellation_data
	{
	  char name[25],eaddress[75],mobileno[15];
	} D;
	struct member_water_park_data
	{
	  char name[25],eaddress[30],mobileno[15],date[11];
	  int memno;
	} ms;
	public:
	void booking();
	void cancellation();
	void taxi_service();
	void foodcourt();
	void water_park();
	void admin_data();
} 	H;

// Class ends here

void write_movie()
{
	char ch;
	fp.open("MOVIE.DAT",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_movie();
		fp.write((char*)&bk,sizeof(movie));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void display_spb(char n[])
{
	cout<<"\nMOVIE DETAILS\n";
	int flag=0;
	fp.open("MOVIE.DAT",ios::in|ios::app);
	while(fp.read((char*)&bk,sizeof(movie)))
	{
		if(strcmpi(bk.retmno(),n)==0)
		{
			bk.show_movie();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nMovie does not exist";
	getch();
}
void modify_movie()
{
	char n[6];
	int found=0;
	cout<<"\n\n\tMODIFY MOVIE REOCORD.... ";
	cout<<"\n\n\tEnter The Movie no. of The Movie";
	cin>>n;
	fp.open("MOVIE.DAT",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(movie)) && found==0)
	{
		if(strcmpi(bk.retmno(),n)==0)
		{
			bk.show_movie();
			cout<<"\nEnter The New Details of Movie"<<endl;
			bk.modify_movie();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(movie));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

void delete_movie()
{
	char n[6];
	cout<<"\n\n\n\tDELETE MOVIE ...";
	cout<<"\n\nEnter The Movie no. of the Movie You Want To Delete : ";
	cin>>n;
	fp.open("MOVIE.DAT",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(movie)))
	{
		if(strcmpi(bk.retmno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(movie));
		}
	}

	fp2.close();
	fp.close();
	remove("MOVIE.DAT");
	rename("Temp.dat","MOVIE.DAT");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}

void display_allm()
{
	fp.open("MOVIE.DAT",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tMOVIE LIST\n\n";
	cout<<"================================================================================\n";
	cout<<"Movie No."<<setw(15)<<"Movie Name"<<setw(15)<<"Language"<<setw(15)<<"Show Time"<<setw(15)<<"Seats\n";
	cout<<"================================================================================\n";

	while(fp.read((char*)&bk,sizeof(movie)))
	{
		bk.report();
	}
	fp.close();

}

//**********************************************************
//	FUNCTION NAME 	  : booking
//**********************************************************


void MULTIPLEX::booking ()
{
	textcolor(2);
	clrscr();
	int c=0;
	//FINDING AN UNOCCUPIED BOOKING NO.
	f.open("ARRAY.DAT",ios::in|ios::binary);
	f.read((char *)&array,sizeof(array));
	while(array[c]!='e') c++;
	array[c]='o';
	f.close();
	f.open("ARRAY.DAT",ios::out|ios::binary);
	f.write((char *)&array,sizeof(array));
	f.close();
	f1.open("MULTIPLEX.DAT",ios::app|ios::binary);
	d.bookingno=c+1;
	//DATA OF THE CUSTOMER
	cout<<"ENTER THE REQUIRED DATA\n"
	    <<"NAME :: ";
	gets(d.name);
	int l=strlen(d.name);
	for(int i=0;i<l;i++) d.name[i]=toupper(d.name[i]);
	cout<<"EMAIL ADDRESS :: ";
	gets(d.eaddress);
	cout<<"MOBILE No. :: ";
	gets(d.mobileno);
	cout<<"DATE WHEN YOU WANT TO WATCH MOVIE (dd/mm/yyyy) :: ";
	gets(d.date);
	cout<<"HOW MANY SEATS REQUIRED? :: ";
	cin>>d.noofseats;
	display_allm();
	REDO:
	int flag=0;
	char bn[6];
	cout<<"\n\n\tEnter the Movie no. ";
	cin>>bn;
	fp.open("MOVIE.DAT",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(movie)))
	{
		if(strcmpi(bk.retmno(),bn)==0)
		{
			if (bk.retaseat()>0)
			{
			flag=1;
			strcpy(d.moviename,bk.retmname());
			d.charge=200;
			strcpy(d.stime,bk.retstime());
			bk.modify_seat(d.noofseats);
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(movie));
			}
			else
			{
			cout<<"\nHouse Full";
			cout<<"\n\nPress any key to go back to Main Menu";
			getch();
			flag=2;
			}
		}
	}
	fp.close();
	if(flag==0)
	{
		cout<<"\n\nMovie does not exist";
		goto REDO;
	}
	clrscr();
	if(flag==1)
	{
	cout<<"YOUR MOVIE BOOKING NO. IS :: "<<d.bookingno<<"\n";
	cout<<"CHARGES:: "<<d.noofseats*d.charge<<" + 8% GST\n";
	gotoxy(25,25);
	cout<<"MAKE PAYMENT & PRESS ANY KEY TO PRINT TICKET";
	getch();
	clrscr();
		gotoxy(25,1); cout<<"**** TICKET ****\n\n";
	cout<<endl;
	cout<<"\t\tBOOKING NUMBER    :: "<<d.bookingno<<"\n"
	    <<"\t\tNAME              :: "<<d.name<<"\n"
	    <<"\t\tEMAIL ADDRESS     :: "<<d.eaddress<<"\n"
	    <<"\t\tMOBILE  NO.       :: "<<d.mobileno<<"\n"
	    <<"\t\tMOVIE DATE        :: "<<d.date<<"\n"
	    <<"\t\tMOVIE NAME        :: "<<d.moviename<<"\n"
	    <<"\t\tSHOW TIME         :: "<<d.stime<<"\n"
	    <<"\t\tNO. OF SEATS      :: "<<d.noofseats<<"\n"
	    <<"\t\tSEAT NO.          :: ";
	    for(i=1;i<=d.noofseats;i++)
	    {
	    cout<<char(64+i)<<d.bookingno<<" ";
	    }
	    cout<<"\n";
	cout<<"\t\tPAYMENT MADE (Rs) :: "<<d.noofseats*d.charge<<"\n";
	gotoxy(25,25);
	cout<<"PRINT TICKET AND PRESS ANY KEY TO GO BACK TO MENU";
	getch();
	//COPYING THE RECORD OF THE CUSTOMER INTO A FILE
	f1.write((char *)&d,sizeof(d));
	f1.close();
	clrscr();
	}
}
void MULTIPLEX::cancellation()
{
	textcolor(1);
	clrscr();
	int rn;
	cout<<"BOOKING NUMBER  :: ";
	cin>>rn;
	f1.open("MULTIPLEX.DAT",ios::in|ios::binary);
	do f1.read((char*)&d,sizeof(d)); while(d.bookingno!=rn);
	cout<<"NAME         :: "<<d.name<<"\n"
	    <<"EMAIL ADDRESS:: "<<d.eaddress<<"\n"
	    <<"MOBILE NO.   :: "<<d.mobileno<<"\n"
	    <<"MOVIE NAME   :: "<<d.moviename<<"\n"
	    <<"MOVIE DATE   :: "<<d.date<<"\n"
	    <<"SHOW TIME    :: "<<d.stime<<"\n"
	    <<"NO. OF SEATS :: "<<d.noofseats<<"\n"
	    <<"YOUR TICKETS ARE CANCELLED AND MONEY REFUNDED.\n";

	fp.open("MOVIE.DAT",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(movie)))
	{
		if(strcmpi(bk.retmname(),d.moviename)==0)
		{
			bk.modify_seat1(d.noofseats);
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(movie));
		 }
	}
	fp.close();
	//COPYING THE RECORD OF THE CUSTOMER INTO ANOTHER FILE
	f3.open("CANCEL.DAT",ios::app|ios::binary);
	strcpy(D.name,d.name);
	strcpy(D.eaddress,d.eaddress);
	strcpy(D.mobileno,d.mobileno);
	f3.write((char *)&D,sizeof(D));
	f3.close();
	f1.close();
	//MAKING THE BOOKING NO ALLOTED TO THE CUSTOMER AS EMPTY
	f.open("ARRAY.DAT",ios::in|ios::binary);
	f.read((char *)&array,sizeof(array));
	array[rn-1]='e';
	f.close();
	f.open("ARRAY.DAT",ios::out|ios::binary);
	f.write((char *)&array,sizeof(array));
	f.close();
	fstream e;
	//DELETING THE RECORD OF THE CUSTOMER
	f1.open("MULTIPLEX.DAT",ios::in|ios::binary);
	e.open("F1.DAT",ios::out|ios::binary);
	f1.read((char *)&d,sizeof(d));
	while(f1)
	{
	  if(d.bookingno!=rn)
	  {
	    e.write((char *)&d,sizeof(d));
	    f1.read((char *)&d,sizeof(d));
	  }
	  else f1.read((char *)&d,sizeof(d));
	}
	e.close();
	f1.close();
	f1.open("MULTIPLEX.DAT",ios::out|ios::binary);
	e.open("F1.DAT",ios::in|ios::binary);
	e.read((char *)&d,sizeof(d));
	while(e)
	{
	  f1.write((char *)&d,sizeof(d));
	  e.read((char *)&d,sizeof(d));
	}
	e.close();
	f1.close();
	gotoxy(25,25);
	cout<<"PRESS ANY KEY TO GO BACK TO MENU";
	getch();
	clrscr();
}
void MULTIPLEX::taxi_service()
{
	int gd=DETECT,gm,choice;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	settextstyle(10,0,1);
	int x=40,y=30;
	setcolor(BROWN);
	outtextxy(50,40,"I am a Visitor of PVR Multiplex");
	outtextxy(x,y,".");
	setcolor(CYAN);
	outtextxy(50,80,"I am not a Visitor of PVR Multiplex");
	char W;
	int count=0;
	do
	{
	  count++;
	  W=getch();
	  if(W=='\0'+'H')
	  {
	    setcolor(BLACK);
	    outtextxy(x,y,".");
	    y-=40;
	    if(y<30)
	    {
	      y=70;
	      setcolor(CYAN);
	      outtextxy(x,y,".");
	      choice=2;
	    }
	    else if(y==30)
	    {
	      setcolor(BROWN);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==70)
	    {
	      setcolor(CYAN);
	      outtextxy(x,y,".");
	      choice=2;
	    }
	  }
	  else if(W=='\0'+'P')
	  {
	    setcolor(BLACK);
	    outtextxy(x,y,".");
	    y+=40;
	    if(y>70)
	    {
	      y=30;
	      setcolor(BROWN);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==30)
	    {
	      setcolor(BROWN);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==70)
	    {
	      setcolor(CYAN);
	      outtextxy(x,y,".");
	      choice=2;
	    }
	  }
	  else if(count==1 && W==13) choice=1;
	} while(W!=13);
	closegraph();
	textcolor(8);
	clrscr();
	if(choice==2)
	{
	cout<<"\n\nSORRY.THIS FACILITY IS ONLY FOR VISITORS OF PVR MULTIPLEX"
	    <<"\nYOU CAN NOT USE THIS FACILITY";
	gotoxy(20,12);
	cout<<"PRESS ANY KEY TO GO BACK TO MENU";
	getch();
	return;
	}
	if(choice==1)
	{
	  char n[25],t[6],date[11];
	  int x,room;
	  cout<<"BOOKING NUMBER :: ";
	  cin>>room;
	  cout<<"NAME        :: ";
	  gets(n);
	  int l=strlen(n);
	  for(int i=0;i<l;i++) n[i]=toupper(n[i]);
	  //VERIFYING THE ENTERED DATA
	  f1.open("MULTIPLEX.DAT",ios::in|ios::binary);
	  f1.read((char *)&d,sizeof(d));
	  while(f1)
	  {
	    if(d.bookingno==room && strcmp(d.name,n)==0)
	    {
	      f1.close();
	      goto PROCEED;
	    }
	    f1.read((char *)&d,sizeof(d));
	  }
	  f1.close();
	  clrscr();
	  cout<<"SORRY.ENTERED DATA IS NOT MATCHING THE ACTUAL DATA"
	      <<"\nYOU CAN NOT USE THIS FACILITY";
	  gotoxy(25,25);
	  cout<<"PRESS ANY KEY TO CONTINUE";
	  getch();
	  return;
	  PROCEED:
	  cout<<"NO. OF TAXIS NEEDED      :: ";
	  cin>>x;
	  cout<<"TAXI(s) NEEDED ON (date) :: ";
	  gets(date);
	  cout<<"TAXI(s) NEEDED AT (time) :: ";
	  gets(t);
	  clrscr();
	  if(x==1)
	    cout<<"A TAXI WILL BE WAITING FOR YOU AT "<<t
		<<" ON "<<date<<" OUTSIDE THE PVR MULTIPLEX GATE";
	  else
	    cout<<x<<" TAXIS WILL BE WAITING FOR YOU AT "<<t
		<<" ON "<<date<<" OUTSIDE THE PVR MULTIPLEX GATE";
	  gotoxy(25,25);
	  cout<<"PRESS ANY KEY TO GO BACK TO MENU";
	  getch();
	}
	clrscr();
}
void MULTIPLEX::foodcourt()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	cleardevice();
	setbkcolor(RED);
	settextstyle(8,0,4);
	setcolor(YELLOW);
	delay(1000);
	outtextxy(50,150,"WELCOME TO THE RESTAURANT");
	delay(2000);
	outtextxy(100,200,"PLEASE TAKE YOUR SEAT");
	delay(2000);
	closegraph();
	int price[113]={245,245,245,245,240,240,240,240,235,235,250,235,235,
	220,215,230,215,240,250,250,250,250,250,250,250,255,245,245,245,245,
	250,240,240,360,290,360,290,370,295,360,290,360,290,250,360,290,360,
	290,250,370,290,360,290,250,250,280,245,290,235,265,240,290,300,256,
	240,265,270,255,255,240,240,235,220,25,30,25,30,35,35,25,30,35,25,35,
	25,25,30,100,105,105,100,105,100,105,125,105,105,100,105,110,115,100,
	100,100,105,105,105,105,125,105,120,120,100};
	char food[113][30]={"SHAHI PANEER","KADAI PANEER","CHEESE KORMA",
	"MALAI KOFTA","MATAR PANEER","PALAK PANEER","MIX VEG.","ALOO GOBI",
	"ALOO JEERA","CHANA MASALA","MATAR MUSHROOM","RAJMA MAKHANI",
	"DAL MAKHANI","MIXED RAITA","BUNDI RAITA","PINEAPPLE RAITA",
	"SALAD(GREEN)","DUM ALOO","MUSHROOM PANEER","MUTTON MASALA",
	"MUTTON MUGHLAI","MUTTON KORMA","MUTTON DO PYAZA","MUTTON SAGH",
	"MUTTON DAHI","MUTTON ROGAN JOSH","MUTTON CURRY","KADAI MUTTON",
	"KEEMA LEVER","KEEMA MATAR","KEEMA EGG","BRAIN CURRY","EGG CURRY",
	"BUTTER CHICKEN","BUTTER CHICKEN(1/2)","KADAI CHICKEN",
	"KADAI CHICKEN(1/2)","BUTTER CHICKEN(BL)","BUTTER CHICKEN(BL)(1/2)",
	"CHICKEN MUGHLAI","CHICKEN MUGHLAI(1/2)","CHICKEN MASALA",
	"CHICKEN MASALA(1/2)","CHICKEN MASALA(1/4)","CHICKEN SAGH",
	"CHICKEN SAGH(1/2)","CHICKEN DAHI","CHICKEN DAHI(1/2)",
	"CHICKEN DAHI(1/4)","CHICKEN KORMA","CHICKEN KORMA(1/2)",
	"CHICKEN DO PYAZA","CHICKEN DO PYAZA(1/2)","FISH CURRY",
	"CHICKEN CURRY","CHICKEN CURRY(1/2)","CHICKEN CURRY(1/4)",
	"CHILLI CHICKEN","TANDOORI ALOO","CHICKEN TIKKA","SEEKH KABAB",
	"FISH TIKKA","CHICKEN TANDOORI","CHICKEN TANDOORI(1/2)",
	"PANEER TIKKA","CHICKEN SEEKH KABAB","CHICKEN HARA KABAB",
	"CHICKEN BIRYANI","MUTTON BIRYANI","PANEER PULAO","VEG.PULAO",
	"JEERA RICE","STEAMED RICE","RUMALI ROTI","ROTI","NAN","ALOO NAN",
	"PANEER NAN","KEEMA NAN","PARANTHA","ALOO PARANTHA",
	"PANEER PARANTHA","PUDINA PARANTHA","BUTTER NAN","LACHCHA PARANTHA",
	"MISSI ROTI","KHASTA ROTI","VEG.BURGER","PANEER BURGER",
	"CHEESE SANDWICH","VEG.PATTI","CHICKEN PATTI","TEA","COFFEE",
	"COLD COFFEE","PINEAPPLE","STRAWBERRY","CHOCOLATE","BLACK FOREST",
	"DOUBLE STORIED","TRIPLE STORIED","SOFT CONE","VANILLA","STRAWBERRY",
	"CHOCOLATE","CHOCO CHIPS","MANGO","TUTTI FRUITY","LICHI",
	"PISTA BADAM","CHOCOLATE PISTA BADAM","CHOCO DIP","CHOCOLATE LICHI"};
	START:
	textcolor(4);
	clrscr();
	gotoxy(31,1); cout<<"*********";
	gotoxy(31,2); cout<<"MENU CARD";
	gotoxy(31,3); cout<<"*********";
	gotoxy(31,5); cout<<"VEGETARIAN";
	for(int i=0;i<15;i++)
	{
	  gotoxy(15,i+7); cout<<i+1;
	  gotoxy(30,i+7); cout<<food[i];
	  gotoxy(55,i+7); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	for(i=15;i<19;i++)
	{
	  gotoxy(15,i-14); cout<<i+1;
	  gotoxy(30,i-14); cout<<food[i];
	  gotoxy(55,i-14); cout<<price[i];
	}
	gotoxy(33,7); cout<<"MUTTON";
	for(i=19;i<33;i++)
	{
	  gotoxy(15,i-10); cout<<i+1;
	  gotoxy(30,i-10); cout<<food[i];
	  gotoxy(55,i-10); cout<<price[i];
	}
	gotoxy(25,25) ;cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(31,1); cout<<"CHICKEN";
	for(i=33;i<54;i++)
	{
	  gotoxy(15,i-30); cout<<i+1;
	  gotoxy(25,i-30); cout<<food[i];
	  gotoxy(55,i-30); cout<<price[i];
	}
	gotoxy(25,25) ;cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	for(i=54;i<58;i++)
	{
	  gotoxy(15,i-53); cout<<i+1;
	  gotoxy(30,i-53); cout<<food[i];
	  gotoxy(55,i-53); cout<<price[i];
	}
	gotoxy(31,7); cout<<"BAR-BE-QUE";
	for(i=58;i<73;i++)
	{
	  gotoxy(15,i-49); cout<<i+1;
	  gotoxy(30,i-49); cout<<food[i];
	  gotoxy(55,i-49); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(30,1); cout<<"ROTI-NAN-PARANTHA";
	for(i=73;i<92;i++)
	{
	  gotoxy(15,i-70); cout<<i+1;
	  gotoxy(30,i-70); cout<<food[i];
	  gotoxy(55,i-70); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(30,1); cout<<"BEVERAGES";
	for(i=92;i<95;i++)
	{
	  gotoxy(15,i-89); cout<<i+1;
	  gotoxy(30,i-89); cout<<food[i];
	  gotoxy(55,i-89); cout<<price[i];
	}
	gotoxy(30,8) ;cout<<"PASTRIES";
	for(i=95;i<101;i++)
	{
	  gotoxy(15,i-85); cout<<i+1;
	  gotoxy(30,i-85); cout<<food[i];
	  gotoxy(55,i-85); cout<<price[i];
	}
	gotoxy(25,25); cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	gotoxy(30,1); cout<<"ICE-CREAMS";
	for(i=101;i<113;i++)
	{
	  gotoxy(15,i-98); cout<<i+1;
	  gotoxy(30,i-98); cout<<food[i];
	  gotoxy(55,i-98); cout<<price[i];
	}
	gotoxy(25,25);cout<<"PRESS ANY KEY TO CONTINUE"; getch();
	clrscr();
	int answ,fc,fch[113],fe=0,z=-1;
	char fi[113][30],answe;
	RETRY:
	clrscr();
	cout<<"PRESS 0 TO GO BACK TO MENU CARD\n"
	    <<"PRESS 1 TO CONTINUE ";
	cin>>answ;
	switch(answ)
	{
	  case 0 : goto START;
	  case 1 : clrscr();
		   do
		   {
		     z++;
		     cout<<"ENTER THE FOOD CODE YOU WANT TO HAVE :: ";
		     cin>>fc;
		     fch[z]=price[fc-1];
		     fe+=price[fc-1];
		     strcpy(fi[z],food[fc-1]);
		     cout<<"DO YOU WANT MORE(Y/N) :: ";
		     cin>>answe;
		   } while(answe=='y' || answe=='Y');
		   clrscr();
		   for(int y=0;y<z+1;y++)
		   {
		     cout<<fi[y];
		     gotoxy(40,y+1); cout<<fch[y]<<"\n";
		   }
		   cout<<"TOTAL";
		   gotoxy(40,y+1); cout<<fe<<"\n";
		   cout<<"ARE YOU WATCHING MOVIE (Y/N) ? ";
		   char ans;
		   cin>>ans;

		   if(ans=='y' || ans=='Y')
		   {
		     char na[25];
		     int rn;
		     cout<<"BOOKING NO. :: ";
		     cin>>rn;
		     cout<<"NAME     :: ";
		     gets(na);
		     for(i=0;na[i]!='\0';i++) na[i]=toupper(na[i]);
		     //VERIFYING THE ENTERED DATA
		     f1.open("MULTIPLEX.DAT",ios::in|ios::binary);
		     f1.read((char *)&d,sizeof(d));
		     while(f1)
		     {
		       if(d.bookingno==rn && strcmp(d.name,na)==0)
		       {
			 f1.close();
			 goto BILL;
		       }
		       f1.read((char *)&d,sizeof(d));
		     }
		     f1.close();
		     cout<<"ENTERED DATA IS NOT MATCHING THE ACTUAL DATA";
		     gotoxy(25,25); cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     getch();
		     return;
		     BILL:
		     //ENTERING THE FOOD COURT CHARGE INTO THE FILE
		     f8.open("BILL.DAT",ios::in|ios::binary);
		     f8.read((char *)&b,sizeof(b));
		     int first=0;
		     cout<<" \nVisiting first ";
		     cout<<" \nPress 1 if Yes ";
		     cout<<" \nPress 0 if No";
		     cin>>first;
		     if (first == 1)
		     {
		     b[rn-1].bfood = 0;
		     b[rn-1].bfood+=fe;
		     }
		     else
		     b[rn-1].bfood+=fe;
		     f8.close();
		     f8.open("BILL.DAT",ios::out|ios::binary);
		     f8.write((char *)&b,sizeof(b));
		     f8.close();
		     cout<<"YOU WILL BE DELIVERED EATABLES AT YOUR SEATS. PLEASE PAY TO THE DELIVERY BOY.";
		   }
		   else
		   {
		     gotoxy(25,25);
		     cout<<"PRESS ANY KEY AFTER PAYING THE BILL ";
		     getch();
		     return;
		   }
		   gotoxy(25,25);
		   cout<<"PRESS ANY KEY TO CONTINUE";
		   getch();
		   break;
	  default: cout<<"YOU HAVE PRESSED A WRONG KEY\nRETRY\n";
		   getch();
		   goto RETRY;
	}
	clrscr();
}

void MULTIPLEX::water_park()
{
	START:
	clrscr();
	int choice;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	cleardevice();
	settextstyle(10,0,1);
	setcolor(MAGENTA);
	outtextxy(10,50,"I am visitor of Multiplex Theatre");
	setcolor(LIGHTRED);
	outtextxy(10,90,"I am a member of this facility");
	setcolor(LIGHTGREEN);
	outtextxy(10,130,"I want to be its member");
	setcolor(RED);
	outtextxy(10,170,"Back to options");
	setcolor(MAGENTA);
	int x=0,y=40;
	outtextxy(x,y,".");
	char W;
	int count=0;
	do
	{
	  count++;
	  W=getch();
	  if(W=='\0'+'H')
	  {
	    setcolor(BLACK);
	    outtextxy(x,y,".");
	    y-=40;
	    if(y<40)
	    {
	      y=160;
	      setcolor(RED);
	      outtextxy(x,y,".");
	      choice=5;
	    }
	    else if(y==40)
	    {
	      setcolor(MAGENTA);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==80)
	    {
	      setcolor(LIGHTRED);
	      outtextxy(x,y,".");
	      choice=2;
	    }
	    else if(y==120)
	    {
	      setcolor(LIGHTGREEN);
	      outtextxy(x,y,".");
	      choice=3;
	    }
	    else if(y==160)
	    {
	      setcolor(RED);
	      outtextxy(x,y,".");
	      choice=5;
	    }
	  }
	  else if(W=='\0'+'P')
	  {
	    setcolor(BLACK);
	    outtextxy(x,y,".");
	    y+=40;
	    if(y>160)
	    {
	      y=40;
	      setcolor(MAGENTA);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==40)
	    {
	      setcolor(MAGENTA);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==80)
	    {
	      setcolor(LIGHTRED);
	      outtextxy(x,y,".");
	      choice=2;
	    }
	    else if(y==120)
	    {
	      setcolor(LIGHTGREEN);
	      outtextxy(x,y,".");
	      choice=3;
	    }
	    else if(y==160)
	    {
	      setcolor(RED);
	      outtextxy(x,y,".");
	      choice=5;
	    }
	  }
	  else if(count==1&&W==13) choice=1;
	} while(W!=13);
	closegraph();
	char na[25];
	switch(choice)
	{
	  case 1 : textcolor(9);
		   clrscr();
		   int rn;
		   cout<<"BOOKING NUMBER :: ";
		   cin>>rn;
		   cout<<"NAME        :: ";
		   gets(na);
		   int l=strlen(na);
		   for(int i=0;i<l;i++) na[i]=toupper(na[i]);
		   //VERIFYING THE ENTERED DATA
		   f1.open("MULTIPLEX.DAT",ios::in|ios::binary);
		   f1.read((char *)&d,sizeof(d));
		   while(f1)
		   {
		     if(d.bookingno==rn && strcmp(d.name,na)==0)
		     {
		       f1.close();
		       cout<<"\n\nYOU MAY USE THIS FACILITY";
		       goto PROCEED;
		     }
		     f1.read((char *)&d,sizeof(d));
		   }
		   f1.close();
		   cout<<"\n\nSORRY.ENTERED DATA IS NOT MATCHING THE ACTUAL DATA"
		       <<"\nYOU CAN NOT USE THIS FACILITY";
		   PROCEED:
		   gotoxy(25,25);
		   cout<<"PRESS ANY KEY TO CONTINUE";
		   getch();
		   goto START;
	  case 2 : textcolor(8);
		   clrscr();
		   char od[11],id[11];
		   int mems;
		   cout<<"MEMBERSHIP NUMBER :: ";
		   cin>>mems;
		   cout<<"NAME              :: ";
		   gets(na);
		   l=strlen(na);
		   for(i=0;i<l;i++) na[i]=toupper(na[i]);
		   cout<<"TODAY'S DATE(dd/mm/yyyy) :: ";
		   gets(od);
		   //VERIFYING THE ENTERED DATA
		   f4.open("WATER.DAT",ios::in|ios::binary);
		   while(f4)
		   {
		     f4.read((char *)&ms,sizeof(ms));
		     if(ms.memno==mems && strcmp(ms.name,na)==0)
		     {
		       //CHECKING IF THE MEMBERSHIP CARD IS VALID
		       int dd1,dd2,mm1,mm2,yy1,yy2,p,q,r;
		       dd1=(ms.date[0]-48)*10+(ms.date[1]-48);
		       dd2=(od[0]-48)*10+(od[1]-48);
		       mm1=(ms.date[3]-48)*10+(ms.date[4]-48);
		       mm2=(od[3]-48)*10+(od[4]-48);
		       yy1=(ms.date[6]-48)*1000+(ms.date[7]-48)*100+(ms.date[8]-48)*10+(ms.date[9]-48);
		       yy2=(od[6]-48)*1000+(od[7]-48)*100+(od[8]-48)*10+(od[9]-48);
		       if((yy2-yy1)>1)
		       {
			 f4.close();
			 cout<<"\n\nVALIDITY OF YOUR MEMBERSHIP CARD IS OVER"
			     <<"\nYOU WILL HAVE TO MAKE A NEW MEMBERSHIP CARD";
			 goto END;
		       }
		       else if(yy1==yy2 || mm1>mm2)
		       {
			 f4.close();
			 cout<<"\n\nYOU MAY USE THIS FACILITY";
			 goto END;
		       }
		       else if(mm1==mm2)
		       {
			 if(dd1>=dd2)
			 {
			   f4.close();
			   cout<<"\n\nYOU MAY USE THIS FACILITY";
			   goto END;
			 }
			 else
			 {
			   f4.close();
			   cout<<"\n\nVALIDITY OF YOUR MEMBERSHIP CARD IS OVER"
			       <<"\nYOU WILL HAVE TO MAKE A NEW MEMBERSHIP CARD";
			   goto END;
			 }
		       }
		       else
		       {
			 f4.close();
			 cout<<"\n\nVALIDITY OF YOUR MEMBERSHIP CARD IS OVER\n"
			     <<"YOU WILL HAVE TO MAKE A NEW MEMBERSHIP CARD";
			 goto END;
		       }
		     }
		   }
		   f4.close();
		   cout<<"\n\nSORRY.ENTERED DATA IS NOT MATCHING THE ACTUAL DATA"
		       <<"\nYOU CAN NOT USE THIS FACILITY";
		   END:
		   gotoxy(25,25);
		   cout<<"PRESS ANY KEY TO CONTINUE";
		   getch();
		   goto START;
	  case 3 : textcolor(1);
		   clrscr();
		   char datete[5];
		   f4.open("WATER.DAT",ios::app|ios::binary);
		   //DATA OF THE MEMBER
		   cout<<"ENTER THE REQUIRED DATA\n";
		   cout<<"NAME :: ";
		   gets(ms.name);
		   l=strlen(ms.name);
		   for(i=0;i<l;i++) ms.name[i]=toupper(ms.name[i]);
		   cout<<"EMAIL ADDRESS :: ";
		   gets(ms.eaddress);
		   cout<<"MOBILE NUMBER :: ";
		   gets(ms.mobileno);
		   cout<<"TODAY'S DATE(dd/mm/yyyy) :: ";
		   gets(ms.date);
		   for(int z=0;z<6;z++) datete[z]=ms.date[z];
		   //CALCULATING THE DATE TILL WHICH THE MEMBERSHIP CARD IS VALID
		   int a,b,c,d,e,q;
		   a=ms.date[6]-48;
		   b=ms.date[7]-48;
		   c=ms.date[8]-48;
		   d=ms.date[9]-48;
		   e=a*1000+b*100+c*10+d+1;
		   //GIVING THE MEMBRESHIP NO.
		   f5.open("D.DAT",ios::in|ios::binary);
		   f5.read((char *)&q,2);
		   ms.memno=q;
		   q++;
		   f5.close();
		   f5.open("D.DAT",ios::out|ios::binary);
		   f5.write((char *)&q,2);
		   f5.close();
		   clrscr();
		   cout<<"PRESS ANY KEY AFTER PAYING MEMBERSHIP FEES"
		       <<" OF Rs 10000 FOR ONE YEAR\n";
		   getch();
		   textcolor(2);
		   clrscr();
		   cout<<"\t\t\t**** MEMBERSHIP CARD ****\n\n"
		       <<"\t\t\tNAME           :: "<<ms.name<<"\n"
		       <<"\t\t\tEMAIL ADDRESS  :: "<<ms.eaddress<<"\n"
		       <<"\t\t\tMOBILE NO.     :: "<<ms.mobileno<<"\n"
		       <<"\t\t\tMEMBERSHIP NO. :: "<<ms.memno<<"\n"
		       <<"\t\t\tVALID TILL     :: ";
		   for(z=0;z<6;z++) cout<<datete[z];
		   cout<<e<<"\n";
		   //ENTERING THE RECORD OF THE MEMBER INTO A FILE
		   f4.write((char *)&ms,sizeof(ms));
		   f4.close();
		   gotoxy(25,25);
		   cout<<"PRESS ANY KEY TO CONTINUE";
		   getch();
		   goto START;
	}
	clrscr();
}
void MULTIPLEX::admin_data()
{
	START:
	int choice;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
	cleardevice();
	settextstyle(10,0,2);
	setcolor(LIGHTBLUE);
	outtextxy(10,5,"Please make your Choice :");
	setcolor(YELLOW);
	settextstyle(10,0,1);
	outtextxy(50,85,"Create Movie");
	setcolor(LIGHTRED);
	outtextxy(50,125,"Modify Movie");
	setcolor(DARKGRAY);
	outtextxy(50,165,"Delete Movie");
	setcolor(RED);
	outtextxy(50,205,"Display Specific Movie");
	setcolor(CYAN);
	outtextxy(50,245,"Display All Customers");
	setcolor(WHITE);
	outtextxy(50,285,"Back to options");
	setcolor(YELLOW);
	int x=40,y=77;
	outtextxy(x,y,".");
	char W;
	int count=0;
	do
	{
	  count++;
	  W=getch();
	  if(W=='\0'+'H')
	  {
	    setcolor(BLACK);
	    outtextxy(x,y,".");
	    y-=40;
	    if(y<77)
	    {
	      y=277;
	      setcolor(WHITE);
	      outtextxy(x,y,".");
	      choice=6;
	    }
	    else if(y==77)
	    {
	      setcolor(YELLOW);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==117)
	    {
	      setcolor(LIGHTRED);
	      outtextxy(x,y,".");
	      choice=2;
	    }
	    else if(y==157)
	    {
	      setcolor(DARKGRAY);
	      outtextxy(x,y,".");
	      choice=3;
	    }
	    else if(y==197)
	    {
	      setcolor(RED);
	      outtextxy(x,y,".");
	      choice=4;
	    }
	    else if(y==237)
	    {
	      setcolor(CYAN);
	      outtextxy(x,y,".");
	      choice=5;
	    }
	    else if(y==277)
	    {
	      setcolor(WHITE);
	      outtextxy(x,y,".");
	      choice=6;
	    }
	  }
	  else if(W=='\0'+'P')
	  {
	    setcolor(BLACK);
	    outtextxy(x,y,".");
	    y+=40;
	    if(y>277)
	    {
	      y=77;
	      setcolor(YELLOW);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==77)
	    {
	      setcolor(YELLOW);
	      outtextxy(x,y,".");
	      choice=1;
	    }
	    else if(y==117)
	    {
	      setcolor(LIGHTRED);
	      outtextxy(x,y,".");
	      choice=2;
	    }
	    else if(y==157)
	    {
	      setcolor(DARKGRAY);
	      outtextxy(x,y,".");
	      choice=3;
	    }
	    else if(y==197)
	    {
	      setcolor(RED);
	      outtextxy(x,y,".");
	      choice=4;
	    }
	    else if(y==237)
	    {
	      setcolor(CYAN);
	      outtextxy(x,y,".");
	      choice=5;
	    }
	    else if(y==277)
	    {
	      setcolor(WHITE);
	      outtextxy(x,y,".");
	      choice=6;
	    }
	  }
	  else if(count==1&&W==13) choice=1;
	} while(W!=13);
	closegraph();
	switch(choice)
	{
	  case 1 : textcolor(6);
		   clrscr();
		   write_movie();
		   clrscr();
		   goto START;
	  case 2 : textcolor(3);
		   clrscr();
		   modify_movie();
		   clrscr();
		   goto START;
	  case 3 : textcolor(8);
		   clrscr();
		   delete_movie();
		   clrscr();
		   goto START;
	  case 4 : textcolor(2);
		   clrscr();
		   char num[6];
		   cout<<"\n\n\tPlease Enter The Movie No. ";
		   cin>>num;
		   display_spb(num);
		   goto START;
	  case 5 : textcolor(2);
		   clrscr();
		   f1.open("MULTIPLEX.DAT",ios::in|ios::binary);
		   f1.read((char *)&d,sizeof(d));
		   while(f1)
		   {
		     cout<<"BOOKING NO.     :: "<<d.bookingno<<"\n"
			 <<"NAME            :: "<<d.name<<"\n"
			 <<"EMAIL ADDRESS   :: "<<d.eaddress<<"\n"
			 <<"MOBILE NO       :: "<<d.mobileno<<"\n"
			 <<"MOVIE DATE	    :: "<<d.date<<"\n"
			 <<"SHOW TIME	    :: "<<d.stime<<"\n"
			 <<"MOVIE NAME      :: "<<d.moviename<<"\n"
			 <<"No. OF SEATS    :: "<<d.noofseats<<"\n\n\n";
		     getch();
		     f1.read((char *)&d,sizeof(d));
		   }
		   f1.close();
		   clrscr();
		   goto START;
	}
	clrscr();
}


void main()
{
	clrscr();
	gotoxy(35,11);
	cout<<"MULTIPLEX";
	gotoxy(35,14);
	cout<<"THEATRE";
	gotoxy(35,17);
	cout<<"SYSTEM";
	cout<<"\n\nMADE BY : VARUN SIRPAL";
	cout<<"\n\nSCHOOL  : AHLCON PUBLIC SCHOOL";
	delay(2000);
	// STARTING PAGE
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TurboC++\\Disk\\TurboC3\\BGI");
	setbkcolor(0);
	delay(100);
	setcolor(RED);
	settextstyle(4,0,5);
	outtextxy(270,50,"WELCOME"); delay(1000);
	settextstyle(7,0,5);
	setcolor(BLUE);
	outtextxy(290,150,"TO"); delay(1000);
	settextstyle(8,0,5);
	setcolor(GREEN);
	outtextxy(245,250,"MULTIPLEX THEATRE"); delay(1000);
	setcolor(WHITE);
	settextstyle(5,0,5);
	for(int i=-100,j=639;i<101;i++,j--)
	{
	  outtextxy(i,360,"PVR"); outtextxy(j,360,"CINEMA");
	  delay(15); setcolor(BLACK);
	  outtextxy(i,360,"PVR"); outtextxy(j,360,"CINEMA");
	  setcolor(WHITE);
	}
	outtextxy(100,360,"PVR");
	outtextxy(j,360,"CINEMA"); delay(1000);
	i=1;
	setbkcolor(BLACK);
	do
	{
	  setcolor(i);
	  settextstyle(4,0,5);
	  outtextxy(270,50,"WELCOME"); delay(100);
	  settextstyle(7,0,5);
	  setcolor(i+1);
	  outtextxy(290,150,"TO"); delay(100);
	  settextstyle(8,0,5);
	  setcolor(i+2);
	  outtextxy(245,250,"MULTIPLEX THEATRE"); delay(100);
	  setcolor(i+3);
	  settextstyle(5,0,5);
	  outtextxy(100,360,"PVR");
	  outtextxy(j,360,"CINEMA"); delay(100);
	  i++;
	} while(i!=13);
	delay(1000); cleardevice();
	settextstyle(0,0,0);
	for(i=400;i>=0;i--) { setcolor(BLUE); circle(320,240,i); delay(5); }
	for(i=0;i<=400;i++) { setcolor(RED); circle(320,240,i); delay(5); }
	// MAP SHOWING TOP VIEW OF THE MULTIPLEX
	cleardevice();
	setbkcolor(BLACK);
	setcolor(WHITE);
	outtextxy(200,0,"TOP VIEW OF PVR MOVIE THEATRE");
	line(20,20,20,460); delay(15);
	line(100,20,60,100); delay(15);
	line(20,20,100,20); delay(15);
	line(20,100,60,100); delay(15);
	line(60,100,60,380); delay(15);
	line(20,380,60,380); delay(15);
	line(60,380,100,460); delay(15);
	line(20,460,100,460); delay(15);
	line(620,20,620,460); delay(15);
	line(540,20,620,20); delay(15);
	line(540,460,620,460); delay(15);
	line(620,100,580,100); delay(15);
	line(620,380,580,380); delay(15);
	line(580,100,580,380); delay(15);
	line(540,20,580,100); delay(15);
	line(580,380,540,460); delay(15);
	line(170,20,470,20); delay(15);
	line(170,20,130,100); delay(15);
	line(130,100,130,200); delay(15);
	line(130,200,245,200); delay(15);
	line(245,200,245,180); delay(15);
	line(295,180,295,200); delay(15);
	line(295,200,510,200); delay(15);
	line(510,200,510,100); delay(15);
	line(510,100,470,20); delay(15);
	line(175,40,150,100); delay(15);
	line(150,100,150,180); delay(15);
	line(150,180,490,180); delay(15);
	line(490,180,490,100); delay(15);
	line(490,100,465,40); delay(15);
	line(465,40,175,40); delay(15);
	line(245,270,245,250); delay(15);
	line(245,250,130,250); delay(15);
	line(130,250,130,380); delay(15);
	line(130,380,170,460); delay(15);
	line(170,460,470,460); delay(15);
	line(470,460,510,380); delay(15);
	line(510,380,510,250); delay(15);
	line(510,250,295,250); delay(15);
	line(295,250,295,270); delay(15);
	line(170,280,310,280); delay(15);
	line(310,280,310,340); delay(15);
	line(310,340,170,340); delay(15);
	line(170,340,170,280); delay(15);
	line(330,280,470,280); delay(15);
	line(470,280,470,340); delay(15);
	line(470,340,330,340); delay(15);
	line(330,340,330,280); delay(15);
	line(170,350,470,350); delay(15);
	line(470,350,470,410); delay(15);
	line(470,410,170,410); delay(15);
	line(170,410,170,350); delay(15);
	line(320,350,320,410); delay(15);
	setcolor(WHITE);
	int poly[8]={20,100,60,100,100,20,20,20};
	setfillstyle(1,GREEN);
	fillpoly(4,poly); delay(15);
	int poly1[8]={20,380,20,460,100,460,60,380};
	setfillstyle(1,GREEN);
	fillpoly(4,poly1); delay(15);
	int poly2[8]={540,20,580,100,620,100,620,20};
	setfillstyle(1,GREEN);
	fillpoly(4,poly2); delay(15);
	int poly3[8]={540,460,620,460,620,380,580,380};
	setfillstyle(1,GREEN);
	fillpoly(4,poly3); delay(15);
	int poly4[8]={170,280,170,340,310,340,310,280};
	setfillstyle(1,9);
	fillpoly(4,poly4); delay(15);
	int poly5[8]={330,280,330,340,470,340,470,280};
	setfillstyle(1,9);
	fillpoly(4,poly5); delay(15);
	int poly6[8]={20,100,20,380,60,380,60,100};
	setfillstyle(9,8);
	fillpoly(4,poly6); delay(15);
	int poly7[8]={580,100,580,380,620,380,620,100};
	setfillstyle(9,8);
	fillpoly(4,poly7); delay(15);
	int poly8[12]={175,40,150,100,150,180,490,180,490,100,465,40};
	setfillstyle(9,12);
	fillpoly(6,poly8); delay(15);
	int poly9[8]={170,350,170,410,320,410,320,350};
	setfillstyle(9,RED);
	fillpoly(4,poly9); delay(15);
	int poly10[8]={320,350,320,410,470,410,470,350};
	setfillstyle(9,RED);
	fillpoly(4,poly10); delay(15);
	outtextxy(40,60,"LAWN"); delay(15);
	outtextxy(568,60,"LAWN"); delay(15);
	outtextxy(570,420,"SHOPS"); delay(15);
	outtextxy(40,420,"SHOPS"); delay(15);
	outtextxy(200,310,"SCREEN 1"); delay(15);
	outtextxy(350,310,"SCREEN 2"); delay(15);
	outtextxy(216,100,"WATER PARK & FOOD COURT"); delay(15);
	outtextxy(220,380,"SCREEN 3"); delay(15);
	outtextxy(370,380,"SCREEN 4"); delay(15);
	setcolor(WHITE);
	outtextxy(110,25,"ENTRY"); delay(15);
	outtextxy(480,25,"ENTRY"); delay(15);
	outtextxy(110,455,"EXIT"); delay(15);
	outtextxy(480,455,"EXIT"); delay(15);
	outtextxy(250,190,"ENTRY"); delay(15);
	outtextxy(250,260,"ENTRY"); delay(15);
	settextstyle(0,1,0);
	outtextxy(38,120,"UNDERGROUND TAXI STAND"); delay(15);
	outtextxy(598,120,"UNDERGROUND PARKING"); delay(15);
	settextstyle(0,0,0);
	setcolor(BLUE);

	for(i=0;i<5;i++)
	{
	  outtextxy(200,464,"PRESS ANY KEY TO CONTINUE"); delay(200);
	  setcolor(BLACK);
	  outtextxy(200,464,"PRESS ANY KEY TO CONTINUE"); delay(200);
	  setcolor(BLUE);
	}
	outtextxy(200,464,"PRESS ANY KEY TO CONTINUE");
	getch();
	cleardevice();
	for(i=400;i>=0;i--) { setcolor(8); circle(320,240,i); delay(5); }
	for(i=0;i<=400;i++) { setcolor(12); circle(320,240,i); delay(5); }
	closegraph();
	// MAIN OPTIONS
	int times=0;
	LABEL:
	times++;
	int count=0;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	int option_code=0;
	setbkcolor(BLACK);
	setcolor(CYAN);
	settextstyle(10,0,5);
	outtextxy(230,-20,"OPTIONS ");
	settextstyle(10,0,1);
	setcolor(BLUE);
	if(times==1)
	{
	  delay(1000);
	  line(100,70,540,70);delay(1000);
	  setcolor(LIGHTRED);
	  outtextxy(220,80,"OPTIONS"); delay(1000);
	  setcolor(RED);
	  outtextxy(220,110,"Movie Booking"); delay(1000);
	  setcolor(BLUE);
	  outtextxy(220,140,"Cancellation"); delay(1000);
	  setcolor(CYAN);
	  outtextxy(220,170,"Food Court"); delay(1000);
	  setcolor(GREEN);
	  outtextxy(220,200,"Taxi Service"); delay(1000);
	  setcolor(LIGHTBLUE);
	  outtextxy(220,230,"Water Park"); delay(1000);
	  setcolor(MAGENTA);
	  outtextxy(220,260,"Admin Menu"); delay(1000);
	  setcolor(WHITE);
	  outtextxy(220,290,"Quit"); delay(1000);
	}
	else
	{
	  line(100,70,540,70);
	  setcolor(LIGHTRED);
	  outtextxy(220,80,"OPTIONS");
	  setcolor(RED);
	  outtextxy(220,110,"Movie Booking");
	  setcolor(BLUE);
	  outtextxy(220,140,"Cancellation");
	  setcolor(CYAN);
	  outtextxy(220,170,"Food Court");
	  setcolor(GREEN);
	  outtextxy(220,200,"Taxi Service");
	  setcolor(LIGHTBLUE);
	  outtextxy(220,230,"Water Park");
	  setcolor(MAGENTA);
	  outtextxy(220,260,"Admin Menu");
	  setcolor(WHITE);
	  outtextxy(220,290,"Quit");
	}
	// FOR MOVING THE CURSOR UP OR DOWN
	int x=190,y=100;
	setcolor(RED);
	outtextxy(x,y,".");
	char W;
	do
	{
	 count++;
	 W=getch();
	 if(W=='\0'+'H')
	 {
	  setcolor(BLACK);
	  outtextxy(x,y,".");
	  y-=30;
	  if(y<100)
	  {
	   y=280;
	   setcolor(WHITE);
	   outtextxy(x,y,".");
	   option_code=12;
	  }
	  else if(y==100)
	  {
	   setcolor(RED);
	   outtextxy(x,y,".");
	   option_code=1;
	  }
	  else if(y==130)
	  {
	   setcolor(BLUE);
	   outtextxy(x,y,".");
	   option_code=4;
	  }
	  else if(y==160)
	  {
	   setcolor(CYAN);
	   outtextxy(x,y,".");
	   option_code=5;
	  }
	  else if(y==190)
	  {
	   setcolor(GREEN);
	   outtextxy(x,y,".");
	   option_code=7;
	  }
	  else if(y==220)
	  {
	   setcolor(LIGHTBLUE);
	   outtextxy(x,y,".");
	   option_code=10;
	  }
	  else if(y==250)
	  {
	   setcolor(MAGENTA);
	   outtextxy(x,y,".");
	   option_code=11;
	  }
	  else if(y==280)
	  {
	   setcolor(WHITE);
	   outtextxy(x,y,".");
	   option_code=12;
	  }
	 }
	 else if(W=='\0'+'P')
	 {
	  setcolor(BLACK);
	  outtextxy(x,y,".");
	  y+=30;
	  if(y>280)
	  {
	   y=100;
	   setcolor(RED);
	   outtextxy(x,y,".");
	   option_code=1;
	  }
	  else if(y==100)
	  {
	   setcolor(RED);
	   outtextxy(x,y,".");
	   option_code=1;
	  }
	  else if(y==130)
	  {
	   setcolor(BLUE);
	   outtextxy(x,y,".");
	   option_code=4;
	  }
	  else if(y==160)
	  {
	   setcolor(CYAN);
	   outtextxy(x,y,".");
	   option_code=5;
	  }
	  else if(y==190)
	  {
	   setcolor(GREEN);
	   outtextxy(x,y,".");
	   option_code=7;
	  }
	  else if(y==220)
	  {
	   setcolor(LIGHTBLUE);
	   outtextxy(x,y,".");
	   option_code=10;
	  }
	  else if(y==250)
	  {
	   setcolor(MAGENTA);
	   outtextxy(x,y,".");
	   option_code=11;
	  }
	  else if(y==280)
	  {
	   setcolor(WHITE);
	   outtextxy(x,y,".");
	   option_code=12;
	  }
	 }
	 else if(count==1&&W==13)
	 {
	  closegraph();
	  H.booking();
	  goto LABEL;
	 }
	}while(W!=13);
	closegraph();
	// FOR GOING TO THE SPECIFIED OPTION
	switch(option_code)
	{
	 case 1:H.booking();
		break;
	 case 4:
		H.cancellation();
		break;
	 case 5:
		H.foodcourt();
		break;
	 case 7:
		H.taxi_service();
		break;
	 case 10:
		 H.water_park();
		 break;
	 case 11:
		 H.admin_data();
		 break;
	 case 12:exit(0);
	}
	goto LABEL;
}
