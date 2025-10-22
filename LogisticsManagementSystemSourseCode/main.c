#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 50
#define NUM_VEHICLES 3
#define MAX_DELIVERIES 100
#define FUEL_PRICE 310 // LKR per liter
#define INF 1000000

void mainMenu();
void reports();
void cityManagement();
void distanceManagement();
void vehicleManagement();
void deliveryRequestHandling();
void costTimeFuelCalculations();
void leastCostRoute();
void deliveryRecords();
void performanceReports();

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

// Delivery Request Dealing Functions
void displayDeliveryMenu();
void processDelivery();

// Cost, Time, and Fuel Calculations
void costTimeFuelCalculations();
void calculateDeliveryCost();
void displayCalculationResults(int deliveryIndex);

//Finding the Least-Cost Route
void displayRouteMenu();
void findLeastCostRoute();
int findPath(int source, int destination, int path[]);
void displayRoute(int source, int destination, int path[], int distance);
void displayAllOptimalRoutes();

// Delivery Records
void displayRecordsMenu();
void viewAllDeliveries();
void markDeliveryCompleted();
void viewCompletedDeliveries();
void viewPendingDeliveries();

// Performance Reports
void displayReportsMenu();
void totalDeliveriesCompleted();
void totalDistanceCovered();
void averageDeliveryTime();
void totalRevenueAndProfit();
void longestShortestRoutes();

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

// Calculation structure
typedef struct {
    double deliveryCost;
    double estimatedTime;
    double fuelUsed;
    double fuelCost;
    double totalOperationalCost;
    double profit;
    double customerCharge;
} Calculation;

// Delivery Records structure
typedef struct {
    int deliveryId;
    int sourceCity;
    int destinationCity;
    int weight;
    int vehicleType;
    int completed;
    char completionTime[20];
} Delivery;

// Performance Reports structure
typedef struct {
    int deliveryId;
    int sourceCity;
    int destinationCity;
    int weight;
    int vehicleType;
    int completed;
    char completionTime[20];
    double actualDeliveryTime;
} Delivery;

char cities[MAX_CITIES][NAME_LENGTH];
int cityCount = 0;

int distances[MAX_CITIES][MAX_CITIES];

Vehicle vehicles[NUM_VEHICLES];

Delivery deliveries[MAX_DELIVERIES];
int deliveryCount = 0;
int nextDeliveryId = 1;

Calculation calculations[MAX_DELIVERIES];

int optimalRoutes[MAX_CITIES][MAX_CITIES];

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
    printf(" 08. Performance Reports\n");
    printf(" 09. Exit\n\n");

    printf("Enter your choice (1-9): ");
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
        printf("\n--- Cost, Time and Fuel Calculations ---\n");
        costTimeFuelCalculations();
         break;
    case 6:
        printf("\n--- Delivery Records ---\n");
        deliveryRecords();
         break;
    case 7:
        printf("\n--- Finding the Least-Cost Route ---\n");
         leastCostRoute();
         break;
    case 8:
         printf("\n--- Performance Reports ---\n");
         performanceReports();
         break;
    case 9:
        printf(" \nExiting from the system\n");
         break;
    default:
        printf(" \nInvalid input. please try again\n");
         break;
    }
    } while(choiceMenu !=9);
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
                calculateDeliveryCost();
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

void calculateDeliveryCost() {
    if (deliveryCount == 0) {
        printf("Error: No deliveries available for calculation!\n");
        return;
    }

    int deliveryChoice;

    printf("\nAvailable deliveries:\n");
    displayActiveDeliveries();

    printf("\nEnter delivery ID to calculate cost: ");
    scanf("%d", &deliveryChoice);

    int deliveryIndex = -1;
    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].deliveryId == deliveryChoice && !deliveries[i].completed) {
            deliveryIndex = i;
            break;
        }
    }

    if (deliveryIndex == -1) {
        printf("Error: Delivery ID not found or already completed!\n");
        return;
    }

    int source = deliveries[deliveryIndex].sourceCity;
    int destination = deliveries[deliveryIndex].destinationCity;
    int weight = deliveries[deliveryIndex].weight;
    int vehicleIndex = deliveries[deliveryIndex].vehicleType;

    int distance = distances[source][destination];

    int ratePerKm = vehicles[vehicleIndex].ratePerKm;
    int speed = vehicles[vehicleIndex].avgSpeed;
    int efficiency = vehicles[vehicleIndex].fuelEfficiency;

    // delivery cost: Cost = D * R * (1 + W/10000)
    calculations[deliveryIndex].deliveryCost = distance * ratePerKm * (1 + weight / 10000.0);

    // estimated delivery time (hours): Time = D / S
    calculations[deliveryIndex].estimatedTime = (double)distance / speed;

    // fuel consumption: Fuel Used = D / E
    calculations[deliveryIndex].fuelUsed = (double)distance / efficiency;

    // fuel cost: Fuel Cost = FuelUsed * F
    calculations[deliveryIndex].fuelCost = calculations[deliveryIndex].fuelUsed * FUEL_PRICE;

    // total operational cost: Total Cost = DeliveryCost + FuelCost
    calculations[deliveryIndex].totalOperationalCost =
        calculations[deliveryIndex].deliveryCost + calculations[deliveryIndex].fuelCost;

    // profit calculation: 25% markup on base delivery cost
    calculations[deliveryIndex].profit = calculations[deliveryIndex].deliveryCost * 0.25;

    // final charge to customer: Customer Charge = TotalCost + Profit
    calculations[deliveryIndex].customerCharge =
        calculations[deliveryIndex].totalOperationalCost + calculations[deliveryIndex].profit;

    printf("\nCalculations completed successfully!\n");
     displayCalculationResults(deliveryIndex);
}

void displayCalculationResults(int deliveryIndex) {
    Delivery *delivery = &deliveries[deliveryIndex];
    Calculation *calc = &calculations[deliveryIndex];
    int distance = distances[delivery->sourceCity][delivery->destinationCity];
    int ratePerKm = vehicles[delivery->vehicleType].ratePerKm;
    int weight = delivery->weight;

    printf("\n======================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[delivery->sourceCity]);
    printf("To: %s\n", cities[delivery->destinationCity]);
    printf("Minimum Distance: %d km\n", distance);
    printf("Vehicle: %s\n", vehicles[delivery->vehicleType].type);
    printf("Weight: %d kg\n", weight);
    printf("------------------------------------------------------\n");

    printf("Base Cost: %d x %d x (1 + %d/10000) = %.2f LKR\n",
           distance, ratePerKm, weight, calc->deliveryCost);

    printf("Fuel Used: %.2f L\n", calc->fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", calc->fuelCost);
    printf("Operational Cost: %.2f LKR\n", calc->totalOperationalCost);
    printf("Profit: %.2f LKR\n", calc->profit);
    printf("Customer Charge: %.2f LKR\n", calc->customerCharge);
    printf("Estimated Time: %.2f hours\n", calc->estimatedTime);
    printf("======================================================\n");
}

void viewAllCalculations() {
    if (deliveryCount == 0) {
        printf("No deliveries available.\n");
        return;
    }

    int hasCalculations = 0;

    printf("\n=== All Delivery Calculations ===\n\n");
    printf("%-12s %-20s %-10s %-15s %-15s %-15s\n",
           "Delivery ID", "Route", "Weight", "Total Cost", "Time (hrs)", "Profit");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < deliveryCount; i++) {
        if (calculations[i].customerCharge > 0) {
            printf("%-12d %s -> %-8s %-10d LKR %-11.2f %-14.2f LKR %-11.2f\n",
                   deliveries[i].deliveryId,
                   cities[deliveries[i].sourceCity],
                   cities[deliveries[i].destinationCity],
                   deliveries[i].weight,
                   calculations[i].customerCharge,
                   calculations[i].estimatedTime,
                   calculations[i].profit);
            hasCalculations = 1;
        }
    }

    if (!hasCalculations) {
        printf("No calculations available. Use 'Calculate cost for delivery' first.\n");
    }
}


// ---------Delivery Records -----------------
void deliveryRecords() {
    int choice;

    printf("Maximum capacity: %d deliveries\n\n", MAX_DELIVERIES);

    do {
        displayRecordsMenu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                viewAllDeliveries();
                break;
            case 2:
                viewPendingDeliveries();
                break;
            case 3:
                viewCompletedDeliveries();
                break;
            case 4:
                markDeliveryCompleted();
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

void displayRecordsMenu() {
    printf(" \tMenu\n");
    printf("1. View all deliveries\n");
    printf("2. View pending deliveries\n");
    printf("3. View completed deliveries\n");
    printf("4. Mark delivery as completed\n");
    printf("5. Back to Main Menu\n");
}

void viewAllDeliveries() {
    if (deliveryCount == 0) {
        printf("No delivery records found.\n");
        return;
    }

    printf("\n=== All Delivery Records (%d/%d) ===\n\n", deliveryCount, MAX_DELIVERIES);
    printf("%-12s %-20s %-10s %-15s %-15s %-12s\n",
           "Delivery ID", "Route", "Weight", "Vehicle", "Status", "Completed At");
    printf("-------------------------------------------------------------------------------\n");

    int pendingCount = 0;
    int completedCount = 0;

    for (int i = 0; i < deliveryCount; i++) {
        char status[20];
        char completionInfo[20];

        if (deliveries[i].completed) {
            strcpy(status, "Completed");
            strcpy(completionInfo, deliveries[i].completionTime);
            completedCount++;
        } else {
            strcpy(status, "Pending");
            strcpy(completionInfo, "-");
            pendingCount++;
        }

        printf("%-12d %s -> %-8s %-10d %-15s %-15s %-12s\n",
               deliveries[i].deliveryId,
               cities[deliveries[i].sourceCity],
               cities[deliveries[i].destinationCity],
               deliveries[i].weight,
               vehicles[deliveries[i].vehicleType].type,
               status,
               completionInfo);
    }

    printf("\nSummary: %d pending, %d completed, %d total\n",
           pendingCount, completedCount, deliveryCount);
}

void viewPendingDeliveries() {
    if (deliveryCount == 0) {
        printf("No delivery records found.\n");
        return;
    }

    printf("\n=== Pending Deliveries ===\n\n");
    printf("%-12s %-20s %-10s %-15s %-12s\n",
           "Delivery ID", "Route", "Weight", "Vehicle", "Distance");
    printf("----------------------------------------------------------------\n");

    int pendingCount = 0;

    for (int i = 0; i < deliveryCount; i++) {
        if (!deliveries[i].completed) {
            int distance = distances[deliveries[i].sourceCity][deliveries[i].destinationCity];

            printf("%-12d %s -> %-8s %-10d %-15s %-12d km\n",
                   deliveries[i].deliveryId,
                   cities[deliveries[i].sourceCity],
                   cities[deliveries[i].destinationCity],
                   deliveries[i].weight,
                   vehicles[deliveries[i].vehicleType].type,
                   distance);
            pendingCount++;
        }
    }

    if (pendingCount == 0) {
        printf("No pending deliveries. All deliveries are completed!\n");
    } else {
        printf("\nTotal pending deliveries: %d\n", pendingCount);
    }
}

void viewCompletedDeliveries() {
    if (deliveryCount == 0) {
        printf("No delivery records found.\n");
        return;
    }

    printf("\n=== Completed Deliveries ===\n\n");
    printf("%-12s %-20s %-10s %-15s %-15s\n",
           "Delivery ID", "Route", "Weight", "Vehicle", "Completed At");
    printf("------------------------------------------------------------------------\n");

    int completedCount = 0;

    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].completed) {
            printf("%-12d %s -> %-8s %-10d %-15s %-15s\n",
                   deliveries[i].deliveryId,
                   cities[deliveries[i].sourceCity],
                   cities[deliveries[i].destinationCity],
                   deliveries[i].weight,
                   vehicles[deliveries[i].vehicleType].type,
                   deliveries[i].completionTime);
            completedCount++;
        }
    }

    if (completedCount == 0) {
        printf("No completed deliveries yet.\n");
    } else {
        printf("\nTotal completed deliveries: %d\n", completedCount);
    }
}

void markDeliveryCompleted() {
    if (deliveryCount == 0) {
        printf("No deliveries available to mark as completed.\n");
        return;
    }

    int deliveryId;
    char completionTime[20];

    printf("\nPending deliveries:\n");
    viewPendingDeliveries();

    printf("\nEnter delivery ID to mark as completed: ");
    scanf("%d", &deliveryId);

    while (getchar() != '\n');

    int foundIndex = -1;
    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].deliveryId == deliveryId && !deliveries[i].completed) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Error: Delivery ID not found or already completed!\n");
        return;
    }

    printf("Enter completion time (e.g., 2024-01-15 14:30): ");
    fgets(completionTime, 20, stdin);
    completionTime[strcspn(completionTime, "\n")] = 0;

    deliveries[foundIndex].completed = 1;
    strcpy(deliveries[foundIndex].completionTime, completionTime);

    printf("\nDelivery ID %d marked as completed!\n", deliveryId);
    printf("Route: %s -> %s\n",
           cities[deliveries[foundIndex].sourceCity],
           cities[deliveries[foundIndex].destinationCity]);
    printf("Completed at: %s\n", completionTime);
}

void processDelivery() {
    if (cityCount < 2) {
        printf("Error: Need at least 2 cities to create delivery!\n");
        return;
    }

    if (deliveryCount >= MAX_DELIVERIES) {
        printf("Error: Maximum delivery capacity reached (%d deliveries)! Cannot create new delivery.\n", MAX_DELIVERIES);
        return;
    }
}


// ---------Least Cost Route System-----------------
void leastCostRoute() {
    int choice;

    do {
        printf(" \tMenu\n");
        printf("1. Find least-cost route between cities\n");
        printf("2. Display all optimal routes\n");
        printf("3. Back to Main Menu\n\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                findLeastCostRoute();
                break;
            case 2:
                displayAllOptimalRoutes();
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


void findLeastCostRoute() {
    if (cityCount < 2) {
        printf("Error: Need at least 2 cities to find routes!\n");
        return;
    }

    int source, destination;

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

    if (source == destination) {
        printf("Error: Source and destination cannot be the same!\n");
        return;
    }

    int path[MAX_CITIES];
    int distance = findPath(source, destination, path);

    if (distance == INF) {
        printf("Error: No route exists between %s and %s!\n",
               cities[source], cities[destination]);
        return;
    }

    printf("\nLeast-Cost Route Found!\n");
    displayRoute(source, destination, path, distance);

    optimalRoutes[source][destination] = distance;
}

int findPath(int source, int destination, int path[]) {
    int dist[MAX_CITIES];
    int visited[MAX_CITIES];
    int previous[MAX_CITIES];

    for (int i = 0; i < cityCount; i++) {
        dist[i] = INF;
        visited[i] = 0;
        previous[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < cityCount - 1; count++) {
        int minDist = INF;
        int minIndex = -1;

        for (int v = 0; v < cityCount; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break;
        visited[minIndex] = 1;

        for (int v = 0; v < cityCount; v++) {
            if (!visited[v] && distances[minIndex][v] != -1 &&
                dist[minIndex] != INF &&
                dist[minIndex] + distances[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + distances[minIndex][v];
                previous[v] = minIndex;
            }
        }
    }

    int current = destination;
    int pathLength = 0;

    while (current != -1) {
        path[pathLength++] = current;
        current = previous[current];
    }

    for (int i = 0; i < pathLength / 2; i++) {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    return dist[destination];
}

void displayRoute(int source, int destination, int path[], int distance) {
    int pathLength = 0;

    while (path[pathLength] != destination && pathLength < cityCount) {
        pathLength++;
    }
    pathLength++;

    printf("\n======================================================\n");
    printf("LEAST-COST ROUTE ANALYSIS\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[source]);
    printf("To: %s\n", cities[destination]);
    printf("------------------------------------------------------\n");

    printf("Optimal Route: ");
    for (int i = 0; i < pathLength; i++) {
        printf("%s", cities[path[i]]);
        if (i < pathLength - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    printf("Total Distance: %d km\n", distance);

    int directDistance = distances[source][destination];
    if (directDistance != -1 && directDistance != distance) {
        printf("Direct Route Distance: %d km\n", directDistance);
        printf("Savings: %d km (%.1f%%)\n",
               directDistance - distance,
               ((double)(directDistance - distance) / directDistance) * 100);
    }

    printf("------------------------------------------------------\n");

    printf("Route Breakdown:\n");
    int total = 0;
    for (int i = 0; i < pathLength - 1; i++) {
        int segment = distances[path[i]][path[i+1]];
        printf("  %s -> %s: %d km\n",
               cities[path[i]], cities[path[i+1]], segment);
        total += segment;
    }
    printf("  Total: %d km\n", total);

    printf("======================================================\n");
}

void displayAllOptimalRoutes() {
    if (cityCount < 2) {
        printf("Need at least 2 cities to display routes.\n");
        return;
    }

    printf("\n=== All Optimal Routes ===\n\n");
    printf("%-20s %-20s %-15s\n", "Route", "Optimal Distance", "Direct Distance");
    printf("------------------------------------------------------------\n");

    int routeCount = 0;
    for (int i = 0; i < cityCount; i++) {
        for (int j = i + 1; j < cityCount; j++) {
            if (i != j) {
                int path[MAX_CITIES];
                int optimalDist = findPath(i, j, path);
                int directDist = distances[i][j];

                if (optimalDist != INF) {
                    printf("%s -> %-12s %-15d", cities[i], cities[j], optimalDist);
                    if (directDist != -1) {
                        printf("%-15d", directDist);
                    } else {
                        printf("%-15s", "No Direct");
                    }
                    printf("\n");
                    routeCount++;
                }
            }
        }
    }

    if (routeCount == 0) {
        printf("No routes available. Add distances between cities first.\n");
    }
}

// --------- performance Reports -----------------
void reports(){

    char choice;
do{
    printf("\n\tmenu\n");
    printf(" a. Total Deliveries Completed\n");
    printf(" b. Total Distance Covered\n");
    printf(" c. Average Delivery Time\n");
    printf(" d. Total Revenue and profit\n");
    printf(" e. Longest and Shortest Routes Completed\n");
    printf(" f. Back to Main Menu\n\n");

        printf("Enter your choice (a-f): ");
        scanf(" %c", &choice);

        while (getchar() != '\n');

        switch (choice) {
            case 'a':
                totalDeliveriesCompleted();
                break;
            case 'b':
                totalDistanceCovered();
                break;
            case 'c':
                averageDeliveryTime();
                break;
            case 'd':
                totalRevenueAndProfit();
                break;
            case 'e':
                longestShortestRoutes();
                break;
            case 'f':
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    } while (choice != 'f');
}

void totalDeliveriesCompleted() {
    int completedCount = 0;
    int pendingCount = 0;

    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].completed) {
            completedCount++;
        } else {
            pendingCount++;
        }
    }

    printf("\n=== Total Deliveries Completed ===\n");
    printf("====================================\n");
    printf("Completed Deliveries: %d\n", completedCount);
    printf("Pending Deliveries:   %d\n", pendingCount);
    printf("Total Deliveries:     %d/%d\n", deliveryCount, MAX_DELIVERIES);
    printf("Completion Rate:      %.1f%%\n", deliveryCount > 0 ? (double)completedCount / deliveryCount * 100 : 0);
    printf("====================================\n");

    if (completedCount > 0) {
        printf("\nRecent Completed Deliveries:\n");
        printf("-----------------------------\n");
        int displayCount = 0;
        for (int i = deliveryCount - 1; i >= 0 && displayCount < 5; i--) {
            if (deliveries[i].completed) {
                printf("ID: %d | %s -> %s | %s\n",
                       deliveries[i].deliveryId,
                       cities[deliveries[i].sourceCity],
                       cities[deliveries[i].destinationCity],
                       deliveries[i].completionTime);
                displayCount++;
            }
        }
    }
}

void totalDistanceCovered() {
    double totalDistance = 0;
    int completedCount = 0;

    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].completed) {
            int distance = distances[deliveries[i].sourceCity][deliveries[i].destinationCity];
            totalDistance += distance;
            completedCount++;
        }
    }

    printf("\n=== Total Distance Covered ===\n");
    printf("================================\n");
    printf("Total Distance:    %.0f km\n", totalDistance);
    printf("Completed Trips:   %d\n", completedCount);

    if (completedCount > 0) {
        printf("Average per Trip:  %.1f km\n", totalDistance / completedCount);

        // Distance breakdown by vehicle type
        printf("\nDistance by Vehicle Type:\n");
        printf("--------------------------\n");
        double vanDistance = 0, truckDistance = 0, lorryDistance = 0;
        int vanCount = 0, truckCount = 0, lorryCount = 0;

        for (int i = 0; i < deliveryCount; i++) {
            if (deliveries[i].completed) {
                int distance = distances[deliveries[i].sourceCity][deliveries[i].destinationCity];
                switch (deliveries[i].vehicleType) {
                    case 0: vanDistance += distance; vanCount++; break;
                    case 1: truckDistance += distance; truckCount++; break;
                    case 2: lorryDistance += distance; lorryCount++; break;
                }
            }
        }

        if (vanCount > 0) printf("Van:   %.0f km (%d trips)\n", vanDistance, vanCount);
        if (truckCount > 0) printf("Truck: %.0f km (%d trips)\n", truckDistance, truckCount);
        if (lorryCount > 0) printf("Lorry: %.0f km (%d trips)\n", lorryDistance, lorryCount);
    }
    printf("================================\n");
}

void averageDeliveryTime() {
    double totalTime = 0;
    int completedCount = 0;
    double minTime = INF;
    double maxTime = 0;

    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].completed && deliveries[i].actualDeliveryTime > 0) {
            totalTime += deliveries[i].actualDeliveryTime;
            completedCount++;

            if (deliveries[i].actualDeliveryTime < minTime) {
                minTime = deliveries[i].actualDeliveryTime;
            }
            if (deliveries[i].actualDeliveryTime > maxTime) {
                maxTime = deliveries[i].actualDeliveryTime;
            }
        }
    }

    printf("\n=== Average Delivery Time ===\n");
    printf("===============================\n");

    if (completedCount > 0) {
        printf("Average Time:      %.1f hours\n", totalTime / completedCount);
        printf("Fastest Delivery:  %.1f hours\n", minTime);
        printf("Slowest Delivery:  %.1f hours\n", maxTime);
        printf("Total Samples:     %d deliveries\n", completedCount);

        printf("\nEfficiency Analysis:\n");
        printf("--------------------\n");
        int onTime = 0, delayed = 0;

        for (int i = 0; i < deliveryCount; i++) {
            if (deliveries[i].completed && deliveries[i].actualDeliveryTime > 0) {
                double estimatedTime = calculations[i].estimatedTime;
                if (estimatedTime > 0) {
                    if (deliveries[i].actualDeliveryTime <= estimatedTime * 1.1) {
                        onTime++;
                    } else {
                        delayed++;
                    }
                }
            }
        }

        printf("On-time Deliveries: %d (%.1f%%)\n", onTime, (double)onTime / completedCount * 100);
        printf("Delayed Deliveries: %d (%.1f%%)\n", delayed, (double)delayed / completedCount * 100);
    } else {
        printf("No delivery time data available.\n");
        printf("Mark deliveries as completed with actual time data.\n");
    }
    printf("===============================\n");
}

void totalRevenueAndProfit() {
    double totalRevenue = 0;
    double totalProfit = 0;
    double totalCost = 0;
    int completedCount = 0;

    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].completed && calculations[i].customerCharge > 0) {
            totalRevenue += calculations[i].customerCharge;
            totalProfit += calculations[i].profit;
            totalCost += calculations[i].totalOperationalCost;
            completedCount++;
        }
    }

    printf("\n=== Total Revenue and Profit ===\n");
    printf("==================================\n");
    printf("Total Revenue:    LKR %.2f\n", totalRevenue);
    printf("Total Profit:     LKR %.2f\n", totalProfit);
    printf("Total Costs:      LKR %.2f\n", totalCost);

    if (completedCount > 0) {
        printf("Completed Orders: %d\n", completedCount);
        printf("Avg Revenue/Order:LKR %.2f\n", totalRevenue / completedCount);
        printf("Avg Profit/Order: LKR %.2f\n", totalProfit / completedCount);
        printf("Profit Margin:    %.1f%%\n", totalRevenue > 0 ? (totalProfit / totalRevenue) * 100 : 0);
    }
    printf("==================================\n");

    if (completedCount > 0) {
        printf("\nRevenue by Vehicle Type:\n");
        printf("-------------------------\n");
        double vanRevenue = 0, truckRevenue = 0, lorryRevenue = 0;

        for (int i = 0; i < deliveryCount; i++) {
            if (deliveries[i].completed && calculations[i].customerCharge > 0) {
                switch (deliveries[i].vehicleType) {
                    case 0: vanRevenue += calculations[i].customerCharge; break;
                    case 1: truckRevenue += calculations[i].customerCharge; break;
                    case 2: lorryRevenue += calculations[i].customerCharge; break;
                }
            }
        }

        if (vanRevenue > 0) printf("Van:   LKR %.2f\n", vanRevenue);
        if (truckRevenue > 0) printf("Truck: LKR %.2f\n", truckRevenue);
        if (lorryRevenue > 0) printf("Lorry: LKR %.2f\n", lorryRevenue);
    }
}

void longestShortestRoutes() {
    int longestDistance = 0;
    int shortestDistance = INF;
    int longestId = -1;
    int shortestId = -1;
    int completedCount = 0;

    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].completed) {
            completedCount++;
            int distance = distances[deliveries[i].sourceCity][deliveries[i].destinationCity];

            if (distance > longestDistance) {
                longestDistance = distance;
                longestId = i;
            }
            if (distance < shortestDistance) {
                shortestDistance = distance;
                shortestId = i;
            }
        }
    }

    printf("\n=== Longest and Shortest Routes ===\n");
    printf("=====================================\n");

    if (completedCount > 0) {
        printf("Longest Route:  %d km\n", longestDistance);
        if (longestId != -1) {
            printf("  Delivery ID:  %d\n", deliveries[longestId].deliveryId);
            printf("  Route:        %s => %s\n",
                   cities[deliveries[longestId].sourceCity],
                   cities[deliveries[longestId].destinationCity]);
            printf("  Vehicle:      %s\n", vehicles[deliveries[longestId].vehicleType].type);
        }

        printf("\nShortest Route: %d km\n", shortestDistance);
        if (shortestId != -1) {
            printf("  Delivery ID:  %d\n", deliveries[shortestId].deliveryId);
            printf("  Route:        %s => %s\n",
                   cities[deliveries[shortestId].sourceCity],
                   cities[deliveries[shortestId].destinationCity]);
            printf("  Vehicle:      %s\n", vehicles[deliveries[shortestId].vehicleType].type);
        }

        printf("\nRoute Statistics:\n");
        printf("------------------\n");
        int totalDistance = 0;
        for (int i = 0; i < deliveryCount; i++) {
            if (deliveries[i].completed) {
                totalDistance += distances[deliveries[i].sourceCity][deliveries[i].destinationCity];
            }
        }
        printf("Average Route:   %.1f km\n", (double)totalDistance / completedCount);
        printf("Total Routes:    %d completed\n", completedCount);
    } else {
        printf("No completed routes to analyze.\n");
    }
    printf("=====================================\n");
}

void markDeliveryCompleted() {
    if (deliveryCount == 0) {
        printf("No deliveries available to mark as completed.\n");
        return;
    }

    int deliveryId;
    char completionTime[20];
    double actualTime;

    printf("\nPending deliveries:\n");
    viewPendingDeliveries();

    printf("\nEnter delivery ID to mark as completed: ");
    scanf("%d", &deliveryId);

    while (getchar() != '\n');

    int foundIndex = -1;
    for (int i = 0; i < deliveryCount; i++) {
        if (deliveries[i].deliveryId == deliveryId && !deliveries[i].completed) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Error: Delivery ID not found or already completed!\n");
        return;
    }

    printf("Enter completion time (e.g: 2025-10-22 17:30): ");
    fgets(completionTime, 20, stdin);
    completionTime[strcspn(completionTime, "\n")] = 0;

    printf("Enter actual delivery time taken (hours): ");
    scanf("%lf", &actualTime);

    while (getchar() != '\n');

    deliveries[foundIndex].completed = 1;
    strcpy(deliveries[foundIndex].completionTime, completionTime);
    deliveries[foundIndex].actualDeliveryTime = actualTime;

    printf("\nDelivery ID %d marked as completed!\n", deliveryId);
    printf("Route: %s -> %s\n",
           cities[deliveries[foundIndex].sourceCity],
           cities[deliveries[foundIndex].destinationCity]);
    printf("Completed at: %s\n", completionTime);
    printf("Actual time: %.1f hours\n", actualTime);
}


