#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
class bank
{
int acc_no;
char name[50];
int amt;
char acc_type;
char bank_nm[20];
int dep;
public:
bank()
{  acc_no=123;
   strcpy(name,"ABC");
   strcpy(bank_nm,"XYZ");
   acc_type='NA';
   amt=0;

}
void disp_acc();
void create_acc();
void modify();
void deposit(int);
void draw(int);
int ret_acc();
int ret_dep();
char ret_acctype();
};
void bank::create_acc()
{    cout<<"\n ENTER BANK NAME:";
     gets(bank_nm);

     cout<<"\t \t \t WELCOME TO  "<<bank_nm<<" BANK";
     cout<<"\n ENTER ACCOUNT NO: ";
     cin>>acc_no;
     cout<<"\n ENTER YOUR NAME: ";
     gets(name);
     cout<<"\n ENTER YOUR ACCOUNT TYPE( C FOR CURRENT/S FOR SAVINGS): ";
     cin>>acc_type;
     cout<<"\n ENTER AMOUNT TO BE DEPOSITED(>5000)" ;
     cin>>amt;
     cout<<"\n  ACCOUNT CREATED   ";
}
void bank::disp_acc()
{    cout<<"\n BANK NAME:"<<bank_nm<<":";
     cout<<"\n ACCOUNT NO:"<<acc_no;
     cout<<"\n NAME:"<<name;
     cout<<"\n ACCOUNT TYPE:";
     if(acc_type=='C')
     cout<<"CURRENT";
     else if(acc_type=='S')
     cout<<"SAVINGS";
     cout<<"\n BALANCE="<<amt;
     cout<<"\n";
}
void bank::modify()
{    cout<<"\n ENTER NEW BANK NAME: ";
     gets(bank_nm);

	  cout<<"\t \t \t WELCOME TO  "<<bank_nm<<" BANK";
     cout<<"\n ENTER NEW ACCOUNT NO: ";
     cin>>acc_no;
     cout<<"\n ENTER NEW NAME: ";
     gets(name);
     cout<<"\n ENTER YOUR ACCOUNT TYPE( C FOR CURRENT/S FOR SAVINGS): ";
     cin>>acc_type;
     cout<<"\n ENTER AMOUNT TO BE DEPOSITED(>5000)" ;
     cin>>amt;
}
void bank::deposit(int x)
{    amt+=x;
cout<<"\n AMOUNT SUCCESSFULLY DEPOSITED: ";
}
void bank::draw(int x)
{  amt-=x;
 cout<<"\n AMOUNT SUCCESSFULLY WITHRAWN: ";
}
int bank::ret_acc()
{  return acc_no;
}
int bank::ret_dep()
{ return amt;
}
char bank::ret_acctype()
{  return acc_type;
}
void write_acc()
{   bank bn;
    ofstream fout;
    fout.open("banking.dat",ios::binary|ios::app);
    bn.create_acc();
    fout.write( (char*) &bn,sizeof(bn) );
    fout.close();
}
void spdisp_acc(int n)
{    bank bn;
     int flag=0;
     ifstream fin;
     fin.open("banking.dat",ios::binary|ios::in);
     fin.read( (char*) &bn,sizeof(bn) );
     while(!fin.eof() )
{     if(bn.ret_acc()==n){
        flag=1;
        bn.disp_acc();
    }
      fin.read( (char*) &bn,sizeof(bn) );
}
     if(flag==0)
    cout<<"\n ACCOUNT DOES NOT EXIST: ";
    fin.close();
}
void  all_acc()
{     bank bn;
      ifstream fin;
      fin.open("banking.dat",ios::binary|ios::in);
      fin.read( (char*) &bn,sizeof(bn) );
      cout<<"\n \n \n ACCOUNT HOLDER'S LIST   ";
      while(!fin.eof())
{     bn.disp_acc();
      fin.read( (char*) &bn,sizeof(bn) );
}
fin.close();
}
void depdraw(int n)
{      bank bn;
       ifstream fin;
       fin.open("banking.dat",ios::binary|ios::in);
       fin.read( (char*) &bn,sizeof(bn) );
      while(!fin.eof() )
{     int choice;
float amount=0;
   if(bn.ret_acc()==n)
{     cout<<"\n ENTER YOUR CHOICE: ";
      cout<<"\n 1:DEPOSIT \n 2:WITHDRAW \n";
      cin>>choice;
   if(choice==1)
{     cout<<"\n ENTER AMOUNT TO BE DEPOSITED: ";
      cin>>amount;
      bn.deposit(amount);}
else if(choice==2)
{     cout<<"\n ENTER AMOUNT TO BE WITHDRAWN: ";
      cin>>amount;
  if(amount>bn.ret_dep() )
      cout<<"\n INSUFFICIENT BALANCE: ";
else
     bn.draw(amount);
}
else
    cout<<"\n ACCOUNT DOES NOT EXIST: ";
}
    fin.read( (char*) &bn,sizeof(bn) );
}
fin.close();
}

void delete_acc(int n, int silent=0)
{    bank bn;
     ofstream fout;
     fout.open("banking1.dat",ios::binary|ios::out);
     
     ifstream fin;
     fin.open("banking.dat",ios::binary|ios::in);
     fin.read( (char*) &bn,sizeof(bn) );
     //int flag=0;

     while(!fin.eof() ){
        if(bn.ret_acc()!=n){
	    //flag=1;
            fout.write( (char*) &bn, sizeof(bn) );
        }
      fin.read( (char*) &bn,sizeof(bn) );
    }
    //if(flag==0 && silent!=1)
    //    cout<<"\n ACCOUNT DOES NOT EXIST: ";
 fin.close();
 fout.close();
  remove("banking.dat");
  rename("banking1.dat","banking.dat");
  if(silent!=1)
    cout<<"\n ACCOUNT SUCCESSFULLY DELTED" ;
 }
 
 void modify_acc(int n )
{
     bank bn;
     int flag=0;
     ifstream fin;
     fin.open("banking.dat",ios::binary|ios::in);
     fin.read( (char*) &bn,sizeof(bn) );
     while(!fin.eof() )
{     if(bn.ret_acc()==n){
        flag=1;
        bn.disp_acc();
        break;
    }
      fin.read( (char*) &bn,sizeof(bn) );
}
     if(flag==0)
    cout<<"\n ACCOUNT DOES NOT EXIST: ";
    else{
        bn.modify();
        fin.close();
        delete_acc(n,1);
        ofstream fout;
        fout.open("banking.dat",ios::binary|ios::app);
        fout.write( (char*) &bn,sizeof(bn) );
        fout.close();
        cout << "Account modified successfully" << endl;
    }
}
 
 void intro()
 { cout<<"\n";
 cout<<"\n\n\t\t\t BANK MANAGEMENT SYSTEM      ";
 cout<<"\n\n\t\t\t PRESS ANY KEY      ";
 cout<<"\n\n\n\n\n\n\n\n     ";
 getch();
 }
  void main()
{        char ch;
	 int num;
	 clrscr();
	 intro();
	   do
	      { clrscr();
	       cout<<"\n  MAIN MENU";
	       cout<<"\n  01. NEW ACCOUNT";
	       cout<<"\n  02. DEPOSIT AMOUNT";
	       cout<<"\n  03. WITHDRAW AMOUNT";
	       cout<<"\n  04. BALANCE AMOUNT";
	       cout<<"\n  05. ALL ACCOUNT HOLDER LIST";
	       cout<<"\n  06. CLOSE AN ACCOUNT";
	       cout<<"\n  07. MODIFY AN ACCOUNT";
	       cout<<"\n  08. EXIT";
	       cout<<"\n SELECT  YOUR OPTION(1-8): ";
    cin>>ch;
     switch(ch)
       { case '1' :
	     write_acc();
	     break;
	 case '2' :
	      cout<<"\n\n\t ENTER ACCOUNT NO: ";cin>>num;
	      depdraw(num);
	      break;
	 case '3'  :
	 cout<<"\n\n\t ENTER ACCOUNT NO: ";cin>>num;
	      depdraw(num);
	      break;
	 case '4':
	      cout<<"\n\n\t ENTER ACCOUNT NO: ";cin>>num;
	      spdisp_acc(num);
	      break;
	 case '5':
	      all_acc();
	      break;
	 case '6':
	       cout<<"\n\n\t ENTER ACCOUNT NO: ";cin>>num;
	       delete_acc(num);
	       break;
	 case '7':
		cout<<"\n\n\t ENTER ACCOUNT NO: ";cin>>num;
		modify_acc(num);
		break;
	 case '8':
	     cout<<"\n\n\tTHANKS FOR USING BANK MANAGEMENT SYSTEM \n \n";
	     cout<<"\n\t\t\tSEE YOU SOON";
	     break;
 default:cout<<"\n WRONG CHOICE";

}
getch();
}while(ch!='8');}
