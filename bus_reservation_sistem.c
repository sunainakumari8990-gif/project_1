#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

char reg_name[30];
char reg_email[40];
char reg_password[20];
char reg_mobile[11];

int booked_seats[4]={0,0,0,0};
struct Bus
{
    int bus_number;
    char source[20];
    char destination[20];
    int total_seats;
    int available_seats;
    int fare;
};

struct Bus buses[4] = {
    {101, "Delhi", "Bihar", 50, 50, 500},
    {102, "Patna", "Kolkata", 40, 40, 600},
    {103, "Lucknow", "Delhi", 45, 45, 550},
    {104, "Ranchi", "Patna", 30, 30, 450}
};

int valid_name(char name[])
{
    for (int i = 0; name[i] != '\0'; i++)
        if (!(isalpha(name[i]) || name[i] == ' '))
            return 0;
    return 1;
}

int valid_mobile(char mobile[])
{
    if (strlen(mobile) != 10)
        return 0;

    int all_zero = 1;
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(mobile[i]))
            return 0;
        if (mobile[i] != '0')
            all_zero = 0;
    }
    if (all_zero)
        return 0;

    return 1;
}

int valid_email(char email[])
{
    int i = 0;

    if (!(email[i] >= 'a' && email[i] <= 'z') &&
        !(email[i] >= 'A' && email[i] <= 'Z'))
        return 0;

    while ((email[i] >= 'a' && email[i] <= 'z') ||
           (email[i] >= 'A' && email[i] <= 'Z'))
    {
        i++;
    }

    int digit_count = 0;
    while (email[i] >= '0' && email[i] <= '9')
    {
        digit_count++;
        i++;
    }

    if (digit_count == 0)
        return 0;

    if (strcmp(&email[i], "@gmail.com") == 0)
        return 1;

    return 0;
}
int valid_password(char password[])
{
    int length = strlen(password);
    return (length >= 8 && length <= 15);
}

void registration()
{
    printf(YELLOW "\n--- REGISTRATION ---\n" RESET);

    do {
        printf("Enter full name: ");
        scanf(" %[^\n]", reg_name);
        if (!valid_name(reg_name))
            printf(RED "Invalid name! Only alphabets allowed\n" RESET);
    } while (!valid_name(reg_name));

    do {
        printf("Enter mobile number: ");
        scanf("%s", reg_mobile);
        if (!valid_mobile(reg_mobile))
            printf(RED "Invalid mobile number!\n" RESET);
    } while (!valid_mobile(reg_mobile));

    do {
        printf("Enter email: ");
        scanf("%s", reg_email);
        if (!valid_email(reg_email))
            printf(RED "Invalid email format!\n" RESET);
    } while (!valid_email(reg_email));

    do {
        printf("Enter password (8 - 15 chars): ");
        scanf("%s", reg_password);
        if (!valid_password(reg_password))
            printf(RED "Password must be 8 - 15 characters!\n" RESET);
    } while (!valid_password(reg_password));

    printf(GREEN "\nRegistration Successful!\n" RESET);
}

int login()
{
    char email[40], password[20];

    printf(YELLOW "\n--- LOGIN ---\n" RESET);
    printf("\nvarify your email & password.");
    printf("\nEnter email: ");
    scanf("%s", email);

    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(email, reg_email) != 0)
    {
        printf(RED "Email not matched!\n" RESET);
        return 0;
    }

    if (strcmp(password, reg_password) != 0)
    {
        printf(RED "Password not matched!\n" RESET);
        return 0;
    }

    printf(GREEN "\nLogin Successful! Welcome %s\n" RESET, reg_name);
    return 1;
}

int find_bus(int bus_number)
{
    for (int i = 0; i < 4; i++)
        if (buses[i].bus_number == bus_number)
            return i;
    return -1;
}

void menu()
{
    int choice;

    while (1)
    {
        printf(YELLOW "\n==== USER MENU ====\n" RESET);
        printf(YELLOW "1. Book Ticket\n" RESET);
        printf(YELLOW "2. Cancel Ticket\n" RESET);
        printf(YELLOW "3. Bus Status\n" RESET);
        printf(YELLOW "4. Logout\n" RESET);
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {


            int bus_number, seats;
            printf("Enter bus number: ");
            scanf("%d", &bus_number);

            int i = find_bus(bus_number);
            if (i == -1)
            {
                printf(RED "Invalid bus number!\n" RESET);
                continue;
            }

            printf("Enter seats: ");
            scanf("%d", &seats);

            if (seats > buses[i].available_seats)
                printf(RED "Not enough seats!\n" RESET);
            else
            {
                buses[i].available_seats -= seats;
                booked_seats[i] += seats;

                printf(GREEN "Booking successful! %d seats booked on bus number %d\n" RESET ,seats,bus_number);
                printf("Total amount = Rs %d\n", seats * buses[i].fare);
            }
        }

else if (choice == 2)
{
    int bus_number, seats;
    printf("Enter bus number: ");
    scanf("%d", &bus_number);

    int i = find_bus(bus_number);
    if (i == -1)
    {
        printf(RED "Invalid bus number!\n" RESET);
        continue;
    }

    printf("Enter seats to cancel: ");
    scanf("%d", &seats);

    if (seats > booked_seats[i])
    {
        printf(RED "Error: Itni seats book hi nahi hui!\n" RESET);
    }
    else
    {
        buses[i].available_seats += seats;
        booked_seats[i] -= seats;

        printf(GREEN "Cancellation successful! %d seats canceled on bus number %d\n" RESET,
               seats, bus_number);
    }
}

        else if (choice == 3)
        {
            int bus_number;
            printf("Enter bus number: \n");
            scanf("%d", &bus_number);

            int i = find_bus(bus_number);
            if (i == -1)
            {
                printf(RED "Invalid bus number!\n" RESET);
                continue;
            }

            printf(YELLOW "\n--- BUS STATUS ---\n" RESET);
            printf(BLUE "Bus No: %d\n" RESET, buses[i].bus_number);
            printf(BLUE "Route: %s to %s\n" RESET, buses[i].source, buses[i].destination);
            printf(BLUE "Total Seats: %d\n" RESET, buses[i].total_seats);
            printf(BLUE "Available Seats: %d\n" RESET, buses[i].available_seats);
            printf(BLUE "Fare: Rs.%d\n" RESET, buses[i].fare);
        }

        else if (choice == 4)
        {
            printf(GREEN "Logout successful!\n" RESET);
            break;
        }
        else
            printf(RED "Invalid choice!\n" RESET);
    }
}

int main()
{
    int choice;
registration();

    while (1)
    {
        printf(YELLOW "\n**** BUS RESERVATION SYSTEM ****\n" RESET);
        
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
            
         if (choice == 1)
        {
            if (login())
                menu();
        }
        else if (choice == 2)
        {
            printf(GREEN "Thank you!\n" RESET);
            break;
        }
        else
            printf(RED "Invalid option!\n" RESET);
    }
    return 0;
}

