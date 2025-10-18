#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 50

void mainMenu();
void reports();
void cityManagement();

// City Management Functions
void displayCityMenu();
void addCity(char cities[][NAME_LENGTH], int *count);
void displayCities(char cities[][NAME_LENGTH], int count);
void renameCity(char cities[][NAME_LENGTH], int count);
void removeCity(char cities[][NAME_LENGTH], int *count);
int findCity(char cities[][NAME_LENGTH], int count, char name[]);
void toLowerCase(char str[]);

char cities[MAX_CITIES][NAME_LENGTH];
int cityCount = 0;

int main()
{
    printf("\n      Logistics Management System  \n");
    printf("---------------------------------------\n");
    mainMenu();
    return 0;
}

//-------main features-------------------
void mainMenu(){
    int choiceMenu;
    do{
    printf("\n      .-Main Menu-.\n");
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
         printf("\n--- City Management ---\n");
         cityManagement();
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

// ---------menu option “Reports”-----------------
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


// --------- City Management -----------------
void cityManagement() {
    int choice;

    printf("Maximum capacity: %d cities\n\n", MAX_CITIES);

    do {
        displayCityMenu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addCity(cities, &cityCount);
                break;
            case 2:
                displayCities(cities, cityCount);
                break;
            case 3:
                renameCity(cities, cityCount);
                break;
            case 4:
                removeCity(cities, &cityCount);
                break;
            case 5:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while (choice != 5);
}

void displayCityMenu() {
    printf("  Menu \n");
    printf("1. Add a new city\n");
    printf("2. Display all cities\n");
    printf("3. Rename a city\n");
    printf("4. Remove a city\n");
    printf("5. Back to Main Menu\n");
}

void addCity(char cities[][NAME_LENGTH], int *count) {
    if (*count >= MAX_CITIES) {
        printf("Error: Maximum capacity reached! Cannot add more cities.\n");
        return;
    }

    char cityName[NAME_LENGTH];
    printf("Enter city name: ");
    fgets(cityName, NAME_LENGTH, stdin);

    cityName[strcspn(cityName, "\n")] = 0;

    // validate input
    if (strlen(cityName) == 0) {
        printf("Error: City name cannot be empty!\n");
        return;
    }

    // check if city already exists
    if (findCity(cities, *count, cityName) != -1) {
        printf("Error: City '%s' already exists!\n", cityName);
        return;
    }

    // add city to the array
    strcpy(cities[*count], cityName);
    (*count)++;
    printf("City '%s' added successfully!\n", cityName);
}

void displayCities(char cities[][NAME_LENGTH], int count) {
    if (count == 0) {
        printf("No cities in the system.\n");
        return;
    }

    printf("=== List of Cities (%d/%d) ===\n", count, MAX_CITIES);
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
}

void renameCity(char cities[][NAME_LENGTH], int count) {
    if (count == 0) {
        printf("No cities available to rename.\n");
        return;
    }

    char oldName[NAME_LENGTH];
    char newName[NAME_LENGTH];

    printf("Enter current city name: ");
    fgets(oldName, NAME_LENGTH, stdin);
    oldName[strcspn(oldName, "\n")] = 0;

    int index = findCity(cities, count, oldName);
    if (index == -1) {
        printf("Error: City '%s' not found!\n", oldName);
        return;
    }

    printf("Enter new city name: ");
    fgets(newName, NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = 0;

    // validate new name
    if (strlen(newName) == 0) {
        printf("Error: New city name cannot be empty!\n");
        return;
    }

    // check if new name already exists
    for (int i = 0; i < count; i++) {
        if (i != index) {
            char temp1[NAME_LENGTH], temp2[NAME_LENGTH];
            strcpy(temp1, cities[i]);
            strcpy(temp2, newName);
            toLowerCase(temp1);
            toLowerCase(temp2);

            if (strcmp(temp1, temp2) == 0) {
                printf("Error: City '%s' already exists!\n", newName);
                return;
            }
        }
    }

    printf("City renamed from '%s' to '%s'\n", cities[index], newName);
    strcpy(cities[index], newName);
}

void removeCity(char cities[][NAME_LENGTH], int *count) {
    if (*count == 0) {
        printf("No cities available to remove.\n");
        return;
    }

    char cityName[NAME_LENGTH];
    printf("Enter city name to remove: ");
    fgets(cityName, NAME_LENGTH, stdin);
    cityName[strcspn(cityName, "\n")] = 0;

    int index = findCity(cities, *count, cityName);
    if (index == -1) {
        printf("Error: City '%s' not found!\n", cityName);
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        strcpy(cities[i], cities[i + 1]);
    }

    (*count)--;
    printf("City '%s' removed successfully!\n", cityName);
}

int findCity(char cities[][NAME_LENGTH], int count, char name[]) {
    char searchName[NAME_LENGTH];
    strcpy(searchName, name);
    toLowerCase(searchName);

    for (int i = 0; i < count; i++) {
        char currentCity[NAME_LENGTH];
        strcpy(currentCity, cities[i]);
        toLowerCase(currentCity);

        if (strcmp(currentCity, searchName) == 0) {
            return i;
        }
    }
    return -1;
}

void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

