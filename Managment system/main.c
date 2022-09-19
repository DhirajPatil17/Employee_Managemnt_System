#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<dos.h>
#include<string.h>
#include <ctype.h>
#include<unistd.h>
#include<time.h>

#include<windows.h>
void dataentry();
void selectAdminOption();
void getdata(int option);
int showAdminMenu;
void selectAdminOption()
{
    char chc[1];
    int chooseNew,chooseShow,chooseSearch,chooseRemove,chooseClose;
    gets(chc);
    chooseNew=strcmp(chc,"1");
    chooseShow=strcmp(chc,"2");
    chooseSearch=strcmp(chc,"3");
    chooseRemove=strcmp(chc,"4");
    chooseClose=strcmp(chc,"5");

    if(!(chooseNew==0 ||chooseShow==0 ||chooseSearch==0||chooseRemove==0 ||chooseClose==0 ))
    {
        printf("Invalid input!");
        printf("press any key to continue");
    }
    if(chooseNew==0)
    {
        system("cls");
        getdata(1);
    }
    else if(chooseShow==0)
    {
        system("cls");
        getdata(2);
    }
    else if(chooseSearch==0)
    {
        system("cls");
        getdata(3);
    }
    else if(chooseRemove==0)
    {
        system("cls");
        getdata(4);
    }

    else if(chooseClose==0)
    {
        showAdminMenu=1;
    }

}
void getdata(int option)
{
FILE *db,*tempdb;
char anotherEmp;
int choice;
int showMenu,posx,posy;
char checkSave,checkAddNew;
int i;
struct employee
{
    char firstname[30];
    char lastname[30];
    char password[30];
    int empid;
    char loginhour;
    char loginmin;
    char loginsec;
    char logouthour;
    char logoutmin;
    char logoutsec;
    int yr;
    char mon;
    char day;
};
struct employee empData;
time_t currentTime;
time(&currentTime);

char confirmPassword[30];
long int size;
char firstNameTemp[30],lastnameTemp[30],password[30];
int searchId;
char pass[30];
char findEmployee;
char confirmDelete;

struct tm *now=localtime(&currentTime);
system("cls");
db=fopen("empbase.dat","rb+");
if (db==NULL)
{
    db=fopen("empbase.dat","wb+");
    if(db==NULL)
    {
        printf("the file cannot be opened.\n");
        exit(0);
    }
}
printf("Application Database\n");
size=sizeof(empData);
showMenu=0;
while(showMenu==0)
{
    fflush(stdin);
    choice=option;
    switch(choice)
    {
    case 1:
        fseek(db,0,SEEK_END);
        anotherEmp='y';
        while(anotherEmp=='y')
        {
            checkAddNew=0;
            while(checkAddNew==0)
            {
                system("cls");
                printf("\n\n\n\n\t\t\t\t\tADD NEW EMPLOYEE\n");
                printf("\n\t\tWarning : Password Must Contain Six(6) AlphaNumeric Digits.\n\n");
                printf("\n\n\t\t\t\tEnter FirstName:");
                scanf("%s",&firstNameTemp);
                printf("\n\n\t\t\t\tEnter Last Name:");
                scanf("%s",&lastnameTemp);
                printf("\n\n\t\t\t\tEnter Password:");
                for(i=0;i<6;i++)
                {
                    password[i]=getch();
                    printf("* ");

                }
                password[6]='\0';
                while(getch()!=13);

                    printf("\n\n\t\t\t\tConfirm Password:");

                    for(int i=0;i<6;i++)
                    {
                        confirmPassword[i]=getch();
                        printf("* ");
                    }
                    confirmPassword[6]='\0';
                    while(getch()!=13);

                        if(strcmp(password,confirmPassword))
                        {
                            printf("\n\n\t\t\t\tPasswords do not match");
                            printf("\n\n\t\t\t\tPress any key to Continue");
                            getch();
                        }
                        else{
                            checkAddNew=1;
                            rewind(db);
                            empData.empid=0;
                            while(fread(&empData,size,1,db)==1);
                            if(empData.empid<2000)
                                empData.empid=20400;
                                empData.empid=empData.empid+1;
                                printf("\n\n\t\t\t\tSave Employee information(y/n):");
                                checkSave=getche();
                                if(checkSave=='y')
                                {
                                    strcpy(empData.firstname,firstNameTemp);
                                    strcpy(empData.lastname,lastnameTemp);
                                    strcpy(empData.password,password);
                                    empData.loginhour='t';
                                    empData.logouthour='t';
                                    empData.day='j';
                                    fwrite(&empData,size,1,db);
                                }
                                printf("\n\n\n\t\t\t\tWould like to add another employee?(y/n):");
                                fflush(stdin);
                                anotherEmp=getche();
                                printf("\n");

                        }
            }

        }break;
        case 2:
        system("cls");
        printf("\n\t\t\t\t\t\t\tVIEW EMPLOYEE INFORMATION\n\n\n");
        printf("----------------------------------------------------------------------------------------------------------------------------------\n\n");
        printf("EMPLOYEE ID\t\t\tEMPLOYEE NAME\t\t\tTIME LOGGED IN\t\t\tTIME LOGGED OUT\t\t\tDATE\n\n");
        printf("----------------------------------------------------------------------------------------------------------------------------------\n\n");
        rewind(db);

        while(fread(&empData,size,1,db)==1)
        {
            empData.firstname[0]=toupper(empData.firstname[0]);
            empData.lastname[0]=toupper(empData.lastname[0]);
            printf("\n\n%d \t\t\t",empData.empid);
            printf("\t%s%s",empData.lastname,empData.firstname);
            if(empData.loginhour=='t')
            {
                printf("\t\t\tNot Logged In");

            }
            else{
                printf("\t\t\t%d:%d:%d",empData.loginhour,empData.loginmin,empData.loginsec);
            }
            if (empData.logouthour=='t')
            {
                printf("\t\t\tNot Logged Out\t\t");
            }
            else{
                printf("\t\t\t%d:%d:%d",empData.logouthour,empData.logoutmin,empData.logoutsec);
            }
            if(empData.day=='j')
            {

                printf("\t\t\tNo Date");
            }
            else{
                printf("\t\t%d/%d/%d ",empData.mon,empData.day,(empData.yr)+1900);

            }


        }
        getch();
        printf("\n");
        break;
        case 3:
            system("cls");
            printf("\t\t\t\t\t\tSEARCH EMPLOYEE INFORMATION\n\n\n\n");
            printf("\t\t\t\tEnter Employee Id to Search:  ");
            scanf("%d",&searchId);
            printf("\n\n\n");
            findEmployee=='f';
            rewind(db);
            while(fread(&empData,size,1,db)==1)
            {
                if(empData.empid==searchId)
                {
                    printf("\t\t\t\tEMPLOYEE INFORMATION IS AVALIABLE.\n\n\n");
                    printf("\t\t\t\tEmployee name is:%s %s\n\n",empData.lastname,empData.firstname);
                if(empData.loginhour=='t')
                {
                    printf("\t\t\t\tLog In Time is:Not Logged In\n\n");
                }
                else{
                    printf("\t\t\t\tLog In Time is:%d:%d:%d",empData.loginhour,empData.loginsec);
                }
                if(empData.logouthour=='t')
                {
                    printf("\t\t\t\tLog Out Time is:Not Logged Out\n\n");
                }
                else
                {
                    printf("\t\t\t\tLog Out Time is:%d:%d:%d",empData.logouthour,empData.logoutmin,empData.logoutsec);

                }
                findEmployee='t';
                getch();
                }
            }
                if(findEmployee!='t')
                {
                    printf("\t\t\t\tEmployee Information not available. Please modify the search.");
                    getch();
                }

                 break;
        case 4:
            system("cls");
            printf("\t\t\t\t\t\tREMOVE AN  EMPLOYEE\n\n\n\n");
            printf("\t\t\t\tEnter Employee Id to Delete: ");
            scanf("%d",&searchId);
            printf("\n\n");
            findEmployee='f';
            rewind(db);
            while(fread(&empData,size,1,db)==1)
            {
                if(empData.empid==searchId)
                {
                    printf("t\t\t\tEmployee Information is Available\n\n");
                    printf("t\t\t\tEmployee name is:%s %s",empData.lastname,empData.firstname);
                    findEmployee='t';
                    printf("\n\n");
                }
            }
            if(findEmployee!='t')
            {
                printf("t\t\t\tEmployee Information is available.Please modify the search.");
                getch();
            }
            if(findEmployee=='t')
            {
                printf("t\t\t\tDo you want to delete the Employee?(y/n)");
                confirmDelete=getche();
                if(confirmDelete=='y'|| confirmDelete=='Y')
                {
                    tempdb=fopen("tempo.dat","wb+");
                    rewind(db);
                    while(fread(&empData,size,1,db)==1)
                    {
                        if(empData.empid!=searchId)
                        {
                            fseek(tempdb,0,SEEK_END);
                            fwrite(&empData,size,1,tempdb);
                        }
                    }
                    fclose(tempdb);
                    fclose(db);
                    remove("empbase.dat");
                    rename("tempo.dat","empbase.dat");
                    db=fopen("empbase.dat","rb+");
                }
            }
            break;

        case 6:
            system("cls");
            printf("\n\n\t\t\t\t\t\tDAILY EMPLOYEE TIME RECORDING SYSTEM\n\n");
            printf("\t\t\t\tWarning! Please Enter Numeric Values Only.\n\n");
            printf("\n\n\t\t\t\t\tEnter Your Login Id:");
            scanf("%d",&searchId);

            printf("\n\n\n");
            findEmployee='f';
            rewind(db);
            while(fread(&empData,size,1,db)==1)
            {
                if(empData.empid==searchId)
                {
                    printf("\t\t\t\t\tEnter your Password: ");
                    for(int i=0;i<6;i++)
                    {
                        pass[i]=getch();
                        printf("* ");
                    }
                    pass[6]='\0';
                    printf("\n\n\n");
                    while(getch()!=13);

                        if(strcmp(empData.password,pass))
                        {
                            printf("\n\n\t\t\t\t\tYou Have Supplied a wrong password.");
                            findEmployee='t';
                            getch();
                            break;
                        }
                        printf("\n\n\n\t\t\t\tEmployee name:%s %s",empData.lastname,empData.firstname);

                        printf("\n\n\t\t\t\tYour Login time :,%2d:%2d:%2d",now->tm_hour,now->tm_min,now->tm_sec);
                        printf("\n\n\t\t\t\tYour Login Date :,%d:%d:%d",now->tm_mon,now->tm_mday,now->tm_year);
                        empData.day=now->tm_mday;
                        empData.mon=now->tm_mon;
                        empData.yr=now->tm_year;
                        fseek(db,-size,SEEK_CUR);
                        empData.loginhour=now->tm_hour;
                        empData.loginmin=now->tm_min;
                        empData.loginsec=now->tm_sec;
                        fwrite(&empData,size,1,db);
                        findEmployee='t';
                        getch();




                }}
                if (findEmployee!='t')
                {
                    printf("\n\n\n\t\t\tEmployee Information is not Available.");
                    getch();
                }
            break;
        case 7:
            printf("\n\n\t\t\t\t\t\t\tDAILY EMPLOYEE TIME RECORDING SYSTEM");
            printf("\n\n\t\t\t\tWarning Please Enter Numeric Values Only.");
            printf("\n\n\n\t\t\t\tEnter  Your Id to Logout:");
            scanf("%d",&searchId);

            findEmployee='f';
            rewind(db);
            while(fread(&empData,size,1,db)==1)
            {
                if(empData.empid==searchId)
                {
                    printf("\n\n\t\t\t\tEnter the password:");
                    for(int i=0;i<6;i++)
                    {
                        pass[i]=getch();
                        printf("* ");
                    }
                    pass[6]='\0';
                    while(getch()!=13);
                    if(strcmp(empData.password,pass))
                    {
                        printf("\n\n\t\t\t\tYou Have Supplied a wrong Password.");
                        findEmployee='t';
                        getch();
                        break;

                    }
                    printf("\n\n\t\t\t\tYou have successfully logged Out of the System.");
                    printf("\n\n\t\t\t\tEmployee name is:%s %s",empData.lastname,empData.firstname);


                    printf("\n\n\t\t\t\tYour Log Out Time:%2d:%2d:%2d",now->tm_hour,now->tm_min,now->tm_sec);
                    printf("\n\n\t\t\t\tYour Log Out Date:%d:%d:%d",now->tm_mon,now->tm_mday,(now->tm_year)+1900);
                    fseek(db,-size,SEEK_CUR);
                    empData.logouthour=now->tm_hour;
                    empData.logoutmin=now->tm_min;
                    empData.logoutsec=now->tm_sec;
                    fwrite(&empData,size,1,db);
                    findEmployee='t';
                    getch();


                }
            }
            if(findEmployee!='t')
            {
                printf("Employee Information is not avaliable.");
                getch();
            }
            break;
        case 8:
            printf("\n");
            exit(0);
                }
                fclose(db);
                showMenu=1;





}

    }



void dataentry(){
char adminName[10],passwd[5],buffer[1];
char tempo[6],sel[1];
int validUserNameOption,validUserPwdOption,returnOption,UserName,inc,tmp;
char plus;
system("cls");
validUserNameOption=0;
validUserPwdOption=0;
while(validUserPwdOption==0)
{
    system("cls");
    while(validUserNameOption==0)
    {
        system("cls");
        printf("\n\n\n\n\t\t\t\t\tIT SOFTWARE DATA ENTRY ADMIN INTERFACE \n\n\n");
        printf("\t\t\t\tEnter Administrator name:");
        scanf("%s",&adminName);
        returnOption=strcmp(adminName,"return");
        UserName=strcmp(adminName,"admin");
        if(returnOption==0)
        {
            goto stream;
        }
        if(!(UserName==0 || returnOption==0))
        {
            printf("\n\t\t\t\tAdministrator Name is Invalid.");
            validUserNameOption=0;
        }
        else{
            validUserNameOption=1;
        }

    }
    printf("\n\n\t\t\t\tEnter Password:");
    inc=0;
    while(inc<5)
    {
        passwd[inc]=getch();
        inc=inc+1;
        printf("* ");
    }
    inc=0;
    while(inc<5)
    {
        tempo[inc]=passwd[inc];
        inc=inc+1;
    }
    while(getch()!=13);
    if(!strcmp(tempo,"admin12"))
    {
        printf("\n\n\t\t\t\t\tYou have entered a wrong password. Please Try Again.");
        getch();
        validUserPwdOption=0;
        validUserNameOption=0;
    }
    else{
        system("cls");
        printf("\n\n\t\t\t\t\tYou Have Successfully Logged In.\n");
        printf("\n\t\t\t\t\tPress Any Key to Continue:");
        validUserNameOption=1;
        validUserPwdOption=1;
        getch();
        showAdminMenu=0;
        while(showAdminMenu==0)
        {
            system("cls");
            printf("\n\n\t\t\t\t\t ADMIN OPTIONS\n\n");
            printf("\t\t\t\t 1.)\t Add New Employee\n\n");
            printf("\t\t\t\t 2.)\t show Daily Entries\n\n");
            printf("\t\t\t\t 3.)\t search employee record\n\n");
            printf("\t\t\t\t 4.)\t Remove Employee\n\n");
            printf("\t\t\t\t 5.)\t Close\n\n");
            printf("\t\t\t\tPlease enter your choice:");
            selectAdminOption();

        }

    }

}stream:{}}


void main()
{
   int cancelOption,timeOption,entryOption,exitOption;
   char choice[1];
   char selectOption[1];
   cancelOption=0;
   while(cancelOption==0)
   {
       system("cls");
       printf("\n\n\n\n\t\t\t\t\tPLEASE SELECT AN ACTION \n\n\n");
       printf("\t\t\t\t 1.)\tTime Record\n\n");
       printf("\t\t\t\t 2.)\tData Entry\n\n");
       printf("\t\t\t\t 3.)\tClose\n\n");
       printf("\t\t\t\t\tPlease Enter your Choice(1/2/3):");

       scanf("%s",&choice);

       timeOption=strcmp(choice,"1");
       entryOption=strcmp(choice,"2");
       exitOption=strcmp(choice,"3");
       if(timeOption==0)
       {
           system("cls");
           printf("\n\n\n\n\t\t\t\t\t DAILY EMPLOYEE TIME RECORDING SYSTEM\n\n\n");

           printf("\t\t\t\t 1.)\t Employee LogIn\n\n");
           printf("\t\t\t\t 2.)\t Employee Logout\n\n");
           printf("\t\t\t\t\tPlease Enter Your Option:");
           scanf("%s",&selectOption);

           if (strcmp(selectOption,"1")==0){
            getdata(6);

           }
           if(strcmp(selectOption,"2")==0){
            getdata(7);
           }

           cancelOption=0;
       }
       if(entryOption==0){
        dataentry();
        cancelOption=0;
       }
       if(exitOption==0){
        cancelOption=1;
       }
       if(!(timeOption==0 || entryOption==0 || exitOption==0))
       {
           printf("You have Entered an Invalid Option .Please Choose Either 1,2 or 3.");
           getch();
           cancelOption=0;
       }
   }
   system("cls");
   printf("The Application will Close Now .Thanks!");
return 0;
    }



