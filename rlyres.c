#include<stdio.h>
#include"conio2.h"
#include"rlyres.h"
#include<ctype.h>

view_all_bookings()
{

    FILE *fp=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
    }
    passenger p;
    int x=1,i;
    printf("TICKET NO\tTRAIN NO\t CLASS\t\t  NAME\t\tGENDER\tAGE\tMOBILE NO\tADDRESS \n");
    for(i=0;i<=118;i++)
    {
      printf("-");
    }
    printf("\n");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
           x++;
           printf("%d\t\t%s\t\t %c \t\t  %s ",p.ticketno,p.train_no,p.p_class,p.p_name);
           gotoxy(67,x+1);
           printf("%c\t%d\t%s\t%s\n",p.gender,p.age,p.mob_no,p.address);
    }
if(x==1)
{
    clrscr();
    textcolor(LIGHTRED);
    printf("\n NO BOOKINGS DONE YET!!!!");
}
fclose(fp);
}

void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("---------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
textcolor(WHITE);
printf("\n\nPress any key to go back to the main screen");
textcolor(YELLOW);
getch();
}


int* get_ticket_no(char *p_mob_no)
{
   int count=0;
   FILE *fp=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
   if(fp==NULL)
    {
        return NULL;
    }
   passenger pr;
   while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
   }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
      {
          *(p+i)=pr.ticketno;
            i++;
      }
    }
*(p+i)=-1;
fclose(fp);
return p;
}


char* accept_mob_no()
{
  static char mob_no[11];
  char *pos;
  int valid;
  gotoxy(100,1);//60 column 1 row
 textcolor(LIGHTGREEN);
 printf("Press 0 to exit");

 gotoxy(1,1);
 textcolor(YELLOW);
  printf("Enter mobile number:");
   do
   {
    fflush(stdin);
    fgets(mob_no,11,stdin);
    pos=strchr(mob_no,'\n');
    if(pos!=NULL)
     *pos='\0';
    if(strcmp(mob_no,"0")==0)
     {
      textcolor(LIGHTRED);
      gotoxy(1,25);
      printf("\t\t\t\t\t\t\t");
      gotoxy(1,25);
      printf("Cancelling Input. . .!");
      getch();
      textcolor(YELLOW);
      return NULL;
     }
  valid=check_mob_no(mob_no);
  if(valid==0)
  {
   textcolor(LIGHTRED);
   gotoxy(1,25);
   printf("Error! Invalid Mobile No");
   getch();
   gotoxy(21,1);
   printf("\t\t\t\t\t\t");
   gotoxy(21,1);
   textcolor(YELLOW);
  }
 }while(valid==0);

clrscr();
return mob_no;

}

void view_booking(char* train_no)
{
    FILE *fp=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return -1;
    }
    passenger p;
    int i;
    printf("TICKET NO\t CLASS\t\t  NAME\t\t\tGENDER\t\t AGE\t\tMOBILE NO \n");
    for(i=0;i<=100;i++)
    {
      printf("-");
    }
    printf("\n");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
       if(strcmp(p.train_no,train_no)==0)
       {
           printf("%d\t\t %c \t\t  %s\t\t%c\t\t %d\t\t%s\n",p.ticketno,p.p_class,p.p_name,p.gender,p.age,p.mob_no);

       }
    }
    fclose(fp);

}

int cancel_train(char *ptrain_no)
{
  gotoxy(100,1);//60 column 1 row
 textcolor(LIGHTGREEN);
 printf("Press 0 to exit");

 gotoxy(1,1);
 textcolor(YELLOW);
  FILE *fp1=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
  if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return -1;
    }
  FILE *fp2=fopen("D:\\c program\\NewRMSS\\temp.dat","wb");
  passenger pr;
  int found=0;
  while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
      if(strcmp(pr.train_no,ptrain_no)!=0)
      {
          fwrite(&pr,sizeof(pr),1,fp2);
      }
      else
      {
          found=1;
      }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==1)
    {

        remove("D:\\c program\\NewRMSS\\allbookings.dat");
        rename("D:\\c program\\NewRMSS\\temp.dat","D:\\c program\\NewRMSS\\allbookings.dat");
    }
    else
    {
        remove("D:\\c program\\NewRMSS\\temp.dat");

    }

return found;
}


int check_train_no(char *trainno)
{
    FILE *fp=fopen("D:\\c program\\NewRMSS\\alltrains.dat","rb");
    train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
      if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }

    }
fclose(fp);
return 0;
}

char *accept_train_no()
{
   static char train_no[10];
   int valid;
   gotoxy(100,1);//60 column 1 row
 textcolor(LIGHTGREEN);
 printf("Press 0 to exit");

 gotoxy(1,1);
 textcolor(YELLOW);
   printf("Enter train number:");

   do
   {
    fflush(stdin);
    scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling Input. . .!");
                textcolor(YELLOW);
                return NULL;
        }

    valid=check_train_no(train_no);
    if(valid==0)
     {
            textcolor(LIGHTRED);
            gotoxy(1,25);

            printf("Error! Invalid Train No");
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t");
            gotoxy(20,1);
            printf("\t\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);

     }
    }while(valid==0);
clrscr();
return train_no;
}


int  cancel_ticket(int ticket_no)
{
    FILE *fp1=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return -1;

    }

    FILE *fp2=fopen("D:\\c program\\NewRMSS\\temp.dat","wb+");
    passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
      if(pr.ticketno!=ticket_no)
      {
          fwrite(&pr,sizeof(pr),1,fp2);
      }
      else
      {
          found=1;
      }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\c program\\NewRMSS\\temp.dat");
    }
    else
    {
        remove("D:\\c program\\NewRMSS\\allbookings.dat");
        rename("D:\\c program\\NewRMSS\\temp.dat","D:\\c program\\NewRMSS\\allbookings.dat");

    }

return found;
}


int accept_ticket_no()
{   fflush(stdin);
    gotoxy(100,1);//60 column 1 row
 textcolor(LIGHTGREEN);
 printf("Press 0 to exit");

 gotoxy(1,1);
 textcolor(YELLOW);
    printf("Enter ticket number:");
    int valid;
    int ticket_no;

    do
    {
        valid =1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            valid=0;
            textcolor(YELLOW);
            return 0;
        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Ticket number should be positive");
            valid =0;
            getch();
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(21,1);
            printf("\t\t\t\t");
            gotoxy(21,1);
            textcolor(YELLOW);
        }
    }while(valid==0);

    return ticket_no;
}

void view_ticket(int ticket_no)
{
    FILE *fp=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");

    }
    passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("\nNamE:%s\nGender:%c\nTrain number:%s\nClass:%c\nAddress:%s\nAgE:%d\nMobile number:%s\nTicket number:%d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            printf("\n\n");
            found=1;
            break;
        }
    }
    if(found==0)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of ticket no %d found!",ticket_no);
    }
    fclose(fp);
}

int book_ticket(passenger p)
{
 int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
 if(ticket_count==30)
 {
     textcolor(LIGHTRED);
     printf("All seats full in train no %s in %c class!\n",p.train_no,p.p_class);
     return -1;
 }
int ticket_no=last_ticket_no()+1;
p.ticketno=ticket_no;

FILE *fp=fopen("D:\\c program\\NewRMSS\\allbookings.dat","ab");
if(fp==NULL)
{
    textcolor(LIGHTRED);
    printf("Sorry! File cannot be opened");
    return -1;
}
fwrite(&p,sizeof(p),1,fp);
fclose(fp);
return ticket_no;
}


int get_booked_ticket_count(char*train_no,char tc)//tc-train class
{

   FILE *fp;
   fp=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
   if(fp==NULL)
   return 0;

   passenger p;
   int count=0;
   while(fread(&p,sizeof(p),1,fp)==1)
      {
       if(strcmp(p.train_no,train_no)==0&&p.p_class==tc)
       count++;
      }

    fclose(fp);
    return count;
}

int last_ticket_no()
{
   FILE *fp;
   fp=fopen("D:\\c program\\NewRMSS\\allbookings.dat","rb");
   if(fp==NULL)
    return 0;
   passenger p;
   fseek(fp,-1*sizeof(p),SEEK_END);
   fread(&p,sizeof(p),1,fp);
   fclose(fp);
   return p.ticketno;
}

int check_mob_no(char *p_mob)
{
  if(strlen(p_mob)!=10)
  {
      return 0;
  }

  while(*p_mob!='\0')
   {
     if(isdigit(*p_mob)==0)
        return 0;
     p_mob++;
   }
return 1;
}


int enterchoice()
{

int choice ,i,res;
textcolor(YELLOW);
gotoxy(28,1);
printf("RAILWAY RESERVATION SYSTEM\n");
for(i=0;i<=100;i++)
{
printf("-");
}
printf("\nSelect an option\n1- View Trains\n2- Book Ticket\n3- View Ticket\n4- Search Ticket No\n5- View All Bookings\n6- View Train Bookings\n7- Cancle Ticket\n8- Cancle Train\n9- Quit\n\nEnter choicE: ");
do
{
fflush(stdin);
res=scanf("%d",&choice);
if(res!=1)
{
    textcolor(LIGHTRED);
    printf("\nPlease input digits only!\n");
    getch();
    textcolor(YELLOW);
    gotoxy(15,14);
    printf("\t\t\t\n\n\t\t\t\t\t\t");
    gotoxy(15,14);
    textcolor(YELLOW);
}
}while(res!=1);
return choice;
}


void add_trains()
{
FILE *fp;
fp=fopen("D:\\c program\\NewRMSS\\alltrains.dat","rb");
if(fp==NULL)
{
  train alltrains[]={{"123","BPL","GWA",2100,1500},{"546","BPL","DEL",3500,2240},{"345","HBJ","AGR",1560,1135},{"896","HBJ","MUM",4500,3360}};

      fp=fopen("D:\\c program\\NewRMSS\\alltrains.dat","wb");
      fwrite(alltrains,4*sizeof(train),1,fp); //to write 4 data at a time using single fwrite() .No need to use loop and write data one by one.
     // printf("file saved successfully\n");
      fclose(fp);
}
else
   // printf("file already present\n");
    fclose(fp);
}

void view_trains()
{   clrscr();
    int i;
    FILE *fp;
    fp=fopen("D:\\c program\\NewRMSS\\alltrains.dat","rb");
    textcolor(YELLOW);
    printf("TRAIN NO\tFROM\t\t TO\t\tFIRST AC FAIR\t\ SECOND AC FAIR\n");
    for(i=0;i<=80;i++)
    {
     printf("-");
    }
    printf("\n");

    train t;
    //fread(&t,sizeof(train),1,fp);
    while(fread(&t,sizeof(train),1,fp)==1) //or use while(!feof(fp)) write all this with comments
    {
      printf("%s \t\t %s \t\t %s \t\t %d \t\t %d",t.train_no,t.from,t.to,t.fac_fare,t.sac_fare);
      printf("\n");
      //fread(&t,sizeof(train),1,fp);
    }

    printf("\n\npress any key to go back to main screen\n");
    getch();
}

passenger*get_passenger_details()
{

 gotoxy(100,1);//60 column 1 row
 textcolor(LIGHTGREEN);
 printf("Press 0 to exit");

 gotoxy(1,1);
 textcolor(YELLOW);//write after above to get cursor after enter your name.or use gotoxy()
 static passenger psn;
 printf("Enter passenger name:");
 int valid;
 do
 {
 valid=1;
 fflush(stdin);
 fgets(psn.p_name,20,stdin); // stdin to take ip from keaboard use fp to take ip from file .stops to take ip if enter pressed or limit exceed . store \n(enter) and null with string;
 if(strcmp(psn.p_name,"\n")==0)
 {
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Name field cannot be empty");
    valid=0;
    getch();
    fflush(stdin);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    textcolor(YELLOW);
    gotoxy(22,1);
    printf(" \b");
 }
 }while(valid==0);
 char*pos;
 pos=strchr(psn.p_name,'\n');//it will search left to right for \o and return address of its first occurence .
 *pos='\0';

if(strcmp(psn.p_name,"0")==0)//or psn.p_name[1]==0
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Reservation Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;
}


printf("Enter gender(M or F):");
do
{
valid=1;
scanf("%c",&psn.gender);
if(psn.gender=='0')
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Reservation Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;
}
if(psn.gender!='M'&&psn.gender!='F')
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Error! Gender should be M or F(in upper case)");
    valid=0;
    getch();
    fflush(stdin);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    textcolor(YELLOW);
    gotoxy(14,2);
    printf(" \b");
}
}while(valid==0);

printf("Enter train number:");
fflush(stdin);
do
{
fgets(psn.train_no,20,stdin); // stdin to take ip from keaboard use fp to take ip from file .stops to take ip if enter pressed or limit exceed . store \n(enter) and null with string;
valid=1;
pos=strchr(psn.train_no,'\n');//it will search left to right for \o and return address of its first occurence .
 *pos='\0';

if(strcmp(psn.train_no,"0")==0)
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Reservation Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;
}

if(check_train_no(psn.train_no)==0)
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Error! Invalid train number");
    valid=0;
    getch();
    fflush(stdin);
    gotoxy(1,25);
    printf("\t \t \t \t \t \t \t \t \t");
    textcolor(YELLOW);
    gotoxy(20,3);
    printf("\t\t");
    gotoxy(20,3);
}
}while(valid==0);

printf("Enter travelling class(First AC-F,Second AC-S):");
do
{
scanf("%c",&psn.p_class);
valid=1;
if(psn.p_class=='0')
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Reservation Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;
}

if(psn.p_class!='F'&&psn.p_class!='S')
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Error! Travelling class should be F or S(in upper case)");
    valid=0;
    getch();
    fflush(stdin);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    textcolor(YELLOW);
    gotoxy(48,4);
    printf(" \b");
}
}while(valid==0);


fflush(stdin);
printf("Enter your age:");
do
{
scanf("%d",&psn.age);
valid=1;
if(psn.age==0)
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Reservation Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;
}
if(psn.age<0)
{   gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Error! Age should be positive");
    valid=0;
    getch();
    fflush(stdin);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    textcolor(YELLOW);
    gotoxy(16,5);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(16,5);
}
}while(valid==0);

printf("Enter your address:");
do
{
fflush(stdin);
fgets(psn.address,100,stdin);
valid=1;
if(strcmp(psn.address,"\n")==0)
 {
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Address field cannot be empty");
    valid=0;
    getch();
    fflush(stdin);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    textcolor(YELLOW);
    gotoxy(20,6);
    printf(" \b");
 }
}while(valid==0);

pos=strchr(psn.address,'\n');
*pos='\0';

if(strcmp(psn.address,"0")==0)
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Reservation Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;
}


fflush(stdin);
printf("Enter mobile number:");
do
{
fgets(psn.mob_no,13,stdin); // stdin to take ip from keaboard use fp to take ip from file .stops to take ip if enter pressed or limit exceed . store \n(enter) and null with string;
valid=1;
pos=strchr(psn.mob_no,'\n');// if not found \n return null
 if(pos!=NULL)
 *pos='\0';

if(strcmp(psn.mob_no,"0")==0)
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Reservation Cancelled!");
    getch();
    textcolor(YELLOW);
    return NULL;
}
if(check_mob_no(psn.mob_no)==0)
{
    gotoxy(1,25);//at bottom
    textcolor(LIGHTRED);
    printf("Wrong mobile number entered!! Please enter the correct mobile number");
    valid=0;
    getch();
    fflush(stdin);
    gotoxy(1,25);
    printf("\t \t \t \t \t \t \t \t \t");
    textcolor(YELLOW);
    gotoxy(21,7);
    printf("\t \t \t \t");
    gotoxy(21,7);

}
}while(valid==0);

return &psn;
}
