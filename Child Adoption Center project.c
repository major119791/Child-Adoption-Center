#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
#define MAX_USERS 100
#define MAX_CHILDREN 100

typedef struct {
    char firstName[50], lastName[50], email[100], password[50];
    char address[100], occupation[50], phone[15];
    int age;
} User;

typedef struct {
    char name[50], gender[10], birthDate[20];
    int age;
    float height, weight;
    int adopted;
} Child;

User users[MAX_USERS];
Child children[MAX_CHILDREN];
int userCount = 0, childCount = 0;

void menu() {
    int choice;
    do {
        printf("\n1. Adopt a Child\n2. View Children\n3. Return a Child\n4. Exit\nChoice: ");
        scanf("%d", &choice);
    } while (choice != 4);
}

void signUp() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    User newUser;
    printf("\nEnter First Name: "); 
    scanf(" %[^\n]", newUser.firstName);
    printf("Enter Last Name: "); 
    scanf(" %[^\n]", newUser.lastName);
    printf("Enter Age: "); 
    scanf("%d", &newUser.age);
    printf("Enter Address: "); 
    scanf(" %[^\n]", newUser.address);
    printf("Enter Occupation: "); 
    scanf(" %[^\n]", newUser.occupation);
    printf("Enter Phone: "); 
    scanf("%s", newUser.phone);
    printf("Enter Email: "); 
    scanf("%s", newUser.email);
    printf("Enter Password: "); 
    scanf("%s", newUser.password);

    users[userCount++] = newUser;
    printf("\nAccount Created Successfully!\n");
}

int login() {
    char email[100], pass[50];
    printf("\nEnter Email: "); 
    scanf("%s", email);
    printf("Enter Password: "); 
    scanf("%s", pass);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, pass) == 0) {
            printf("\nLogin Successful! Welcome, %s %s!\n", users[i].firstName, users[i].lastName);
            return 1;
        }
    }
    printf("\nInvalid credentials.\n");
    return 0;
}

//admin

void addChild() {
    if (childCount >= MAX_CHILDREN) {
        printf("Child profile limit reached.\n");
        return;
    }

    Child newChild;
    printf("\nEnter Child's Name: ");
    scanf(" %[^\n]", newChild.name);
    printf("Enter Age: ");
    scanf("%d", &newChild.age);
    printf("Enter Gender: ");
    scanf("%s", newChild.gender);
    printf("Enter Birth Date (YYYY-MM-DD): ");
    scanf("%s", newChild.birthDate);
    printf("Enter Height (cm): ");
    scanf("%f", &newChild.height);
    printf("Enter Weight (kg): ");
    scanf("%f", &newChild.weight);
    
    newChild.adopted = 0;
    children[childCount++] = newChild;
    printf("\nChild profile created successfully!\n");
}

void deleteChild() {
    char name[50];
    printf("\nEnter the name of the child to delete: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < childCount; i++) {
        if (strcmp(children[i].name, name) == 0) {
            for (int j = i; j < childCount - 1; j++) {
                children[j] = children[j + 1];
            }
            childCount--;
            printf("\nChild profile deleted successfully!\n");
            return;
        }
    }
    printf("\nChild not found.\n");
}

void viewChildren() {
    int i;
    printf("\n========================================\n");
    printf("            CHILD PROFILES             ");
    printf("\n========================================\n");

    if (childCount == 0) {
        printf("\nNo child profiles available.\n");
        return;
    }

    for (i = 0; i < childCount; i++) {
        printf("\n----------------------------------------\n");
        printf(" Name        : %s\n", children[i].name);
        printf(" Age         : %d years\n", children[i].age);
        printf(" Gender      : %s\n", children[i].gender);
        printf(" Birth Date  : %s\n", children[i].birthDate);
        printf(" Height      : %.2f cm\n", children[i].height);
        printf(" Weight      : %.2f kg\n", children[i].weight);
        printf(" Status      : %s\n", children[i].adopted ? "Adopted" : "Available");
        printf("----------------------------------------\n");
    }
}

void viewAdoptedChildren() {
    
}

void viewUsers() {
    int i;
    printf("\n========================================\n");
    printf("        REGISTERED USERS (PARENTS)      ");
    printf("\n========================================\n");

    if (userCount == 0) {
        printf("\nNo registered users available.\n");
        return;
    }

    for (i = 0; i < userCount; i++) {
        printf("\n----------------------------------------\n");
        printf(" Name       : %s %s\n", users[i].firstName, users[i].lastName);
        printf(" Age        : %d years\n", users[i].age);
        printf(" Email      : %s\n", users[i].email);
        printf(" Occupation : %s\n", users[i].occupation);
        printf(" Phone      : %s\n", users[i].phone);
        printf(" Address    : %s\n", users[i].address);
        printf("----------------------------------------\n");
    }
}

void adminMenu() {
    int choice;
    do {
        printf("\n====== Admin Menu ======\n");
        printf("1. Add Child Profile\n2. Delete Child Profile\n3. View All Children\n4. View Adopted Children\n5. View Registered Users\n6. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
            addChild(); 
            break;
            case 2: 
            deleteChild(); 
            break;
            case 3: 
            viewChildren(); 
            break;
            case 4: 
            viewAdoptedChildren(); 
            break;
            case 5: 
            viewUsers(); 
            break;
        }
    } while (choice != 6);
}

void adminLogin() {
    char pass[20];
    printf("\nEnter Admin Password: ");
    scanf("%s", pass);

    if (strcmp(pass, "admin123") == 0) {
        printf("\nAdmin Login Successful!\n");
        adminMenu();
    } else {
        printf("\nIncorrect Password.\n");
    }
}



void userLogin() {
    int choice;
    printf("====== Welcome to Adoption Center ======\n\n");

    do {
        printf("\n1. Login\n2. Register\n3. Admin\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (login()) menu();
                break;
            case 2:
                signUp();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                printf("\nExiting... Thank you for visiting the Adoption Center!\n");
                break;
            default:
                printf("\nInvalid choice!.\n");
        }
    } while (choice != 4);
}
//

int main() {
    userLogin();
    return 0;
}
