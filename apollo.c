#include <stdio.h>
#include <string.h>

#define MAX_APPOINTMENTS 100
#define MAX_MEDICINES 100
#define MAX_LAB_TESTS 100
#define MAX_INSURANCES 5
#define MAX_USERS 100

struct User {
    char username[50];
    char password[50];
};

struct Appointment {
    int id;
    char doctor_name[50];
    char date[20];
    char time[10];
};

struct Medicine {
    int id;
    char name[50];
    int quantity;
};

struct LabTest {
    int id;
    char test_name[50];
    char date[20];
};

struct Insurance {
    int id;
    char name[50];
    char coverage[100];
};

struct Appointment appointments[MAX_APPOINTMENTS];
struct Medicine medicines[MAX_MEDICINES];
struct LabTest lab_tests[MAX_LAB_TESTS];
struct Insurance insurances[MAX_INSURANCES];
struct User users[MAX_USERS];

int appointment_count = 0;
int medicine_count = 0;
int lab_test_count = 0;
int user_count = 0;
int logged_in_user_index = -1;

void initialize_insurances() {
    struct Insurance insurance1 = {1, "HealthPlus", "Comprehensive health coverage with low deductibles."};
    struct Insurance insurance2 = {2, "CareMax", "Affordable health coverage with a wide network of providers."};
    struct Insurance insurance3 = {3, "FamilyCare", "Family health plans with pediatric coverage."};
    struct Insurance insurance4 = {4, "SeniorHealth", "Specialized plans for seniors with additional benefits."};
    struct Insurance insurance5 = {5, "StudentCare", "Health insurance tailored for students."};

    insurances[0] = insurance1;
    insurances[1] = insurance2;
    insurances[2] = insurance3;
    insurances[3] = insurance4;
    insurances[4] = insurance5;
}

void signup() {
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    struct User new_user;
    printf("Enter username: ");
    scanf(" %[^\n]", new_user.username);
    printf("Enter password: ");
    scanf(" %[^\n]", new_user.password);

    // Check if username already exists
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, new_user.username) == 0) {
            printf("Username already exists. Please choose a different username.\n");
            return;
        }
    }

    users[user_count] = new_user;
    user_count++;
    printf("Signup successful! You can now log in.\n");
}

int login() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf(" %[^\n]", username);
    printf("Enter password: ");
    scanf(" %[^\n]", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user_index = i;
            printf("Login successful! Welcome, %s.\n", username);
            return 1; // Login successful
        }
    }

    printf("Invalid username or password. Please try again.\n");
    return 0; // Login failed
}

void book_appointment() {
    if (appointment_count >= MAX_APPOINTMENTS) {
        printf("Maximum number of appointments reached.\n");
        return;
    }

    struct Appointment appointment;
    appointment.id = appointment_count + 1;
    printf("Enter doctor's name: ");
    scanf(" %[^\n]", appointment.doctor_name);
    printf("Enter appointment date (YYYY-MM-DD): ");
    scanf("%s", appointment.date);
    printf("Enter appointment time (HH:MM): ");
    scanf("%s", appointment.time);

    appointments[appointment_count] = appointment;
    appointment_count++;

    printf("Appointment booked with Dr. %s on %s at %s (ID: %d).\n",
           appointment.doctor_name, appointment.date, appointment.time, appointment.id);
}

void view_appointments() {
    if (appointment_count == 0) {
        printf("No appointments found.\n");
        return;
    }

    printf("Existing Appointments:\n");
    for (int i = 0; i < appointment_count; i++) {
        printf("ID: %d, Doctor: %s, Date: %s, Time: %s\n",
               appointments[i].id, appointments[i].doctor_name, appointments[i].date, appointments[i].time);
    }
}

void buy_medicine() {
    if (medicine_count >= MAX_MEDICINES) {
        printf("Maximum number of medicines reached.\n");
        return;
    }

    struct Medicine medicine;
    medicine.id = medicine_count + 1;

    printf("Enter medicine name: ");
    scanf(" %[^\n]", medicine.name);
    printf("Enter quantity: ");
    scanf("%d", &medicine.quantity);

    medicines[medicine_count] = medicine;
    medicine_count++;

    printf("You have purchased %d of %s (ID: %d).\n", medicine.quantity, medicine.name, medicine.id);
}

void lab_test() {
    if (lab_test_count >= MAX_LAB_TESTS) {
        printf("Maximum number of lab tests reached.\n");
        return;
    }

    struct LabTest lab_test;
    lab_test.id = lab_test_count + 1;
    printf("Enter lab test name: ");
    scanf(" %[^\n]", lab_test.test_name);  
    printf("Enter test date (YYYY-MM-DD): ");
    scanf("%s", lab_test.date);

    lab_tests[lab_test_count] = lab_test;
    lab_test_count++;

    printf("Lab test '%s' scheduled on %s (ID: %d).\n", lab_test.test_name, lab_test.date, lab_test.id);
}

void insurance_info() {
    printf("Available Insurance Plans:\n");
    for (int i = 0; i < MAX_INSURANCES; i++) {
        printf("ID: %d, Name: %s, Coverage: %s\n",
               insurances[i].id, insurances[i].name, insurances[i].coverage);
    }
}

void select_insurance() {
    int choice;
    printf("Select an insurance plan by entering the corresponding ID:\n");
    insurance_info();

    printf("Enter your choice (1-%d): ", MAX_INSURANCES);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= MAX_INSURANCES) {
        printf("You have selected the insurance plan: %s\n", insurances[choice - 1].name);
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}

void about_us() {
    printf("About Us:\n");
    printf("We provide a range of healthcare services including telemedicine, lab tests, and medicine delivery.\n");
    printf("Our mission is to make healthcare accessible and convenient for everyone.\n");
}

void main_menu() {
    int choice;

    while (1) {
        printf("\n--- Apollo 24/7  ---\n");
        printf("1. Doctor Appointment\n");
        printf("2. Buy Medicine\n");
        printf("3. Lab Test\n");
        printf("4. Insurance\n");
        printf("5. About Us\n");
        printf("6. Exit\n");
        printf("Please select an option (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Doctor Appointment ---\n");
                printf("1. Book Appointment\n");
                printf("2. View Appointments\n");
                printf("3. Go Back\n");
                printf("Please select an option: ");
                int appointment_choice;
                scanf("%d", &appointment_choice);
                if (appointment_choice == 1) {
                    book_appointment();
                } else if (appointment_choice == 2) {
                    view_appointments();
                }
                break;
            case 2:
                buy_medicine();
                break;
            case 3:
                lab_test();
                break;
            case 4:
                select_insurance();
                break;
            case 5:
                about_us();
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    initialize_insurances();

    while (1) {
        printf("\n--- Welcome to Apollo 24/7 ---\n");
        printf("1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Please select an option (1-3): ");
        int option;
        scanf("%d", &option);

        if (option == 1) {
            signup();
        } else if (option == 2) {
            if (login()) {
                main_menu(); // Access the main menu after successful login
            }
        } else if (option == 3) {
            printf("Exiting the program. Goodbye!\n");
            return 0;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
