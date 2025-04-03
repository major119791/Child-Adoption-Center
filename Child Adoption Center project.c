#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 100
#define MAX_CHILDREN 100

typedef struct {
    char firstName[50], lastName[50], email[100], password[50];
    char address[100], occupation[50], phone[15];
    int age;
} User;
typedef struct {
    char id[8], name[50], gender[10], birthDate[20];
    int age;
    float height, weight;
    int adopted;
    char bloodType[5];
    char allergies[100];
    char medicalConditions[200];
    char educationLevel[50];
    char hobbies[100];
    char languagesSpoken[100];
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
	User user;
	FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Users.txt", "a");
    if (!file) {
        printf("Error opening user file.\n");
        return;
    }
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }
    printf("========= Registration =========\n");
    printf("\nEnter First Name: ");
    scanf(" %[^\n]", user.firstName);
    printf("Enter Last Name: ");
    scanf(" %[^\n]", user.lastName);
    printf("Enter Email: ");
    scanf(" %s", user.email);
    printf("Enter Password: ");
    scanf(" %s", user.password);
    printf("Enter Age: ");
    scanf(" %d", &user.age);
    printf("Enter Address: ");
    scanf(" %[^\n]", user.address);
    printf("Enter Occupation: ");
    scanf(" %[^\n]", user.occupation);
    printf("Enter Phone Number: ");
    scanf(" %s", user.phone);

    fprintf(file, "=================================\n");
    fprintf(file, "First Name   : %s\n", user.firstName);
    fprintf(file, "Last Name    : %s\n", user.lastName);
    fprintf(file, "Email        : %s\n", user.email);
    fprintf(file, "Password     : %s\n", user.password);
    fprintf(file, "Age          : %d\n", user.age);
    fprintf(file, "Address      : %s\n", user.address);
    fprintf(file, "Occupation   : %s\n", user.occupation);
    fprintf(file, "Phone        : %s\n", user.phone);
    fprintf(file, "=================================\n\n");

    fclose(file);
    printf("\nAccount Created Successfully!\n");
}
int login() {
	int i;
    char email[100], pass[50];
    printf("\nEnter Email: "); 
    scanf("%s", email);
    printf("Enter Password: "); 
    scanf("%s", pass);
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, pass) == 0) {
            printf("\nLogin Successful! Welcome, %s %s!\n", users[i].firstName, users[i].lastName);
            return 1;
        }
    }
    printf("\nInvalid credentials.\n");
    return 0;
}
	void generateChildID(char id[], char gender) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int i;
    id[0] = gender; 
    for (i = 1; i < 7; i++) {
        id[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    id[7] = '\0'; 
}
void addChild() {
    Child child;
	FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Children.txt", "a");
    if (!file) {
        printf("Error opening child file.\n");
        return;
    }
    if (childCount >= MAX_CHILDREN) {
        printf("Child profile limit reached.\n");
        return;
    }
    printf("Enter Child Name: ");
    scanf(" %[^\n]", child.name);
    printf("Enter Age: ");
    scanf(" %d", &child.age);
    printf("Enter Gender (M/F): ");
    scanf(" %s", child.gender);
    printf("Enter Birth Date (YYYY-MM-DD): ");
    scanf(" %s", child.birthDate);
    printf("Enter Height (cm): ");
    scanf(" %f", &child.height);
    printf("Enter Weight (kg): ");
    scanf(" %f", &child.weight);
    printf("Enter Blood Type: ");
    scanf(" %s", child.bloodType);
    printf("Enter Allergies (if any): ");
    scanf(" %[^\n]", child.allergies);
    printf("Enter Medical Conditions (if any): ");
    scanf(" %[^\n]", child.medicalConditions);
    printf("Enter Education Level: ");
    scanf(" %[^\n]", child.educationLevel);
    printf("Enter Hobbies & Interests: ");
    scanf(" %[^\n]", child.hobbies);
    printf("Enter Languages Spoken: ");
    scanf(" %[^\n]", child.languagesSpoken);
    child.adopted = 0;
    generateChildID(child.id, child.gender[0]);

    fprintf(file, "=================================\n");
    fprintf(file, "Child ID     : %s\n", child.id);
    fprintf(file, "Name         : %s\n", child.name);
    fprintf(file, "Age          : %d\n", child.age);
    fprintf(file, "Gender       : %s\n", child.gender);
    fprintf(file, "Birth Date   : %s\n", child.birthDate);
    fprintf(file, "Height       : %.2f cm\n", child.height);
    fprintf(file, "Weight       : %.2f kg\n", child.weight);
    fprintf(file, "Blood Type   : %s\n", child.bloodType);
    fprintf(file, "Allergies    : %s\n", child.allergies);
    fprintf(file, "Medical Conditions : %s\n", child.medicalConditions);
    fprintf(file, "Education Level    : %s\n", child.educationLevel);
    fprintf(file, "Hobbies & Interests : %s\n", child.hobbies);
    fprintf(file, "Languages Spoken : %s\n", child.languagesSpoken);
    fprintf(file, "Status       : %s\n", child.adopted ? "Adopted" : "Available");
    fprintf(file, "=================================\n\n");

    fclose(file);
    printf("\nChild profile created successfully!\n");
}
void deleteChild() {
	int i, j;
    char name[50];
    printf("\nEnter the name of the child to delete: ");
    scanf(" %[^\n]", name);
    for (i = 0; i < childCount; i++) {
        if (strcmp(children[i].name, name) == 0) {
            for (j = i; j < childCount - 1; j++) {
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
    printf("====== Welcome to Adoption Center ======\n");
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
void loadUsers() {
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Users.txt", "r");
    if (!file) {
        printf("? No user data found. Starting fresh.\n");
        return;
    }

    userCount = 0;
    while (fscanf(file, "=================================\n") != EOF) {
        fscanf(file, "First Name   : %[^\n]\n", users[userCount].firstName);
        fscanf(file, "Last Name    : %[^\n]\n", users[userCount].lastName);
        fscanf(file, "Email        : %s\n", users[userCount].email);
        fscanf(file, "Password     : %s\n", users[userCount].password);
        fscanf(file, "Age          : %d\n", &users[userCount].age);
        fscanf(file, "Address      : %[^\n]\n", users[userCount].address);
        fscanf(file, "Occupation   : %[^\n]\n", users[userCount].occupation);
        fscanf(file, "Phone        : %s\n", users[userCount].phone);
        fscanf(file, "=================================\n\n");

        userCount++;
        if (userCount >= MAX_USERS) break; 
    }

    fclose(file);
}
int main() {
    userLogin();
    return 0;
}
