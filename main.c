#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include"rlyres.h"
int main()
{
    passenger *ptr;
    add_trains();
    int result;
    int choice;
    int ticket_no;
    char *pmob_no;
    char *ptrain_no;
    int *pticket_no;
    while(1)
    {
     clrscr();
     choice=enterchoice();
     if(choice==9)
        exit(0);
     else
        switch(choice)
     {
        case 1:
            view_trains();
            break;
        case 2:
            clrscr();
            ptr=get_passenger_details();
            clrscr();
            if(ptr!=NULL)
            {
                int ticket_no;
                ticket_no=book_ticket(*ptr);
                if(ticket_no==-1)
                    {
                        textcolor(LIGHTRED);
                        printf("booking failed");
                    }
            else
            {
                textcolor(LIGHTGREEN);
                printf("BOOKING SUCCESSFULL\nYour ticket no. is %d",ticket_no);
            }
            textcolor(WHITE);
            printf("\n\n\nPress any key to go back to the main menu!");
            getch();
            clrscr();
            }
            break;
        case 3:
            clrscr();
            ticket_no=accept_ticket_no();
            if(ticket_no!=0)
               {
                 view_ticket(ticket_no);
               }
            textcolor(WHITE);
            printf("\n\nPress any key to go back to the main screen");
            getch();
            clrscr();
            break;
        case 4:
            clrscr();
            pmob_no=accept_mob_no();
            if(pmob_no!=NULL)
            {
                pticket_no=get_ticket_no(pmob_no);
                view_all_tickets(pmob_no,pticket_no);
            }
            clrscr();
            break;
        case 5:
            clrscr();
            view_all_bookings();
            textcolor(WHITE);
            printf("\n\nPress any key to go back to the main screen");
            getch();
            clrscr();
            break;
        case 6:
            clrscr();
            ptrain_no=accept_train_no();
            if(ptrain_no!=NULL)
            {
                view_booking(ptrain_no);
                getch();
                textcolor(WHITE);
                printf("\n\nPress any key to go back to the main screen");
            }
            break;
        case 7:
            clrscr();
            ticket_no=accept_ticket_no();
            if(ticket_no!=0)
                {
                    result=cancel_ticket(ticket_no);
                    if(result==0)
                    {
                        textcolor(LIGHTRED);
                        printf("Sorry! No tickets booked against ticket no %d",ticket_no);

                    }
                    else if(result==1)
                    {
                        textcolor(LIGHTGREEN);
                        printf("Ticket no %d successfully cancelled!",ticket_no);
                    }
            textcolor(WHITE);
            printf("\n\nPress any key to go back to the main screen");

             }

            getch();
            clrscr();
            break;

        case 8:
            clrscr();
            ptrain_no=accept_train_no();
            if(ptrain_no!=NULL)
            {
                result=cancel_train(ptrain_no);
                if(result==0)
                  {
                        textcolor(LIGHTRED);
                        printf("Sorry! No tickets booked in train no no %s",ptrain_no);

                  }
                    else
                    {
                        textcolor(LIGHTGREEN);
                        printf("Train no %s successfully cancelled!",ptrain_no);
                    }
            textcolor(WHITE);
            printf("\n\nPress any key to go back to the main screen");

            }


            getch();
            clrscr();
            break;

        default:
            textcolor(LIGHTRED);
            printf("\nWrong choice entered! Try again...\n");
            getch();
            clrscr();
    }
    }
    return 0;
}
