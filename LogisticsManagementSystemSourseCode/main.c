#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 50
#define NUM_VEHICLES 3
#define MAX_DELIVERIES 100

void mainMenu();
void reports();
void cityManagement();
void distanceManagement();
void vehicleManagement();
void deliveryRequestHandling();
void costTimeFuelCalculations();

// City Management Functions
void displayCityMenu();
void addCity(char cities[][NAME_LENGTH], int *count);
void displayCities(char cities[][NAME_LENGTH], int count);
void renameCity(char cities[][NAME_LENGTH], int count);
void removeCity(char cities[][NAME_LENGTH], int *count);
int findCity(char cities[][NAME_LENGTH], int count, char name[]);
void toLowerCase(char str[]);

// Distance Management Functions
void displayDistanceMenu();
void initializeDistances(int distances[][MAX_CITIES]);
void inputDistance(char cities[][NAME_LENGTH], int cityCount, int distances[][MAX_CITIES]);
void editDistance(char cities[][NAME_LENGTH], int cityCount, int distances[][MAX_CITIES]);
void displayDistanceTable(char cities[][NAME_LENGTH], int cityCount, int distances[][MAX_CITIES]);

// Vehicle Management Functions
void displayVehicleMenu();
void initializeVehicles();
void displayVehicles();
int selectVehicle();

//Delivery Request Dealing Functions
void displayDeliveryMenu();
void processDelivery();

// vehicle structure
typedef struct {
    char type[20];
    int capacity;
    int ratePerKm;
    int avgSpeed;
    int fuelEfficiency;
} Vehicle;

// delivery structure
typedef struct {
    int deliveryId;
    int sourceCity;
    int destinationCity;
    int weight;
    int vehicleType;
    int completed;
} Delivery;


char cities[MAX_CITIES][NAME_LENGTH];
int cityCount = 0;

int distances[MAX_CITIES][MAX_CITIES];

Vehicle vehicles[NUM_VEHICLES];

Delivery deliveries[MAX_DELIVERIES];
int deliveryCount = 0;
int nextDeliveryId = 1;

int main()
{
    printf("\n      Logistics Management System  \n");
    printf("---------------------------------------\n");
    initializeDistances(distances);
    initializeVehicles();
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
    printf(" 05. Cost, Time and Fuel Calculations\n");
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
        printf(" \n--- Distance Management ---\n");
         distanceManagement();
         break;
    case 3:
        printf(" \n--- Vehicle Management ---\n");
        vehicleManagement();
         break;
    case 4:
        printf(" \n--- Delivery Request Handling ---\n");
        deliveryRequestHandling();
         break;
    case 5:
        printf(" \n05. Cost, Time, and Fuel Calculations\n");
        costTimeFuelCalculations();
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
    printf(" \tMenu \n");
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


// ---------Distance Management System-----------------
void distanceManagement() {
    int choice;

    do {
        displayDistanceMenu();
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                inputDistance(cities, cityCount, distances);
                break;
            case 2:
                editDistance(cities, cityCount, distances);
                break;
            case 3:
                displayDistanceTable(cities, cityCount, distances);
                break;
            case 4:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while (choice != 4);
}

void displayDistanceMenu() {
    printf(" \tMenu \n");
    printf("1. Input distance between cities\n");
    printf("2. Edit distance between cities\n");
    printf("3. Display distance table\n");
    printf("4. Back to Main Menu\n");
}

void initializeDistances(int distances[][MAX_CITIES]) {

    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            if (i == j) {
                distances[i][j] = 0;
            } else {
                distances[i][j] = -1;
            }
        }
    }
}

void inputDistance(char cities[][NAME_LENGTH], int cityCount, int distances[][MAX_CITIES]) {
    if (cityCount < 2) {
        printf("Error: Need at least 2 cities to input distances!\n");
        return;
    }

    char city1[NAME_LENGTH], city2[NAME_LENGTH];
    int distance;

    // Display available cities
    printf("\nAvailable cities:\n");
    displayCities(cities, cityCount);

    // Get first city
    printf("\nEnter first city name: ");
    fgets(city1, NAME_LENGTH, stdin);
    city1[strcspn(city1, "\n")] = 0;

    int index1 = findCity(cities, cityCount, city1);
    if (index1 == -1) {
        printf("Error: City '%s' not found!\n", city1);
        return;
    }

    // Get second city
    printf("Enter second city name: ");
    fgets(city2, NAME_LENGTH, stdin);
    city2[strcspn(city2, "\n")] = 0;

    int index2 = findCity(cities, cityCount, city2);
    if (index2 == -1) {
        printf("Error: City '%s' not found!\n", city2);
        return;
    }

    // Check if same city
    if (index1 == index2) {
        printf("Error: Cannot set distance from city to itself! (Already set to 0)\n");
        return;
    }

    // Get distance
    printf("Enter distance between %s and %s (in km): ", cities[index1], cities[index2]);
    scanf("%d", &distance);

    // Validate distance
    if (distance <= 0) {
        printf("Error: Distance must be positive!\n");
        return;
    }

    distances[index1][index2] = distance;
    distances[index2][index1] = distance;

    printf("Distance between %s and %s set to %d km\n", cities[index1], cities[index2], distance);

    while (getchar() != '\n');
}

void editDistance(char cities[][NAME_LENGTH], int cityCount, int distances[][MAX_CITIES]) {
    if (cityCount < 2) {
        printf("Error: Need at least 2 cities to edit distances!\n");
        return;
    }

    char city1[NAME_LENGTH], city2[NAME_LENGTH];
    int distance;

    displayDistanceTable(cities, cityCount, distances);

    // Get cities
    printf("\nEnter first city name: ");
    fgets(city1, NAME_LENGTH, stdin);
    city1[strcspn(city1, "\n")] = 0;

    int index1 = findCity(cities, cityCount, city1);
    if (index1 == -1) {
        printf("Error: City '%s' not found!\n", city1);
        return;
    }

    printf("Enter second city name: ");
    fgets(city2, NAME_LENGTH, stdin);
    city2[strcspn(city2, "\n")] = 0;

    int index2 = findCity(cities, cityCount, city2);
    if (index2 == -1) {
        printf("Error: City '%s' not found!\n", city2);
        return;
    }

    // Check if same city
    if (index1 == index2) {
        printf("Error: Cannot edit distance from city to itself! (Always 0)\n");
        return;
    }

    // Check if distance exists
    if (distances[index1][index2] == -1) {
        printf("Error: No distance set between %s and %s. Use 'Input distance' first.\n", cities[index1], cities[index2]);
        return;
    }

    printf("Current distance between %s and %s: %d km\n", cities[index1], cities[index2], distances[index1][index2]);

    // Get new distance
    printf("Enter new distance (in km): ");
    scanf("%d", &distance);

    // Validate distance
    if (distance <= 0) {
        printf("Error: Distance must be positive!\n");
        return;
    }

    distances[index1][index2] = distance;
    distances[index2][index1] = distance;

    printf("Distance updated successfully!\n");

    while (getchar() != '\n');
}

void displayDistanceTable(char cities[][NAME_LENGTH], int cityCount, int distances[][MAX_CITIES]) {
    if (cityCount == 0) {
        printf("No cities in the system.\n");
        return;
    }

    printf("\n=== Distance Table (in km) ===\n\n");

    // Print header row with city names
    printf("%-15s", "");
    for (int i = 0; i < cityCount; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < (cityCount + 1) * 15; i++) {
        printf("-");
    }
    printf("\n");

    // Print distance matrix
    for (int i = 0; i < cityCount; i++) {
        printf("%-15s", cities[i]);

        for (int j = 0; j < cityCount; j++) {
            if (i == j) {
                printf("%-15s", "0");  // Distance to itself
            } else if (distances[i][j] == -1) {
                printf("%-15s", "-");  // Distance not set
            } else {
                printf("%-15d", distances[i][j]);
            }
        }
        printf("\n");
    }
}


// ---------Vehicle Management System-----------------
void vehicleManagement() {
    int choice;

    do {
        displayVehicleMenu();
        printf("Enter your choice (1-2): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                selectVehicle();
                break;
            case 2:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while (choice != 2);
}

void displayVehicleMenu() {
    printf(" \tMenu\n");
    printf("1. Select vehicle for estimation\n");
    printf("2. Back to Main Menu\n\n");
}

void initializeVehicles() {
    // Initialize Van
    strcpy(vehicles[0].type, "Van");
    vehicles[0].capacity = 1000;
    vehicles[0].ratePerKm = 30;
    vehicles[0].avgSpeed = 60;
    vehicles[0].fuelEfficiency = 12;

    // Initialize Truck
    strcpy(vehicles[1].type, "Truck");
    vehicles[1].capacity = 5000;
    vehicles[1].ratePerKm = 40;
    vehicles[1].avgSpeed = 50;
    vehicles[1].fuelEfficiency = 6;

    // Initialize Lorry
    strcpy(vehicles[2].type, "Lorry");
    vehicles[2].capacity = 10000;
    vehicles[2].ratePerKm = 80;
    vehicles[2].avgSpeed = 45;
    vehicles[2].fuelEfficiency = 4;
}

void displayVehicles() {
    printf("\n    - Available Vehicle Types -\n\n");
    printf("%-10s %-12s %-15s %-12s %-18s\n",
           "Type", "Capacity(kg)", "Rate per km(LKR)", "Avg Speed(km/h)", "Fuel Efficiency(km/l)");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < NUM_VEHICLES; i++) {
        printf("%-12s %-13d %-16d %-17d %-20d\n",
               vehicles[i].type,
               vehicles[i].capacity,
               vehicles[i].ratePerKm,
               vehicles[i].avgSpeed,
               vehicles[i].fuelEfficiency);
    }
}

int selectVehicle() {
    int choice;

    displayVehicles();

    printf("\n\nSelect vehicle type:\n");
    printf("1. Van (Capacity: 1000kg)\n");
    printf("2. Truck (Capacity: 5000kg)\n");
    printf("3. Lorry (Capacity: 10000kg)\n");
    printf("\nEnter your choice (1-3): ");
    scanf("%d", &choice);

    while (getchar() != '\n');

    if (choice >= 1 && choice <= 3) {
        int index = choice - 1;
        printf("\nVehicle selected: %s\n", vehicles[index].type);
        printf("Capacity: %d kg\n", vehicles[index].capacity);
        printf("Rate per km: LKR %d\n", vehicles[index].ratePerKm);
        printf("Average Speed: %d km/h\n", vehicles[index].avgSpeed);
        printf("Fuel Efficiency: %d km/l\n", vehicles[index].fuelEfficiency);

        return index;
    } else {
        printf("Invalid choice! Please try again.\n");
        return -1;
    }
}


// ---------Delivery Request Handling System-----------------
void deliveryRequestHandling() {
    int choice;

    do {
        displayDeliveryMenu();
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                processDelivery();
                break;
            case 2:
                displayActiveDeliveries();
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while (choice != 3);
}

void displayDeliveryMenu() {
    printf(" \tMenu\n");
    printf("1. Create new delivery request\n");
    printf("2. View active deliveries\n");
    printf("3. Back to Main Menu\n");
}

void processDelivery() {
    if (cityCount < 2) {
        printf("Error: Need at least 2 cities to create delivery!\n");
        return;
    }

    if (deliveryCount >= MAX_DELIVERIES) {
        printf("Error: Maximum delivery capacity reached!\n");
        return;
    }

    int source, destination, weight, vehicleChoice;

    printf("\nAvailable cities:\n");
    displayCities(cities, cityCount);

    printf("\nEnter source city number (1-%d): ", cityCount);
    scanf("%d", &source);
    if (source < 1 || source > cityCount) {
        printf("Error: Invalid source city!\n");
        return;
    }
    source--;

    printf("Enter destination city number (1-%d): ", cityCount);
    scanf("%d", &destination);
    if (destination < 1 || destination > cityCount) {
        printf("Error: Invalid destination city!\n");
        return;
    }
    destination--;

    // Validate source != destination
    if (source == destination) {
        printf("Error: Source and destination cannot be the same!\n");
        return;
    }

    // Check if distance exists between cities
    if (distances[source][destination] == -1) {
        printf("Error: No distance set between %s and %s!\n", cities[source], cities[destination]);
        return;
    }

    // Get weight
    printf("Enter package weight (kg): ");
    scanf("%d", &weight);
    if (weight <= 0) {
        printf("Error: Weight must be positive!\n");
        return;
    }

    printf("\nAvailable vehicles:\n");
    displayVehicles();
    printf("\nSelect vehicle type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicleChoice);

    while (getchar() != '\n');

    if (vehicleChoice < 1 || vehicleChoice > 3) {
        printf("Error: Invalid vehicle choice!\n");
        return;
    }

    int vehicleIndex = vehicleChoice - 1;

    if (weight > vehicles[vehicleIndex].capacity) {
        printf("Error: Weight (%d kg) exceeds %s capacity (%d kg)!\n",
               weight, vehicles[vehicleIndex].type, vehicles[vehicleIndex].capacity);
        return;
    }

    // Create delivery record
    deliveries[deliveryCount].deliveryId = nextDeliveryId++;
    deliveries[deliveryCount].sourceCity = source;
    deliveries[deliveryCount].destinationCity = destination;
    deliveries[deliveryCount].weight = weight;
    deliveries[deliveryCount].vehicleType = vehicleIndex;
    deliveries[deliveryCount].completed = 0;

    printf("\nDelivery Request Created Successfully!\n");
    printf("Delivery ID: %d\n", deliveries[deliveryCount].deliveryId);
    printf("Route: %s => %s\n", cities[source], cities[destination]);
    printf("Distance: %d km\n", distances[source][destination]);
    printf("Weight: %d kg\n", weight);
    printf("Vehicle: %s\n", vehicles[vehicleIndex].type);
    printf("Status: Pending\n");

    deliveryCount++;
}

void displayActiveDeliveries() {
    if (deliveryCount == 0) {
        printf("No active deliveries.\n");
        return;
    }

    printf("\n\t Active Deliveries (%d) \n\n", deliveryCount);
    printf("%-12s %-20s %-12s %-10s %-15s %-10s\n",
           "Delivery ID", "Route", "Distance", "Weight", "Vehicle", "Status");
    printf("------------------------------------------------------------------------\n");

    int activeCount = 0;
    for (int i = 0; i < deliveryCount; i++) {
        if (!deliveries[i].completed) {
            printf("%-12d %s => %-8s %-12d %-10d %-15s %-10s\n",
                   deliveries[i].deliveryId,
                   cities[deliveries[i].sourceCity],
                   cities[deliveries[i].destinationCity],
                   distances[deliveries[i].sourceCity][deliveries[i].destinationCity],
                   deliveries[i].weight,
                   vehicles[deliveries[i].vehicleType].type,
                   "Pending");
            activeCount++;
        }
    }

    if (activeCount == 0) {
        printf("No pending deliveries.\n");
    }
}

// ---------Cost, Time and Fuel Calculations System-----------------
void costTimeFuelCalculations() {
    int choice;

    printf("\n--- Cost, Time and Fuel Calculations ---\n");

    do {
        printf(" \tMenu\n");
        printf("1. Calculate cost for delivery\n");
        printf("2. View all calculations\n");
        printf("3. Back to Main Menu\n");

        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Calculate cost for delivery\n");
                break;
            case 2:
                 printf("View all calculations\n");
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while (choice != 3);
}
