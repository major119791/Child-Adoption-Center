#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  
#include <time.h>     
#define MAX_USERS 100
#define MAX_CHILDREN 100

typedef struct {
    char email[100];
    char password[50];
} Login;

typedef struct {
	Login login;  
    char email[100];
    char firstName[50];
    char lastName[50];
    int age;
    char address[100];
    char occupation[50];
    char phone[15];
    char maritalStatus[20];
    int householdSize;
    char criminalRecord[10];     
    char housingStatus[10];     
    char hasChildren[10];       
    char reason[200];           
    char status[20];            
} User;

typedef struct {
    char id[8];                   
    char name[50];
    char gender[10];
    char birthDate[20];
    int age;
    float height;
    float weight;
    int adopted;                 
    char bloodType[5];
    char allergies[100];
    char medicalConditions[200];
    char educationLevel[50];
    char hobbies[100];
    char languagesSpoken[100];
} Child;

char currentUserEmail[100];
Login logins[MAX_USERS];
User users[MAX_USERS];
Child children[MAX_CHILDREN];
int loginCount = 0;
int userCount = 0;
int childCount = 0;
void clearScreen();
void menu();
void adminMenu();
void viewAdoptedChildren();
void viewUsers();
void addChild();
void deleteChild();
void viewChildren();  
void adoptChild();

void clearScreen() {
    system("cls");  
}

void menu() {
    int choice;
    do {
        printf("\n======== Adoption Section ========\n");
        printf("1. Adopt a Child\n");
        printf("2. View Children\n");
        printf("3. Submit Application\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clearScreen();

        switch (choice) {
            case 1:
                if (hasSubmittedApplication(currentUserEmail)) {
                    
                    if (isApplicationApproved(currentUserEmail)) {
                        adoptChild();
                    } else {
                        printf("Your application is still pending approval by the admin.\n");
                        printf("Please wait for the admin's approval before adopting.\n");
                    }
                } else {
                    printf("You must submit an application before adopting.\n");
                }
                break;
            case 2:
                viewChildren();
                break;
            case 3:
                submitApplication(currentUserEmail);
                break;
            case 4:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice.\n");
        }
    } while (choice != 4);
}

void signUp() {
    Login login;
    FILE *file;

    while (1) {
        printf("========= Create Account =========\n");
        printf("Enter Email (press 0 to go back): ");
        scanf(" %s", login.email);

        if (strcmp(login.email, "0") == 0) {
            printf("\nReturning to main menu...\n");
            Sleep(1500);  
            clearScreen();
            return;
        }

        printf("Enter Password: ");
        scanf(" %s", login.password);

		file = fopen("C:\\Users\\L65X15W07\\Desktop\\Credentials.txt", "a");
        if (!file) {
            printf("Error: Could not open credentials file.\n");
            return;
        }

        fprintf(file, "==================\n");
        fprintf(file, "Email: %s\n", login.email);
        fprintf(file, "Password: %s\n", login.password);
        fprintf(file, "==================\n\n");
        fclose(file);

        printf("\nAccount Created Successfully!\n");
        Sleep(1500);  
        clearScreen(); 
        return; 
    }
}

int hasSubmittedApplication(const char *email) {
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Applications.txt", "r");
    char line[300];
    if (!file) return 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Email")) {
            char storedEmail[100];
            sscanf(line, "Email : %s", storedEmail);
            if (strcmp(storedEmail, email) == 0) {
                fclose(file);
                return 1; 
            }
        }
    }

    fclose(file);
    return 0; 
}

int isApplicationApproved(const char *email) {
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Applications.txt", "r");
    if (!file) {
        printf("Error: Could not open application file.\n");
        return 0;  
    }

    char line[256];
    User temp;
    int foundUser = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
       
        if (strcmp(line, "=================================\n") == 0) {
          
            temp.email[0] = '\0';
            temp.status[0] = '\0';

            
            while (fgets(line, sizeof(line), file) != NULL && strcmp(line, "=================================\n") != 0) {
                if (strstr(line, "Email") != NULL) {
                    sscanf(line, "Email              : %[^\n]", temp.email);
                } else if (strstr(line, "Status") != NULL) {
                    sscanf(line, "Status             : %[^\n]", temp.status);
                }
            }

          
            if (strcmp(temp.email, email) == 0) {
                fclose(file);
                
                return strcasecmp(temp.status, "Approved") == 0 ? 1 : 0;
            }
        }
    }

    fclose(file);
    return 0;
}

void submitApplication(const char *email) {
    User user;
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Applications.txt", "a");
    if (!file) {
        printf("Error: Could not open application file.\n");
        return;
    }

    strcpy(user.email, email);
    printf("\n========= Adoption Application Form (press 0 to go back) =========\n");

    while (1) {
        printf("Enter First Name: ");
        scanf(" %[^\n]", user.firstName);
        if (strcmp(user.firstName, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.firstName[0] != '\0') break;
    }
    while (1) {
        printf("Enter Last Name: ");
        scanf(" %[^\n]", user.lastName);
        if (strcmp(user.lastName, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.lastName[0] != '\0') break;
    }
    while (1) {
        printf("Enter Age: ");
        if (scanf("%d", &user.age) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Try again.\n");
            continue;
        }
        if (user.age == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.age > 0) break;
        printf("Age must be positive.\n");
    }
    while (getchar() != '\n'); 
    
    while (1) {
        printf("Enter Address: ");
        scanf(" %[^\n]", user.address);
        if (strcmp(user.address, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.address[0] != '\0') break;
    }
    while (1) {
        printf("Enter Occupation: ");
        scanf(" %[^\n]", user.occupation);
        if (strcmp(user.occupation, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.occupation[0] != '\0') break;
    }
    while (1) {
        printf("Enter Phone Number: ");
        scanf(" %[^\n]", user.phone);
        if (strcmp(user.phone, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.phone[0] != '\0') break;
    }
    while (1) {
        printf("Enter Marital Status (Single/Married): ");
        scanf(" %[^\n]", user.maritalStatus);
        if (strcmp(user.maritalStatus, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.maritalStatus[0] != '\0') break;
    }

    while (1) {
        printf("Enter Number of Household Members: ");
        if (scanf("%d", &user.householdSize) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Try again.\n");
            continue;
        }
        if (user.householdSize == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.householdSize > 0) break;
        printf("Must be greater than 0.\n");
    }
    while (getchar() != '\n');

    while (1) {
        printf("Do you have any criminal record? (Yes/No): ");
        scanf(" %[^\n]", user.criminalRecord);
        if (strcmp(user.criminalRecord, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.criminalRecord[0] != '\0') break;
    }

    while (1) {
        printf("Do you own or rent your home? (Own/Rent): ");
        scanf(" %[^\n]", user.housingStatus);
        if (strcmp(user.housingStatus, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.housingStatus[0] != '\0') break;
    }

    while (1) {
        printf("Do you currently have children? (Yes/No): ");
        scanf(" %[^\n]", user.hasChildren);
        if (strcmp(user.hasChildren, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.hasChildren[0] != '\0') break;
    }

    while (1) {
        printf("Why do you want to adopt a child?\n-> ");
        scanf(" %[^\n]", user.reason);
        if (strcmp(user.reason, "0") == 0) {
            printf("Returning to menu...\n");
            Sleep(1000);
            clearScreen();
            fclose(file);
            return;
        }
        if (user.reason[0] != '\0') break;
    }

    strcpy(user.status, "Pending");

    fprintf(file, "=================================\n");
    fprintf(file, "Email              : %s\n", user.email);
	fprintf(file, "First Name         : %s\n", user.firstName);
	fprintf(file, "Last Name          : %s\n", user.lastName);
    fprintf(file, "Age                : %d\n", user.age);
    fprintf(file, "Address            : %s\n", user.address);
    fprintf(file, "Occupation         : %s\n", user.occupation);
    fprintf(file, "Phone              : %s\n", user.phone);
    fprintf(file, "Marital Status     : %s\n", user.maritalStatus);
    fprintf(file, "Household Size     : %d\n", user.householdSize);
    fprintf(file, "Criminal Record    : %s\n", user.criminalRecord);
    fprintf(file, "Housing Status     : %s\n", user.housingStatus);
    fprintf(file, "Has Children       : %s\n", user.hasChildren);
    fprintf(file, "Reason for Adopting: %s\n", user.reason);
    fprintf(file, "Status             : %s\n", user.status);
    fprintf(file, "=================================\n\n");

    fclose(file);

    printf("\nApplication Submitted for Review!\n");
    Sleep(1500);
    clearScreen();
}

void userLogin() {
    char email[100], password[100], line[200];
    int i, loginSuccess = 0;

    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Credentials.txt", "r");
    if (!file) {
        printf("Error: Could not open credentials file.\n");
        return;
    }

  
    loginCount = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Email:")) {
            sscanf(line, "Email: %s", logins[loginCount].email);
        } else if (strstr(line, "Password:")) {
            sscanf(line, "Password: %s", logins[loginCount].password);
            loginCount++;
        }
    }
    fclose(file);

    printf("\n====== User Login ======\n");
    printf("Enter Email (press 0 to go back): ");
    scanf("%s", email);
    if (strcmp(email, "0") == 0) {
        printf("Returning to main menu...\n");
        Sleep(1000);
        clearScreen();
        return;
    }

    printf("Enter Password (press 0 to go back): ");
    scanf("%s", password);
    if (strcmp(password, "0") == 0) {
        printf("Returning to main menu...\n");
        Sleep(1000);
        clearScreen();
        return;
    }

    clearScreen();

    for (i = 0; i < loginCount; i++) {
        if (strcmp(logins[i].email, email) == 0 && strcmp(logins[i].password, password) == 0) {
            loginSuccess = 1;
            break;
        }
    }

    if (loginSuccess) {
    	strcpy(currentUserEmail, email);
        printf("Login Successful! Welcome.\n");
        Sleep(1500);
        clearScreen();
        menu();  
    } else {
        printf("Invalid Email or Password. Please try again.\n");
        Sleep(1500);
        clearScreen();
    }
}

void generateChildID(char id[], char gender) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int i;
    int idExists = 1;

    
    while (idExists) {
        id[0] = gender;  
        
        
        for (i = 1; i < 7; i++) {
            id[i] = charset[rand() % (sizeof(charset) - 1)];
        }
        id[7] = '\0';  

        
        idExists = 0;  
        for (i = 0; i < childCount; i++) {
            if (strcmp(children[i].id, id) == 0) {
                idExists = 1;  
                break;
            }
        }
    }
}

void addChild() {
    Child child;
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Childrens.txt", "a");
    if (!file) {
        printf("Error opening child file.\n");
        return;
    }

    if (childCount >= MAX_CHILDREN) {
        printf("Child profile limit reached.\n");
        fclose(file);
        return;
    }

    printf("\n=== Press 0 to go back =====================\n");

    printf("Enter Child Name: ");
    scanf(" %[^\n]", child.name);
    if (strcmp(child.name, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    printf("Enter Age: ");
    char tempAge[10];
    scanf(" %s", tempAge);
    if (strcmp(tempAge, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }
    child.age = atoi(tempAge);
    while (child.age <= 0) {
        printf("Invalid age. Please enter a valid age: ");
        scanf("%d", &child.age);
    }

    printf("Enter Gender (M/F): ");
    scanf(" %s", child.gender);
    if (strcmp(child.gender, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }
    while (child.gender[0] != 'M' && child.gender[0] != 'F') {
        printf("Invalid gender. Please enter M or F: ");
        scanf(" %s", child.gender);
    }

    printf("Enter Birth Date (YYYY-MM-DD): ");
    scanf(" %[^\n]", child.birthDate);
    if (strcmp(child.birthDate, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    printf("Enter Height (cm): ");
    char tempHeight[10];
    scanf(" %s", tempHeight);
    if (strcmp(tempHeight, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }
    child.height = atof(tempHeight);
    while (child.height <= 0) {
        printf("Invalid height. Please enter a valid height: ");
        scanf("%f", &child.height);
    }

    printf("Enter Weight (kg): ");
    char tempWeight[10];
    scanf(" %s", tempWeight);
    if (strcmp(tempWeight, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }
    child.weight = atof(tempWeight);
    while (child.weight <= 0) {
        printf("Invalid weight. Please enter a valid weight: ");
        scanf("%f", &child.weight);
    }

    printf("Enter Blood Type: ");
    scanf(" %s", child.bloodType);
    if (strcmp(child.bloodType, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    printf("Enter Allergies: ");
    scanf(" %[^\n]", child.allergies);
    if (strcmp(child.allergies, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    printf("Enter Medical Conditions: ");
    scanf(" %[^\n]", child.medicalConditions);
    if (strcmp(child.medicalConditions, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    printf("Enter Education Level: ");
    scanf(" %[^\n]", child.educationLevel);
    if (strcmp(child.educationLevel, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    printf("Enter Hobbies & Interests: ");
    scanf(" %[^\n]", child.hobbies);
    if (strcmp(child.hobbies, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    printf("Enter Languages Spoken: ");
    scanf(" %[^\n]", child.languagesSpoken);
    if (strcmp(child.languagesSpoken, "0") == 0) {
        printf("\nReturning to admin menu...\n");
        Sleep(1500);
        clearScreen();
        fclose(file);
        return;
    }

    child.adopted = 0;
    generateChildID(child.id, child.gender[0]);

    fprintf(file, "=================================\n");
    fprintf(file, "Child ID           : %s\n", child.id);
    fprintf(file, "Name               : %s\n", child.name);
    fprintf(file, "Age                : %d\n", child.age);
    fprintf(file, "Gender             : %s\n", child.gender);
    fprintf(file, "Birth Date         : %s\n", child.birthDate);
    fprintf(file, "Height             : %.2f cm\n", child.height);
    fprintf(file, "Weight             : %.2f kg\n", child.weight);
    fprintf(file, "Blood Type         : %s\n", child.bloodType);
    fprintf(file, "Allergies          : %s\n", child.allergies);
    fprintf(file, "Medical Conditions : %s\n", child.medicalConditions);
    fprintf(file, "Education Level    : %s\n", child.educationLevel);
    fprintf(file, "Hobbies            : %s\n", child.hobbies);
    fprintf(file, "Languages Spoken   : %s\n", child.languagesSpoken);
    fprintf(file, "Status             : %s\n", child.adopted ? "Adopted" : "Available");
    fprintf(file, "=================================\n\n");

    fclose(file);

    printf("\nChild profile created successfully!\n");
    childCount++;
    Sleep(1500);
    clearScreen();
}

void loadChildren() {
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Childrens.txt", "r");
    if (!file) {
        printf("No child data found. Starting fresh.\n");
        return;
    }

    while (!feof(file) && childCount < MAX_CHILDREN) {
        char line[256];

        fgets(line, sizeof(line), file); 
        fgets(line, sizeof(line), file); sscanf(line, "Child ID     : %[^\n]", children[childCount].id);
        fgets(line, sizeof(line), file); sscanf(line, "Name         : %[^\n]", children[childCount].name);
        fgets(line, sizeof(line), file); sscanf(line, "Age          : %d", &children[childCount].age);
        fgets(line, sizeof(line), file); sscanf(line, "Gender       : %[^\n]", children[childCount].gender);
        fgets(line, sizeof(line), file); sscanf(line, "Birth Date   : %[^\n]", children[childCount].birthDate);
        fgets(line, sizeof(line), file); sscanf(line, "Height       : %f", &children[childCount].height);
        fgets(line, sizeof(line), file); sscanf(line, "Weight       : %f", &children[childCount].weight);
        fgets(line, sizeof(line), file); sscanf(line, "Blood Type   : %[^\n]", children[childCount].bloodType);
        fgets(line, sizeof(line), file); sscanf(line, "Allergies    : %[^\n]", children[childCount].allergies);
        fgets(line, sizeof(line), file); sscanf(line, "Medical Conditions : %[^\n]", children[childCount].medicalConditions);
        fgets(line, sizeof(line), file); sscanf(line, "Education Level    : %[^\n]", children[childCount].educationLevel);
        fgets(line, sizeof(line), file); sscanf(line, "Hobbies & Interests : %[^\n]", children[childCount].hobbies);
        fgets(line, sizeof(line), file); sscanf(line, "Languages Spoken : %[^\n]", children[childCount].languagesSpoken);
        
        fgets(line, sizeof(line), file);  
        if (strstr(line, "Adopted")) {
            children[childCount].adopted = 1;
        } else {
            children[childCount].adopted = 0;
        }

        fgets(line, sizeof(line), file); 
        fgets(line, sizeof(line), file); 

        childCount++;
    }

    fclose(file);
    printf("Child data loaded successfully. (%d profiles)\n", childCount);
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
    int validProfiles = 0;

    printf("\n========================================\n");
    printf("            CHILD PROFILES              \n");
    printf("========================================\n");

    for (i = 0; i < childCount; i++) {
        
        if (children[i].adopted == 1) {
            continue;
        }

        if (children[i].id[0] != '\0') {
            validProfiles++;
            printf("\n----------------------------------------\n");
            printf(" Child ID            : %s\n", children[i].id);
            printf(" Name                : %s\n", children[i].name);
            printf(" Age                 : %d years\n", children[i].age);
            printf(" Gender              : %s\n", children[i].gender);
            printf(" Birth Date          : %s\n", children[i].birthDate);
            printf(" Height              : %.2f cm\n", children[i].height);
            printf(" Weight              : %.2f kg\n", children[i].weight);
            printf(" Blood Type          : %s\n", children[i].bloodType);
            printf(" Allergies           : %s\n", children[i].allergies);
            printf(" Medical Conditions  : %s\n", children[i].medicalConditions);
            printf(" Education Level     : %s\n", children[i].educationLevel);
            printf(" Hobbies & Interests : %s\n", children[i].hobbies);
            printf(" Languages Spoken    : %s\n", children[i].languagesSpoken);
            printf(" Status              : %s\n", "Available");
            printf("----------------------------------------\n");
        }
    }

    if (validProfiles == 0) {
        printf("\nNo child profiles available.\n");
    }

    printf("\nPress any key to go back...\n");
    getchar();  
    getchar();  

    clearScreen();
    return;  
}

void viewAdoptedChildren() {
    int i;
    int validProfiles = 0;

    printf("\n========================================\n");
    printf("        ADOPTED CHILD PROFILES         \n");
    printf("========================================\n");

    for (i = 0; i < childCount; i++) {

        if (children[i].adopted == 1 && children[i].id[0] != '\0') {
            validProfiles++;
            printf("\n----------------------------------------\n");
            printf(" Child ID            : %s\n", children[i].id);
            printf(" Name                : %s\n", children[i].name);
            printf(" Age                 : %d years\n", children[i].age);
            printf(" Gender              : %s\n", children[i].gender);
            printf(" Birth Date          : %s\n", children[i].birthDate);
            printf(" Height              : %.2f cm\n", children[i].height);
            printf(" Weight              : %.2f kg\n", children[i].weight);
            printf(" Blood Type          : %s\n", children[i].bloodType);
            printf(" Allergies           : %s\n", children[i].allergies);
            printf(" Medical Conditions  : %s\n", children[i].medicalConditions);
            printf(" Education Level     : %s\n", children[i].educationLevel);
            printf(" Hobbies & Interests : %s\n", children[i].hobbies);
            printf(" Languages Spoken    : %s\n", children[i].languagesSpoken);
            printf(" Status              : %s\n", "Adopted");
            printf("----------------------------------------\n");
        }
    }

    if (validProfiles == 0) {
        printf("\nNo adopted child profiles available.\n");
    }

    printf("\nPress any key to go back...\n");
    getchar();  
    getchar();  

    clearScreen();
    return;
}

void displayChildDetails(Child child) {
    printf("\n=================================\n");
    printf("Child ID           : %s\n", child.id);
    printf("Name               : %s\n", child.name);
    printf("Age                : %d\n", child.age);
    printf("Gender             : %s\n", child.gender);
    printf("Birth Date         : %s\n", child.birthDate);
    printf("Height             : %.2f cm\n", child.height);
    printf("Weight             : %.2f kg\n", child.weight);
    printf("Blood Type         : %s\n", child.bloodType);
    printf("Allergies          : %s\n", child.allergies);
    printf("Medical Conditions : %s\n", child.medicalConditions);
    printf("Education Level    : %s\n", child.educationLevel);
    printf("Hobbies            : %s\n", child.hobbies);
    printf("Languages Spoken   : %s\n", child.languagesSpoken);
    printf("Status             : %s\n", child.adopted ? "Adopted" : "Available");
    printf("=================================\n");
}

void adoptChild(const char *userEmail) {
    FILE *childFile = fopen("C:\\Users\\L65X15W07\\Desktop\\Childrens.txt", "r+");
    if (!childFile) {
        printf("Error: Cannot open Childrens.txt\n");
        return;
    }

    Child children[100];
    int j, i, count = 0;
    char line[256];

   while (fgets(line, sizeof(line), childFile)) {
        if (strstr(line, "=================================")) {
            while (fgets(line, sizeof(line), childFile)) {
                if (strstr(line, "Child ID")) {
                    sscanf(line, "Child ID           : %s", children[count].id);
                } else if (strstr(line, "Name")) {
                    sscanf(line, "Name               : %[^\n]", children[count].name);
                } else if (strstr(line, "Age")) {
                    sscanf(line, "Age                : %d", &children[count].age);
                } else if (strstr(line, "Gender")) {
                    sscanf(line, "Gender             : %s", children[count].gender);
                } else if (strstr(line, "Birth Date")) {
                    sscanf(line, "Birth Date         : %[^\n]", children[count].birthDate);
                } else if (strstr(line, "Height")) {
                    sscanf(line, "Height             : %f cm", &children[count].height);
                } else if (strstr(line, "Weight")) {
                    sscanf(line, "Weight             : %f kg", &children[count].weight);
                } else if (strstr(line, "Blood Type")) {
                    sscanf(line, "Blood Type         : %s", children[count].bloodType);
                } else if (strstr(line, "Allergies")) {
                    sscanf(line, "Allergies          : %[^\n]", children[count].allergies);
                } else if (strstr(line, "Medical Conditions")) {
                    sscanf(line, "Medical Conditions : %[^\n]", children[count].medicalConditions);
                } else if (strstr(line, "Education Level")) {
                    sscanf(line, "Education Level    : %[^\n]", children[count].educationLevel);
                } else if (strstr(line, "Hobbies")) {
                    sscanf(line, "Hobbies            : %[^\n]", children[count].hobbies);
                } else if (strstr(line, "Languages Spoken")) {
                    sscanf(line, "Languages Spoken   : %[^\n]", children[count].languagesSpoken);
                } else if (strstr(line, "Status")) {
                    char status[20];
                    sscanf(line, "Status             : %s", status);
                    children[count].adopted = (strcmp(status, "Adopted") == 0);
                    count++;
                    if (count >= 100) {
                        printf("Warning: Maximum number of children reached (100).\n");
                        break;
                    }
                    break;
                }
            }
        }
    }
    fclose(childFile);

    if (count == 0) {
        printf("No children records found.\n");
        return;
    }

    int choice;
    char filter[20];

    while (1) {
        printf("\n--- Child Adoption Menu ---\n");
        printf("1. View all available children\n");
        printf("2. Filter by gender\n");
        printf("3. Filter by blood type\n");
        printf("4. Search by child ID\n");
        printf("5. Adopt a child by ID\n");
        printf("6. Go back\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }
        getchar(); 

        clearScreen();

        switch (choice) {
            case 1:
                for (i = 0; i < count; i++) {
                    if (!children[i].adopted)
                        displayChildDetails(children[i]);
                }
                break;

            case 2:
                printf("Enter gender (M/F): ");
                scanf("%s", filter);
                getchar();
                for (i = 0; i < count; i++) {
                    if (!children[i].adopted && strcasecmp(children[i].gender, filter) == 0)
                        displayChildDetails(children[i]);
                }
                break;

            case 3:
                printf("Enter blood type (A, B, AB, O): ");
                scanf("%s", filter);
                getchar();
                for (i = 0; i < count; i++) {
                    if (!children[i].adopted && strcasecmp(children[i].bloodType, filter) == 0)
                        displayChildDetails(children[i]);
                }
                break;

            case 4: {
                char searchID[20];
                printf("Enter Child ID: ");
                scanf("%s", searchID);
                getchar();

                int found = 0;
                for (i = 0; i < count; i++) {
                    if (strcmp(children[i].id, searchID) == 0) {
                        displayChildDetails(children[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    printf("No child found with ID %s\n", searchID);
                break;
            }

            case 5: {
                char chosenID[20];
                printf("Enter the ID of the child to adopt: ");
                scanf("%s", chosenID);
                getchar();

                int found = 0;
                for (i = 0; i < count; i++) {
                    if (strcmp(children[i].id, chosenID) == 0) {  
                        if (children[i].adopted) {  
                            printf("This child has already been adopted.\n");
                            found = 1;
                            break;
                        }

                        children[i].adopted = 1;
                        found = 1;

                        
                        FILE *adoptFile = fopen("C:\\Users\\L65X15W07\\Desktop\\Adoptions.txt", "a");
                        if (!adoptFile) {
                            printf("Error: Cannot open Adoptions.txt\n");
                            return;
                        }

                        fprintf(adoptFile, "=================================\n");
                        fprintf(adoptFile, "Parent Email      : %s\n", userEmail);
                        fprintf(adoptFile, "Child ID          : %s\n", children[i].id);
                        fprintf(adoptFile, "Child Name        : %s\n", children[i].name);
                        fprintf(adoptFile, "Adoption Date     : %s\n", __DATE__);
                        fprintf(adoptFile, "=================================\n\n");
                        fclose(adoptFile);

                     
                        childFile = fopen("C:\\Users\\L65X15W07\\Desktop\\Childrens.txt", "w");  
                        if (!childFile) {
                            printf("Error: Cannot rewrite Childrens.txt\n");
                            return;
                        }

                       
                        for (j = 0; j < count; j++) {
                            fprintf(childFile, "=================================\n");
                            fprintf(childFile, "Child ID           : %s\n", children[j].id);
                            fprintf(childFile, "Name               : %s\n", children[j].name);
                            fprintf(childFile, "Age                : %d\n", children[j].age);
                            fprintf(childFile, "Gender             : %s\n", children[j].gender);
                            fprintf(childFile, "Birth Date         : %s\n", children[j].birthDate);
                            fprintf(childFile, "Height             : %.2f cm\n", children[j].height);
                            fprintf(childFile, "Weight             : %.2f kg\n", children[j].weight);
                            fprintf(childFile, "Blood Type         : %s\n", children[j].bloodType);
                            fprintf(childFile, "Allergies          : %s\n", children[j].allergies);
                            fprintf(childFile, "Medical Conditions : %s\n", children[j].medicalConditions);
                            fprintf(childFile, "Education Level    : %s\n", children[j].educationLevel);
                            fprintf(childFile, "Hobbies            : %s\n", children[j].hobbies);
                            fprintf(childFile, "Languages Spoken   : %s\n", children[j].languagesSpoken);
                            fprintf(childFile, "Status             : %s\n", children[j].adopted ? "Adopted" : "Available");
                            fprintf(childFile, "=================================\n\n");
                        }
                        fclose(childFile);

                        printf("\nYou have successfully adopted %s!\n", children[i].name);
                        break;
                    }
                }

                if (!found) {
                    printf("Invalid ID or child already adopted.\n");
                }

                break;
            }

            case 6:
                return;

            default:
                printf("Invalid choice.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        clearScreen();
    }
}


void viewUsers() {
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Users.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open Users.txt\n");
        return;
    }

    char line[200];
    int userFound = 0;

    printf("\n========================================\n");
    printf("        REGISTERED USERS (PARENTS)      ");
    printf("\n========================================\n");

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "========================================")) {
            if (userFound) {
                printf("----------------------------------------\n");
            }
            userFound = 1;
        } else {
            printf("%s", line);
        }
    }

    if (!userFound) {
        printf("\nNo registered users available.\n");
    }

    fclose(file);
}
void adminReviewApplications() {
    int i = 0, j, choice;
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Applications.txt", "r");
    if (!file) {
        printf("Error: Could not open application file.\n");
        return;
    }

    User applications[100];
    int count = 0;
    char line[256];
    User temp;

    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, "=================================\n") != 0)
            continue;

        fgets(line, sizeof(line), file); sscanf(line, "Email              : %[^\n]", temp.email);
        fgets(line, sizeof(line), file); sscanf(line, "First Name         : %[^\n]", temp.firstName);
        fgets(line, sizeof(line), file); sscanf(line, "Last Name          : %[^\n]", temp.lastName);
        fgets(line, sizeof(line), file); sscanf(line, "Age                : %d", &temp.age);
        fgets(line, sizeof(line), file); sscanf(line, "Address            : %[^\n]", temp.address);
        fgets(line, sizeof(line), file); sscanf(line, "Occupation         : %[^\n]", temp.occupation);
        fgets(line, sizeof(line), file); sscanf(line, "Phone              : %[^\n]", temp.phone);
        fgets(line, sizeof(line), file); sscanf(line, "Marital Status     : %[^\n]", temp.maritalStatus);
        fgets(line, sizeof(line), file); sscanf(line, "Household Size     : %d", &temp.householdSize);
        fgets(line, sizeof(line), file); sscanf(line, "Criminal Record    : %[^\n]", temp.criminalRecord);
        fgets(line, sizeof(line), file); sscanf(line, "Housing Status     : %[^\n]", temp.housingStatus);
        fgets(line, sizeof(line), file); sscanf(line, "Has Children       : %[^\n]", temp.hasChildren);
        fgets(line, sizeof(line), file); sscanf(line, "Reason for Adopting: %[^\n]", temp.reason);
        fgets(line, sizeof(line), file); sscanf(line, "Status             : %[^\n]", temp.status);
        fgets(line, sizeof(line), file); 

        applications[count++] = temp;
    }
    fclose(file);

    while (i < count) {
        printf("\n--- Reviewing Application (%d/%d) ---\n", i + 1, count);
        printf("First Name       : %s\n", applications[i].firstName);
        printf("Last Name        : %s\n", applications[i].lastName);
        printf("Email            : %s\n", applications[i].email);
        printf("Age              : %d\n", applications[i].age);
        printf("Occupation       : %s\n", applications[i].occupation);
        printf("Phone            : %s\n", applications[i].phone);
        printf("Address          : %s\n", applications[i].address);
        printf("Marital Status   : %s\n", applications[i].maritalStatus);
        printf("Household Size   : %d\n", applications[i].householdSize);
        printf("Criminal Record  : %s\n", applications[i].criminalRecord);
        printf("Housing Status   : %s\n", applications[i].housingStatus);
        printf("Has Children     : %s\n", applications[i].hasChildren);
        printf("Reason           : %s\n", applications[i].reason);
        printf("Current Status   : %s\n", applications[i].status);

        printf("\n1. Approve\n2. Reject\n3. Skip\n4. Go Back\n5. Search Application\n6. Go Back to Main Menu\nChoice: ");
        scanf("%d", &choice);
        clearScreen();

        if (choice == 1) {
            strcpy(applications[i].status, "Approved");
            printf("Application Approved!\n");

            FILE *userFile = fopen("C:\\Users\\L65X15W07\\Desktop\\Users.txt", "a");
            if (userFile) {
                fprintf(userFile, "========================================\n");
                fprintf(userFile, "Name       : %s %s\n", applications[i].firstName, applications[i].lastName);
                fprintf(userFile, "Age        : %d\n", applications[i].age);
                fprintf(userFile, "Email      : %s\n", applications[i].email);
                fprintf(userFile, "Occupation : %s\n", applications[i].occupation);
                fprintf(userFile, "Phone      : %s\n", applications[i].phone);
                fprintf(userFile, "Address    : %s\n", applications[i].address);
                fprintf(userFile, "========================================\n\n");
                fclose(userFile);
            } else {
                printf("Error: Could not open Users.txt for writing.\n");
            }
            i++;
        } else if (choice == 2) {
            strcpy(applications[i].status, "Rejected");
            printf("Application Rejected.\n");
            i++;
        } else if (choice == 3) {
            printf("You have skipped the application.\n");
            i++;
        } else if (choice == 4) {
            if (i > 0) {
                i--;
                printf("Going back to previous application...\n");
            } else {
                printf("Already at the first application.\n");
            }
            Sleep(1500);
            continue;
        } else if (choice == 5) {
            char searchEmail[100];
            printf("Enter the email to search for: ");
            scanf("%s", searchEmail);

            int found = 0;
            for (j = 0; j < count; j++) {
                if (strcmp(applications[j].email, searchEmail) == 0) {
                    printf("Application found:\n");
                    printf("First Name : %s\n", applications[j].firstName);
                    printf("Last Name  : %s\n", applications[j].lastName);
                    printf("Email      : %s\n", applications[j].email);
                    printf("Status     : %s\n", applications[j].status);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("No application found with that email.\n");
            }
            printf("Press any key to go back to the application review.\n");
            getchar(); getchar();
            continue;
        } else if (choice == 6) {
            printf("Going back to the main menu...\n");
            Sleep(2000);      
            clearScreen();     
            return;  
        } else {
            printf("Invalid choice. Please select 1, 2, 3, 4, 5, or 6.\n");
            continue;
        }

        printf("\nPress any key to continue to the next application...\n");
        getchar(); getchar();
        clearScreen();  
    }

    
    file = fopen("C:\\Users\\L65X15W07\\Desktop\\Applications.txt", "w");
    if (!file) {
        printf("Error: Could not save updated applications.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        fprintf(file, "=================================\n");
        fprintf(file, "Email              : %s\n", applications[i].email);
        fprintf(file, "First Name         : %s\n", applications[i].firstName);
        fprintf(file, "Last Name          : %s\n", applications[i].lastName);
        fprintf(file, "Age                : %d\n", applications[i].age);
        fprintf(file, "Address            : %s\n", applications[i].address);
        fprintf(file, "Occupation         : %s\n", applications[i].occupation);
        fprintf(file, "Phone              : %s\n", applications[i].phone);
        fprintf(file, "Marital Status     : %s\n", applications[i].maritalStatus);
        fprintf(file, "Household Size     : %d\n", applications[i].householdSize);
        fprintf(file, "Criminal Record    : %s\n", applications[i].criminalRecord);
        fprintf(file, "Housing Status     : %s\n", applications[i].housingStatus);
        fprintf(file, "Has Children       : %s\n", applications[i].hasChildren);
        fprintf(file, "Reason for Adopting: %s\n", applications[i].reason);
        fprintf(file, "Status             : %s\n", applications[i].status);
        fprintf(file, "=================================\n\n");
    }

    fclose(file);
    printf("All updates saved!\n");
}

int checkApplicationStatus(const char *email) {
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Applications.txt", "r");
    if (!file) {
        printf("Error: Could not open Applications.txt\n");
        return -2;
    }

    User temp;

   char line[200];  

while (fgets(line, sizeof(line), file)) {
    if (strcmp(line, "=================================\n") != 0)
        continue;  

    
    fscanf(file, "Email              : %[^\n]\n", temp.email);
    fscanf(file, "First Name         : %[^\n]\n", temp.firstName);
    fscanf(file, "Last Name          : %[^\n]\n", temp.lastName);
    fscanf(file, "Age                : %d\n", &temp.age);
    fscanf(file, "Address            : %[^\n]\n", temp.address);
    fscanf(file, "Occupation         : %[^\n]\n", temp.occupation);
    fscanf(file, "Phone              : %[^\n]\n", temp.phone);
    fscanf(file, "Marital Status     : %[^\n]\n", temp.maritalStatus);
    fscanf(file, "Household Size     : %d\n", &temp.householdSize);
    fscanf(file, "Criminal Record    : %[^\n]\n", temp.criminalRecord);
    fscanf(file, "Housing Status     : %[^\n]\n", temp.housingStatus);
    fscanf(file, "Has Children       : %[^\n]\n", temp.hasChildren);
    fscanf(file, "Reason for Adopting: %[^\n]\n", temp.reason);
    fscanf(file, "Status             : %[^\n]\n", temp.status);
    fgets(line, sizeof(line), file);  

    
    if (strcmp(temp.email, email) == 0) {
        fclose(file);
        if (strcmp(temp.status, "Approved") == 0) return 1;
        else if (strcmp(temp.status, "Rejected") == 0) return -1;
        else return 0; 
    }
}

    fclose(file);
    return -2; 
}

void adminMenu() {
    int choice;

    while (1) {
        printf("\n====== Admin Menu ======\n");
        printf("1. Add Child Profile\n");
        printf("2. Delete Child Profile\n");
        printf("3. View All Children\n");
        printf("4. View Adopted Children\n");
        printf("5. View Registered Users\n");
        printf("6. Review Applications\n");
        printf("7. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            Sleep(1500);
            clearScreen();
            continue;
        }

        clearScreen();

        switch (choice) {
            case 1:
                addChild();
                         
   				 loadChildren();
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
            case 6:
                adminReviewApplications();
                break;
            case 7:
                printf("Exiting Admin Menu...\n");
                Sleep(1000);
                return;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
                Sleep(1500);
                break;
        }
    }
}
void adminLogin() {
    char pass[20];
    int choice;

    while (1) {
        printf("\n====== Admin Login ======\n");
        printf("1. Enter Admin Password\n");
        printf("2. Back\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number (1 or 2).\n");
            Sleep(1500);
            while (getchar() != '\n');
            clearScreen();
            continue;
        }

        if (choice == 2) {
            printf("Going back...\n");
            Sleep(1500);
            clearScreen();
            return;  
        } else if (choice == 1) {
            printf("\nEnter Admin Password: ");
            scanf("%s", pass); 
            clearScreen();

            if (strcmp(pass, "admin123") == 0) {
                printf("\nAdmin Login Successful!\n");
                Sleep(1500);
                clearScreen();
                adminMenu();
                return;  
            } else {
                printf("\nIncorrect Password. Try again.\n");
                Sleep(1500);
                clearScreen();
            }
        } else {
            printf("\nInvalid choice. Please select 1 (Login) or 2 (Back).\n");
            Sleep(1500);
            clearScreen();
        }
    }
}

void loadUsers() {
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Users.txt", "r");
    if (!file) {
        printf("No user data found. Starting fresh.\n");
        return;
    }

    userCount = 0;
    while (fscanf(file, "=================================\n") != EOF) {
        fscanf(file, "First Name   : %[^\n]\n", users[userCount].firstName);
        fscanf(file, "Last Name    : %[^\n]\n", users[userCount].lastName);
        fscanf(file, "Email        : %s\n", users[userCount].login.email);  
        fscanf(file, "Password     : %s\n", users[userCount].login.password);  
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
    int choice;

    loadUsers();
    loadChildren();

    while (1) {
        printf("\n========== WELCOME TO CHILD ADOPTION CENTER ==========\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");
        printf("======================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            Sleep(1500);
            clearScreen();
            continue;
        }

        clearScreen();

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                Sleep(1500);
                break;
        }
    }
    return 0;
}
