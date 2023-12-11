#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent an appointment
struct Appointment {
    int serial_number;
    char name[100];
    char phone_number[12];
    int hour;
    int minute;
    struct Appointment* next; // Pointer to the next appointment in the linked list
};

struct Appointment* head = NULL; // Global variable to store the head of the linked list
int appointment_limit = 20; // Maximum number of appointments allowed for the day

// Function to display appointments sorted by time in ascending order
void displayAppointments() {
    printf("\nToday's Appointments\n");

    if (head == NULL) {
        printf("No appointments scheduled for today.\n");
        return;
    }

    // Sort appointments by time using insertion sort
    struct Appointment* sorted_head = NULL;
    struct Appointment* temp = head;

    while (temp != NULL) {
        struct Appointment* next = (*temp).next;
        struct Appointment* current = sorted_head;
        struct Appointment* previous = NULL;

        // Find the correct position to insert the current appointment in sorted order
        while (current != NULL && ((*current).hour < (*temp).hour || ((*current).hour == (*temp).hour && (*current).minute <= (*temp).minute))) {
            previous = current;
            current = (*current).next;
        }

        // Insert the current appointment into the sorted list
        if (previous == NULL) {
            (*temp).next = sorted_head;
            sorted_head = temp;
        } else {
            (*previous).next = temp;
            (*temp).next = current;
        }

        temp = next;
    }

    // Display sorted appointments
    temp = sorted_head;
    while (temp != NULL) {
        printf("Serial Number: %d\n", (*temp).serial_number);
        printf("Patient's Name: %s\n", (*temp).name);
        printf("Phone Number: %s\n", (*temp).phone_number);
        printf("Time: %02d:%02d\n", (*temp).hour, (*temp).minute);
        printf("----------------------------------------\n");

        temp = (*temp).next;
    }

    // Free the memory allocated for the sorted list
    while (sorted_head != NULL) {
        struct Appointment* next = (*sorted_head).next;
        free(sorted_head);
        sorted_head = next;
    }
}

// Function to display the serial number of a scheduled appointment
void displaySerialNumber(int serial_number) {
    printf("Appointment scheduled successfully! Your Serial Number is: %d\n", serial_number);
}

// Function to check if a given time slot is available
int timeAvailability(int hour, int minute);

// Function to schedule a new appointment
void scheduleAppointment() {
    if (appointment_limit == 0) {
        printf("Sorry! Today's appointments are full. Try again tomorrow.\n");
        return;
    }

    // Allocate memory for a new appointment
    struct Appointment* newAppointment = (struct Appointment*)malloc(sizeof(struct Appointment));
    (*newAppointment).next = NULL;

    // Get patient's name and phone number
    printf("Enter your name: ");
    fgets((*newAppointment).name, sizeof((*newAppointment).name), stdin);
    strtok((*newAppointment).name, "\n");

    printf("Enter your phone number: ");
    fgets((*newAppointment).phone_number, sizeof((*newAppointment).phone_number), stdin);
    strtok((*newAppointment).phone_number, "\n");

    do {
        // Get patient's preferred time
        printf("Enter your preferred time (HH:MM): ");
        scanf("%d:%d", &(*newAppointment).hour, &(*newAppointment).minute);

        // Consume the newline character left in the buffer
        getchar();

        // Check if the entered time is between 9 a.m. and 7 p.m.
        if ((*newAppointment).hour < 9 || (*newAppointment).hour > 19 || (*newAppointment).minute < 0 || (*newAppointment).minute > 59) {
            printf("Please choose a valid time between 9 a.m. and 7 p.m.\n");
        } else if (!timeAvailability((*newAppointment).hour, (*newAppointment).minute)) {
            printf("Sorry, the chosen time is not available. Please choose another time.\n");
        } else {
            break;
        }
    } while (1);

    // Assign a serial number to the new appointment
    (*newAppointment).serial_number = 20 - appointment_limit + 1;
    appointment_limit--;

    // Insert the new appointment into the linked list
    if (head == NULL) {
        head = newAppointment;
    } else {
        struct Appointment* temp = head;
        while ((*temp).next != NULL) {
            temp = (*temp).next;
        }
        (*temp).next = newAppointment;
    }

    // Display the serial number of the scheduled appointment
    displaySerialNumber((*newAppointment).serial_number);
}

// Function to check if a given time slot is available
int timeAvailability(int hour, int minute) {
    struct Appointment* temp = head;

    // Iterate through existing appointments to check for conflicts
    while (temp != NULL) {
        if ((*temp).hour == hour && (*temp).minute == minute) {
            return 0; // Time slot not available
        }
        temp = (*temp).next;
    }

    return 1; // Time slot available
}

// Function to remove a scheduled appointment
void removeAppointment(int serial_number) {
    struct Appointment* current = head;
    struct Appointment* previous = NULL;

    // Find the appointment with the specified serial number
    while (current != NULL && (*current).serial_number != serial_number) {
        previous = current;
        current = (*current).next;
    }

    if (current == NULL) {
        printf("Appointment with Serial Number %d not found.\n", serial_number);
        return;
    }

    // Remove the appointment from the linked list
    if (previous == NULL) {
        // If the appointment to be removed is the head
        head = (*current).next;
    } else {
        // If the appointment to be removed is not the head
        (*previous).next = (*current).next;
    }

    free(current); // Free the memory allocated for the removed appointment
    printf("Appointment with Serial Number %d removed successfully.\n", serial_number);
}

// Function to display the menu for patients
void displayPatientMenu() {
    printf("\nPatient's Menu\n");
    printf("1. Schedule an Appointment\n");
    printf("2. Remove an Appointment\n");
    printf("3. Back to the main menu\n");
}

// Function to display the menu for doctors
void displayDoctorMenu() {
    printf("\nDoctor's Menu\n");
    printf("1. View Appointments\n");
    printf("2. Back to the main menu\n");
}

// Main function
int main() {
    char choice;

    while (1) {
        // Display the main menu
        printf("\nMAIN MENU\n");
        printf("A. I'm a Patient\n");
        printf("B. I'm the Doctor\n");
        printf("C. Exit\n");

        printf("Enter your choice (A/B/C): ");
        scanf(" %c", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 'A':
                // Patient menu
                while (1) {
                    displayPatientMenu();
                    printf("Enter your choice: ");
                    scanf(" %c", &choice);
                    getchar(); // Consume newline

                    switch (choice) {
                        case '1':
                            scheduleAppointment();
                            break;
                        case '2':
                            printf("Enter the Serial Number of the appointment to remove: ");
                            int serial_number;
                            scanf("%d", &serial_number);
                            getchar(); // Consume newline
                            removeAppointment(serial_number);
                            break;
                        case '3':
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }

                    if (choice == '3') {
                        break;
                    }
                }
                break;

            case 'B':
                // Doctor menu
                while (1) {
                    displayDoctorMenu();
                    printf("Enter your choice: ");
                    scanf(" %c", &choice);
                    getchar(); // Consume newline

                    switch (choice) {
                        case '1':
                            displayAppointments();
                            break;
                        case '2':
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }

                    if (choice == '2') {
                        break;
                    }
                }
                break;

            case 'C':
                printf("Exiting program.\n");
                exit(0); // Exit the program
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Appointment {
    int serial_number;
    char name[100];
    char phone_number[12];
    int hour;
    int minute;  
    struct Appointment* next;
};

struct Appointment* head = NULL;
int appointment_limit = 20;

void displayAppointments() {
    printf("\nToday's Appointments\n");

    if (head == NULL) {
        printf("No appointments scheduled for today.\n");
        return;
    }

    struct Appointment* sorted_head = NULL;
    struct Appointment* temp = head;

    while (temp != NULL) {
        struct Appointment* next = (*temp).next;
        struct Appointment* current = sorted_head;
        struct Appointment* previous = NULL;

        while (current != NULL && ((*current).hour < (*temp).hour || ((*current).hour == (*temp).hour && (*current).minute <= (*temp).minute))) {
            previous = current;
            current = (*current).next;
        }

        if (previous == NULL) {
            (*temp).next = sorted_head;
            sorted_head = temp;
        } else {
            (*previous).next = temp;
            (*temp).next = current;
        }

        temp = next;
    }

    temp = sorted_head;
    while (temp != NULL) {
        printf("Serial Number: %d\n", (*temp).serial_number);
        printf("Patient's Name: %s\n", (*temp).name);
        printf("Phone Number: %s\n", (*temp).phone_number);
        printf("Time: %02d:%02d\n", (*temp).hour, (*temp).minute); 
        printf("----------------------------------------\n");

        temp = (*temp).next;
    }

    while (sorted_head != NULL) {
        struct Appointment* next = (*sorted_head).next;
        free(sorted_head);
        sorted_head = next;
    }
}


void displaySerialNumber(int serial_number) {
    printf("Appointment scheduled successfully! Your Serial Number is: %d\n", serial_number);
}

int timeAvailability(int hour, int minute);

void scheduleAppointment() {
    if (appointment_limit == 0) {
        printf("Sorry! Today's appointments are full. Try again tomorrow.\n");
        return;
    }

    struct Appointment* newAppointment = (struct Appointment*)malloc(sizeof(struct Appointment));
    (*newAppointment).next = NULL;

    printf("Enter your name: ");
    fgets((*newAppointment).name, sizeof((*newAppointment).name), stdin);
    strtok((*newAppointment).name, "\n");

    printf("Enter your phone number: ");
    fgets((*newAppointment).phone_number, sizeof((*newAppointment).phone_number), stdin);
    strtok((*newAppointment).phone_number, "\n");

    do {
        printf("Enter your preferred time (HH:MM): ");
        scanf("%d:%d", &(*newAppointment).hour, &(*newAppointment).minute);

        getchar();

        if ((*newAppointment).hour < 9 || (*newAppointment).hour > 19 || (*newAppointment).minute < 0 || (*newAppointment).minute > 59) {
            printf("Please choose a valid time between 9 a.m. and 7 p.m.\n");
        } else if (!timeAvailability((*newAppointment).hour, (*newAppointment).minute)) {
            printf("Sorry, the chosen time is not available. Please choose another time.\n");
        } else {
            break;
        }
    } while (1);

    (*newAppointment).serial_number = 20 - appointment_limit + 1;
    appointment_limit--;

    if (head == NULL) {
        head = newAppointment;
    } else {
        struct Appointment* temp = head;
        while ((*temp).next != NULL) {
            temp = (*temp).next;
        }
        (*temp).next = newAppointment;
    }

    displaySerialNumber((*newAppointment).serial_number);
}

int timeAvailability(int hour, int minute) {
    struct Appointment* temp = head;

    while (temp != NULL) {
        if ((*temp).hour == hour && (*temp).minute == minute) {
            return 0;
        }
        temp = (*temp).next;
    }

    return 1;
}

void removeAppointment(int serial_number) {
    struct Appointment* current = head;
    struct Appointment* previous = NULL;

    while (current != NULL && (*current).serial_number != serial_number) {
        previous = current;
        current = (*current).next;
    }

    if (current == NULL) {
        printf("Appointment with Serial Number %d not found.\n", serial_number);
        return;
    }

    if (previous == NULL) {
        head = (*current).next;
    } else {
        (*previous).next = (*current).next;
    }

    free(current);
    printf("Appointment with Serial Number %d removed successfully.\n", serial_number);
}

void displayPatientMenu() {
    printf("\nPatient's Menu\n");
    printf("1. Schedule an Appointment\n");
    printf("2. Remove an Appointment\n");
    printf("3. Back to main menu\n");
}

void displayDoctorMenu() {
    printf("\nDoctor's Menu\n");
    printf("1. View Appointments\n");
    printf("2. Back to main menu\n");
}

int main() {
    char choice;

    while (1) {
        printf("\nMAIN MENU\n");
        printf("A. I'm a Patient\n");
        printf("B. I'm the Doctor\n");
        printf("C. Exit\n");

        printf("Enter your choice (A/B/C): ");
        scanf(" %c", &choice);
        getchar(); 

        switch (choice) {
            case 'A':
                while (1) {
                    displayPatientMenu();
                    printf("Enter your choice: ");
                    scanf(" %c", &choice);
                    getchar(); 

                    switch (choice) {
                        case '1':
                            scheduleAppointment();
                            break;
                        case '2':
                            printf("Enter the Serial Number of the appointment to remove: ");
                            int serial_number;
                            scanf("%d", &serial_number);
                            getchar(); 
                            removeAppointment(serial_number);
                            break;
                        case '3':
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }

                    if (choice == '3') {
                        break;
                    }
                }
                break;

            case 'B':
                while (1) {
                    displayDoctorMenu();
                    printf("Enter your choice: ");
                    scanf(" %c", &choice);
                    getchar(); 

                    switch (choice) {
                        case '1':
                            displayAppointments();
                            break;
                        case '2':
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }

                    if (choice == '2') {
                        break;
                    }
                }
                break;

            case 'C':
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

