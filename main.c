#include <stdio.h>
#include <stdbool.h>

#define MAX_PARKING_SPACES 10
#define BILLING_RATE 100
#define MAX_PARKING_DURATION 10
#define FINE_RATE 150

// Payment status constants
#define UNPAID 0
#define PAID 1

void initializeParkingSpaces(bool parkingSpaces[], int paymentStatus[], int durations[], int size);
int findAvailableSpace(bool parkingSpaces[], int size);
void parkCar(bool parkingSpaces[], int paymentStatus[], int space, int durations[]);
void leaveParkingSpace(bool parkingSpaces[], int paymentStatus[], int space, int durations[]);
void displayParkingStatus(bool parkingSpaces[], int paymentStatus[], int durations[], int size);
bool isSpaceOccupied(bool parkingSpaces[], int space);
int calculateFine(int duration);

// New functions for parking space drawing
void drawParkingSpaces(int size, int durations[]);

int main() {
    bool parkingSpaces[MAX_PARKING_SPACES];
    int paymentStatus[MAX_PARKING_SPACES];
    int durations[MAX_PARKING_SPACES];
    int option, availableSpace, parkedCarSpace, duration, totalBill, fine, payment;

    // Initialize parking spaces, payment status, and durations
    initializeParkingSpaces(parkingSpaces, paymentStatus, durations, MAX_PARKING_SPACES);

    do {
        // Display menu
        printf("\nSmart Parking System\n");
        printf("1. Park Car\n");
        printf("2. Leave Parking Space\n");
        printf("3. Display Parking Status\n");
        printf("4. Check Slot Availability\n");
        printf("5. Generate Bill\n");
        printf("6. Pay Bill\n");
        printf("7. Calculate Fine\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                // Park Car
                availableSpace = findAvailableSpace(parkingSpaces, MAX_PARKING_SPACES);
                if (availableSpace != -1) {
                    printf("Enter parking duration (in hours): ");
                    scanf("%d", &duration);
                    parkCar(parkingSpaces, paymentStatus, availableSpace, durations); // Fix variable name
                    printf("Car parked at space %d for %d hours.\n", availableSpace, duration);
                } else {
                    printf("No available parking spaces.\n");
                }
                break;
                case 2:
                // Leave Parking Space
                printf("Enter the parking space to leave: ");
                scanf("%d", &parkedCarSpace);
                if (isSpaceOccupied(parkingSpaces, parkedCarSpace)) {
                    printf("Enter the total time parked (in hours): ");
                    scanf("%d", &duration);

                    // Check if the total time exceeds the allowed duration
                    if (duration > MAX_PARKING_DURATION) {
                        fine = calculateFine(duration);
                        printf("Fine for overstaying at space %d: Rs. %d\n", parkedCarSpace, fine);
                        // Move the car to the dormitory if the time exceeds 10 hours
                        if (duration > 10) {
                            printf("Car has been moved to the dormitory.\n");
                        }
                    }

                    leaveParkingSpace(parkingSpaces, paymentStatus, parkedCarSpace, durations);
                    printf("Car at space %d left the parking lot.\n", parkedCarSpace);
                } else {
                    printf("Invalid parking space or space is already empty.\n");
                }
                break;
                case 3:
                // Display Parking Status
                drawParkingSpaces(MAX_PARKING_SPACES, durations); // Draw parking spaces
                displayParkingStatus(parkingSpaces, paymentStatus, durations, MAX_PARKING_SPACES); // Display details
                break;
                case 4:
                // Check Slot Availability
                availableSpace = findAvailableSpace(parkingSpaces, MAX_PARKING_SPACES);
                if (availableSpace != -1) {
                    printf("Space %d is available.\n", availableSpace);
                } else {
                    printf("No available parking spaces.\n");
                }
                break;
                case 5:
                // Generate Bill
                printf("Enter the parking space to generate bill: ");
                scanf("%d", &parkedCarSpace);
                if (isSpaceOccupied(parkingSpaces, parkedCarSpace)) {
                    duration = durations[parkedCarSpace];
                    
                    // Debug statements
                    printf("Debug: Duration = %d\n", duration);
                    printf("Debug: Billing Rate = %d\n", BILLING_RATE);
                    
                    totalBill = duration * BILLING_RATE;
                    printf("Bill for parking at space %d: Rs. %d\n", parkedCarSpace, totalBill);
                    paymentStatus[parkedCarSpace] = UNPAID; // Set payment status to unpaid
                } else {
                    printf("Invalid parking space or space is empty.\n");
                }
                break;
                case 6:
                // Pay Bill
                printf("Enter the parking space to pay bill: ");
                scanf("%d", &parkedCarSpace);
                if (isSpaceOccupied(parkingSpaces, parkedCarSpace) && paymentStatus[parkedCarSpace] == UNPAID) {
                    printf("Enter the amount to pay: Rs. ");
                    scanf("%d", &payment);
                    if (payment >= totalBill) {
                        printf("Payment successful. Thank you!\n");
                        paymentStatus[parkedCarSpace] = PAID; // Set payment status to paid
                    } else {
                        printf("Insufficient payment. Please pay the full amount.\n");
                    }
                } else {
                    printf("Invalid parking space, space is empty, or bill is already paid.\n");
                }
                break;

            case 7:
                // Calculate Fine
                printf("Enter the parking space to calculate fine: ");
                scanf("%d", &parkedCarSpace);
                if (isSpaceOccupied(parkingSpaces, parkedCarSpace)) {
                    duration = durations[parkedCarSpace];
                    fine = calculateFine(duration);
                    printf("Fine for overstaying at space %d: Rs. %d\n", parkedCarSpace, fine);
                } else {
                    printf("Invalid parking space or space is empty.\n");
                }
                break;

            case 8:
                // Exit
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (option != 8);

    return 0;
}
// Initialize parking spaces, payment status, and durations
void initializeParkingSpaces(bool parkingSpaces[], int paymentStatus[], int durations[], int size) {
    for (int i = 0; i < size; i++) {
        parkingSpaces[i] = false; // false represents an empty space
        paymentStatus[i] = PAID; // initialize payment status to paid
        durations[i] = 0; // initialize parking durations to 0
    }
}
// Find the first available parking space
int findAvailableSpace(bool parkingSpaces[], int size) {
    for (int i = 0; i < size; i++) {
        if (!parkingSpaces[i]) {
            return i; // Return the index of the first available space
        }
    }
    return -1; // Return -1 if no space is available
}
// Park a car in the specified parking space
void parkCar(bool parkingSpaces[], int paymentStatus[], int space, int durations[]) {
    parkingSpaces[space] = true; // true represents a parked car
    durations[space]++; // increment parking duration
    paymentStatus[space] = UNPAID; // set payment status to unpaid
}
void leaveParkingSpace(bool parkingSpaces[], int paymentStatus[], int space, int durations[]) {
    parkingSpaces[space] = false; // false represents an empty space
    // Assuming the car leaves immediately after user input
    durations[space] = 0; // reset parking duration
    paymentStatus[space] = PAID; // set payment status to paid
}
void displayParkingStatus(bool parkingSpaces[], int paymentStatus[], int durations[], int size) {
    printf("Parking Status:\n");

    for (int i = 0; i < size; i++) {
        printf("Space %d: %s (Duration: %d hours, Payment: %s)\n", i,
               parkingSpaces[i] ? "Occupied" : "Empty",
               durations[i],
               paymentStatus[i] == UNPAID ? "Unpaid" : "Paid");

        // Check if the bill is unpaid and the car has been parked for more than 10 hours
        if (paymentStatus[i] == UNPAID && durations[i] > MAX_PARKING_DURATION) {
            printf("Car in space %d has not paid the bill and has been moved to the dormitory.\n", i);
        }
    }
}

// New function for drawing parking spaces
void drawParkingSpaces(int size, int durations[]) {
    printf("Parking Spaces:\n");

    for (int i = 0; i < size; i++) {
        printf("+---");
    }

    printf("+\n");

    for (int i = 0; i < size; i++) {
        if (durations[i] > 0) {
            printf("|[%c]", 'A' + i); // Use 'A', 'B', 'C', ... for different cars
        } else {
            printf("|[ ]");
        }
    }

    printf("|\n");

    for (int i = 0; i < size; i++) {
        printf("+---");
    }

    printf("+\n");
}
// Check if a parking space is occupied
bool isSpaceOccupied(bool parkingSpaces[], int space) {
    return parkingSpaces[space];
}

// Calculate fine for overstaying cars
int calculateFine(int duration) {
    int fine = 0;
    if (duration > MAX_PARKING_DURATION) {
        fine = (duration - MAX_PARKING_DURATION) * FINE_RATE;
    }
    return fine;
}
