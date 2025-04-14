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
        printf("\n1. Adopt a Child\n2. View Children\n3. Return a Child\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        clearScreen();
        switch (choice) {
            case 1:
                adoptChild();  
                break;
            case 2:
                viewChildren();
                break;
            case 3:
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
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Credentials.txt", "a");
    if (!file) {
        printf("Error: Could not open credentials file.\n");
        return;
    }
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
        fprintf(file, "%s %s\n", login.email, login.password);  
        fclose(file);

        printf("\nAccount Created Successfully!\n");
        Sleep(1500);  
        clearScreen(); 
    }
}

void submitApplication(const char *email) {
    User user;
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Applications.txt", "a");
    if (!file) {
        printf("Error: Could not open application file.\n");
        return;
    }

    strcpy(user.email, email);
    printf("\n========= Adoption Application Form =========\n");

    do {
        printf("Enter First Name: ");
        scanf(" %[^\n]", user.firstName);
    } while (user.firstName[0] == '\0');  

    do {
        printf("Enter Last Name: ");
        scanf(" %[^\n]", user.lastName);
    } while (user.lastName[0] == '\0');  

    printf("Enter Age: ");
    while (scanf("%d", &user.age) != 1 || user.age <= 0) {
        printf("Invalid age. Please enter a valid age: ");
        while (getchar() != '\n');
    }

    do {
        printf("Enter Address: ");
        scanf(" %[^\n]", user.address);
    } while (user.address[0] == '\0'); 

    do {
        printf("Enter Occupation: ");
        scanf(" %[^\n]", user.occupation);
    } while (user.occupation[0] == '\0');  

    do {
        printf("Enter Phone Number: ");
        scanf(" %[^\n]", user.phone);
    } while (user.phone[0] == '\0');  

    do {
        printf("Enter Marital Status (Single/Married): ");
        scanf(" %[^\n]", user.maritalStatus);
    } while (user.maritalStatus[0] == '\0');  

    printf("Enter Number of Household Members: ");
    while (scanf("%d", &user.householdSize) != 1 || user.householdSize <= 0) {
        printf("Invalid number. Please enter a valid household size: ");
        while (getchar() != '\n');
    }

    do {
        printf("Do you have any criminal record? (Yes/No): ");
        scanf(" %[^\n]", user.criminalRecord);
    } while (user.criminalRecord[0] == '\0');  

    do {
        printf("Do you own or rent your home? (Own/Rent): ");
        scanf(" %[^\n]", user.housingStatus);
    } while (user.housingStatus[0] == '\0');  

    do {
        printf("Do you currently have children? (Yes/No): ");
        scanf(" %[^\n]", user.hasChildren);
    } while (user.hasChildren[0] == '\0');  

    do {
        printf("Why do you want to adopt a child?\n-> ");
        scanf(" %[^\n]", user.reason);
    } while (user.reason[0] == '\0');  

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

    printf("\n? Application Submitted for Review!\n");
    Sleep(1500);
    clearScreen();
}
void userLogin() {
    char email[100], password[50];
    int i, j, choice;

    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Credentials.txt", "r");
    if (!file) {
        printf("Error: Could not open credentials file.\n");
        return;
    }

    loginCount = 0;
    while (fscanf(file, "%s %s", logins[loginCount].email, logins[loginCount].password) == 2) {
        loginCount++;
    }
    fclose(file);

    while (1) {
        printf("\n====== User Login ======\n");
        printf("1. Enter Login Credentials\n");
        printf("2. Submit an Application Form\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearScreen();

        switch (choice) {
            case 1:
                printf("Enter Email: ");
                scanf("%s", email);
                printf("Enter Password: ");
                scanf("%s", password);
                clearScreen();

                for (i = 0; i < loginCount; i++) {
                    if (strcmp(logins[i].email, email) == 0 && strcmp(logins[i].password, password) == 0) {
                        FILE *appFile = fopen("D:\\Programs\\Child Adoption Database\\Applications.txt", "r");
                        if (!appFile) {
                            printf("Error: Could not open Applications.txt\n");
                            return;
                        }

                        char line[200], status[20];
                        int found = 0;

                        while (fgets(line, sizeof(line), appFile)) {
                            if (strstr(line, email)) {
                                for (j = 0; j < 7; j++) fgets(line, sizeof(line), appFile);
                                fscanf(appFile, "Status             : %[^\n]\n", status);
                                found = 1;
                                break;
                            }
                        }
                        fclose(appFile);

                        if (!found) {
                            printf("No application found. Please submit your application first.\n");
                            Sleep(2000);
                            clearScreen();
                            break;
                        }

                        if (strcmp(status, "Approved") == 0) {
                            printf("Login Successful! Welcome.\n");
                            Sleep(1500);
                            clearScreen();
                            menu(); 
                            return;
                        } else if (strcmp(status, "Pending") == 0) {
                            printf("Your application is still under review. Please check back later.\n");
                            Sleep(2000);
                            clearScreen();
                            break;
                        } else if (strcmp(status, "Rejected") == 0) {
                            printf("Your application was rejected.\n");
                            printf("If you believe this was a mistake, please contact support@adoptioncenter.com\n");
                            Sleep(3000);
                            clearScreen();
                            break;
                        }
                    }
                }

                printf("Invalid credentials. Please try again.\n");
                Sleep(1500);
                clearScreen();
                break;

            case 2:
                printf("Enter your registered email: ");
                scanf("%s", email);
                submitApplication(email);
                break;

            case 3:
                return;

            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                Sleep(1500);
                clearScreen();
                break;
        }
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
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Childrens.txt", "a");
    if (!file) {
        printf("Error opening child file.\n");
        return;
    }

    if (childCount >= MAX_CHILDREN) {
        printf("Child profile limit reached.\n");
        fclose(file);
        return;
    }

    printf("Enter Child Name: ");
    scanf(" %[^\n]", child.name);

    printf("Enter Age: ");
    while (scanf("%d", &child.age) != 1 || child.age <= 0) {
        printf("Invalid age. Please enter a valid age: ");
        while (getchar() != '\n');
    }

    printf("Enter Gender (M/F): ");
    while (scanf(" %s", child.gender) != 1 || (child.gender[0] != 'M' && child.gender[0] != 'F')) {
        printf("Invalid gender. Please enter M or F: ");
        while (getchar() != '\n');
    }

    printf("Enter Birth Date (YYYY-MM-DD): ");
    scanf(" %s", child.birthDate);

    printf("Enter Height (cm): ");
    while (scanf("%f", &child.height) != 1 || child.height <= 0) {
        printf("Invalid height. Please enter a valid height: ");
        while (getchar() != '\n');
    }

    printf("Enter Weight (kg): ");
    while (scanf("%f", &child.weight) != 1 || child.weight <= 0) {
        printf("Invalid weight. Please enter a valid weight: ");
        while (getchar() != '\n');
    }

    printf("Enter Blood Type: ");
    scanf(" %s", child.bloodType);

    printf("Enter Allergies: ");
    scanf(" %[^\n]", child.allergies);

    printf("Enter Medical Conditions: ");
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
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Childrens.txt", "r");
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

void adoptChild() {
    int i;
    char choice[8];  

    printf("\n=== Available Children ===\n");

    int availableCount = 0;
    for (i = 0; i < childCount; i++) {
        
        if (children[i].adopted == 0 && strlen(children[i].id) > 0) {
            printf("\n----------------------------------------\n");
            printf("Child ID: %s\n", children[i].id);
            printf("Name: %s\n", children[i].name);
            printf("Age: %d years\n", children[i].age);
            printf("Gender: %s\n", children[i].gender);
            printf("Height: %.2f cm\n", children[i].height);
            printf("Weight: %.2f kg\n", children[i].weight);
            printf("Blood Type: %s\n", children[i].bloodType);
            printf("Status: Available\n");
            printf("----------------------------------------\n");
            availableCount++;
        }
    }

    if (availableCount == 0) {
        printf("\nNo children available for adoption.\n");
        return;
    }

    printf("\nEnter the Child ID to adopt or 0 to cancel: ");
    scanf("%s", choice);  

    if (strcmp(choice, "0") == 0) {
        printf("\nAdoption canceled.\n");
        return;
    }

    
    for (i = 0; i < childCount; i++) {
        if (children[i].adopted == 0 && strcmp(children[i].id, choice) == 0) {
            children[i].adopted = 1;
            printf("\nYou have successfully adopted %s!\n", children[i].name);
            return;
        }
    }

    printf("\nInvalid Child ID.\n");
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
		printf(" Email      : %s\n", users[i].login.email);
        printf(" Occupation : %s\n", users[i].occupation);
        printf(" Phone      : %s\n", users[i].phone);
        printf(" Address    : %s\n", users[i].address);
        printf("----------------------------------------\n");
    }
}
void adminReviewApplications() {
    int i, j, choice;
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Applications.txt", "r");
    if (!file) {
        printf("Error: Could not open application file.\n");
        return;
    }

    User applications[100];
    int count = 0;
    User temp;

    while (fscanf(file, "=================================\n") == 0) {
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
        fscanf(file, "=================================\n");

        applications[count++] = temp;
    }

    fclose(file);

    while (i < count) {
        printf("\n--- Reviewing Application (%d/%d) ---\n", i + 1, count);
        printf("Name             : %s %s\n", applications[i].firstName, applications[i].lastName);
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

        printf("\n1. Approve\n2. Reject\n3. Skip\n4. Go Back\n5. Search Application\nChoice: ");
        scanf("%d", &choice);
        clearScreen();

        if (choice == 1) {
            strcpy(applications[i].status, "Approved");
            printf("Application Approved!\n");
            printf("Press any key to continue...\n");
            getchar();  
        } else if (choice == 2) {
            strcpy(applications[i].status, "Rejected");
            printf("Application Rejected.\n");
            printf("Press any key to continue...\n");
            getchar();  
        } else if (choice == 3) {
            printf("You have skipped the application.\n");
            printf("Press any key to continue...\n");
            getchar(); 
        } else if (choice == 4) {
            printf("Going back to previous application...\n");
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
                    printf("Name: %s %s\n", applications[j].firstName, applications[j].lastName);
                    printf("Email: %s\n", applications[j].email);
                    printf("Status: %s\n", applications[j].status);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("No application found with that email.\n");
            }
            printf("Press any key to go back to the application review.\n");
            getchar();  
        } else {
            printf("Invalid choice. Please select 1, 2, 3, 4, or 5.\n");
        }

        printf("\nPress any key to continue to the next application...\n");
        getchar();  
        i++;
    }
    file = fopen("D:\\Programs\\Child Adoption Database\\Applications.txt", "w");
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
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Applications.txt", "r");
    if (!file) {
        printf("Error: Could not open Applications.txt\n");
        return -2;
    }

    User temp;

    while (fscanf(file, "=================================\n") == 0) {
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
        fscanf(file, "=================================\n");

        if (strcmp(temp.email, email) == 0) {
            fclose(file);
            if (strcmp(temp.status, "Approved") == 0)
                return 1;
            else if (strcmp(temp.status, "Rejected") == 0)
                return -1;
            else
                return 0;
        }
    }

    fclose(file);
    return -2; 
}
void adminMenu() {
    int choice;
    do {
        printf("\n====== Admin Menu ======\n");
        printf("1. Add Child Profile\n2. Delete Child Profile\n3. View All Children\n4. View Adopted Children\n5. View Registered Users\n6. Review Applications\n7. Exit\nChoice: ");
        scanf("%d", &choice);
        clearScreen();
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
            case 6: 
                adminReviewApplications();  
                break;
        }
    } while (choice != 7);
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
    FILE *file = fopen("D:\\Programs\\Child Adoption Database\\Users.txt", "r");
    if (!file) {
        printf("? No user data found. Starting fresh.\n");
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
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearScreen();

        switch (choice) {
            case 1:
				signUp();
                break;
            case 2: {
                userLogin();  
                break;
            }
            case 3:
                adminLogin();
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
