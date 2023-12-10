# Appointment-System
This C program allows patients to schedule appointments and doctors to view and manage appointments.

## Features

- **Patient's Menu:**
  - Schedule an Appointment
  - Remove an Appointment
  - Back to the main menu

- **Doctor's Menu:**
  - View Appointments
  - Back to the main menu

## How to Compile and Run

1. Open a terminal window.
2. Navigate to the project directory.

```bash
gcc -o AppointmentSystem main.c
./AppointmentSystem
```

## Patient's Menu

### 1. Schedule an Appointment

Patients can schedule appointments by providing their name, phone number, and preferred time. The system assigns a unique serial number to each appointment.

### 2. Remove an Appointment

Patients can remove an appointment by entering the serial number assigned during scheduling.

### 3. Back to the main menu

Return to the main menu for the choice between being a patient or a doctor.

## Doctor's Menu

### 1. View Appointments

Doctors can view the appointments sorted by time. The system handles scheduling conflicts and ensures appointment availability.

### 2. Back to the main menu

Return to the main menu for the choice between being a patient or a doctor.

## Exiting the Program

Choose 'C' to exit the program gracefully.

## Appointment Limit

There is a daily limit of 20 appointments. Once the limit is reached, patients are informed to try again the next day.

## Author

Edita Matevosyan
