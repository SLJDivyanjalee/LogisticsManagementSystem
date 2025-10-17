#include <stdio.h>
#include <stdlib.h>

void mainMenu();
void reports();

int main()
{
    printf("\n  === Logistics Management System ===\n");
    printf("---------------------------------------\n");
    mainMenu();
    return 0;
}

void mainMenu(){
    int choiceMenu;
    do{
    printf("\n       Main Menu\n");
    printf(" 01. City Management\n");
    printf(" 02. Distance Management\n");
    printf(" 03. Vehicle Management\n");
    printf(" 04. Delivery Request Handling\n");
    printf(" 05. Cost, Time, and Fuel Calculations\n");
    printf(" 06. Delivery Records\n");
    printf(" 07. Finding the Least-Cost Route\n");
    printf(" 08. Exit\n\n");

    printf("Enter your choice (1-8): ");
    scanf("%d", &choiceMenu);

    switch(choiceMenu){
    case 1:
         printf(" \n01. City Management\n");
         break;
    case 2:
        printf(" \n02. Distance Management\n");
         break;
    case 3:
        printf(" \n03. Vehicle Management\n");
         break;
    case 4:
        printf(" \n04. Delivery Request Handling\n");
         break;
    case 5:
        printf(" \n05. Cost, Time, and Fuel Calculations\n");
         break;
    case 6:
        printf(" \n06. Delivery Records: \n");
        reports();
         break;
    case 7:
        printf(" \n07. Finding the Least-Cost Route\n");
         break;
    case 8:
        printf(" \nExiting from the system\n");
         break;
    default:
        printf(" \nInvalid input. please try again\n");
         break;
    }
    } while(choiceMenu != 8);
}

void reports(){

    char choiceReport;
do{
    printf("\n=== Performance Reports ===\n");
    printf(" a. Total Deliveries Completed\n");
    printf(" b. Total Distance Covered\n");
    printf(" c. Average Delivery Time\n");
    printf(" d. Total Revenue and profit\n");
    printf(" e. Longest and Shortest Routes Completed\n");
    printf(" f. Back to Main Menu\n\n");

    printf("Enter your choice (a-f): ");
    scanf(" %c", &choiceReport);

    switch(choiceReport){
    case 'a':
        printf(" \n a. Total Deliveries Completed");
         break;
    case 'b':
        printf(" \n b. Total Distance Covered");
         break;
    case 'c':
        printf(" \n c. Average Delivery Time");
         break;
    case 'd':
        printf(" \n d. Total Revenue and Profit");
         break;
    case 'e':
        printf(" \n e. Longest and Shortest Routes Completed");
         break;
    case 'f'://back to main menu
        break;
    default:
        printf(" \n Invalid input. please try again");
         break;
    }
    }while(choiceReport != 'f');
}
