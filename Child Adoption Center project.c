#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <shlobj.h>
#include <time.h>
#define MAX_CHILDREN 100
#include <ctype.h>
#include <conio.h>
#define MAX_MATCHES 100


typedef struct {
    char email[100];
    char password[100];
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

Child children[MAX_CHILDREN];
int childCount = 0;
User loggedInUser = {0};


void adminMenu();
void AdminLogin();
void addChild();
void viewAllChildren();
void deleteChild();

void signUp();
int loginUser();
void adoptionMenu();
void submitApplication();
int hasSubmittedApplication(const char *email);
int hasSubmittedApplicationWithStatus(const char *email, char *status);
void clearScreen();

void clearScreen() {
    system("cls");  
}

void getPassword(char *password) {
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 99) { 
        if (ch == '\b') { 
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

void signUp() {
    User user;
    char confirmPassword[100];
    FILE *file;
    char filePath[MAX_PATH], line[512], existingEmail[100];

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\users.txt"); 

    while (1) {
        printf("========= Create Account =========\n");
        printf("Enter Email (press 0 to go back): ");
        scanf(" %s", user.email);  

        if (strcmp(user.email, "0") == 0) {  
            printf("\nReturning to main menu...\n");
            Sleep(1500);
            clearScreen();
            return;
        }

        
        file = fopen(filePath, "r");
        int duplicate = 0;
        if (file) {
            while (fgets(line, sizeof(line), file)) {
                sscanf(line, "%99[^|]", existingEmail);
                if (strcmp(existingEmail, user.email) == 0) {
                    duplicate = 1;
                    break;
                }
            }
            fclose(file);
        }

        if (duplicate) {
            printf("This email is already registered. Please use a different email.\n");
            Sleep(2000);
            clearScreen();
            continue;
        }

        printf("Enter Password: ");
        getPassword(user.password);  

        printf("Confirm Password: ");
        getPassword(confirmPassword);

        if (strcmp(user.password, confirmPassword) != 0) {  
            printf("Passwords do not match. Try again.\n");
            Sleep(1500);
            clearScreen();
            continue;
        }

        printf("First Name: ");
        scanf(" %s", user.firstName);

        printf("Last Name: ");
        scanf(" %s", user.lastName);

        printf("Age: ");
        scanf("%d", &user.age);

        file = fopen(filePath, "a");
        if (file == NULL) {
            printf("Error opening file at: %s\n", filePath);
            return;
        }

        fprintf(file, "%s|%s|%s|%s|%d\n", 
            user.email,        
            user.password,     
            user.firstName, 
            user.lastName, 
            user.age);

        fclose(file);

        printf("\nAccount created successfully!\n");
        Sleep(2000);
        clearScreen();
        return;
    }
}



int loginUser() {
    char inputEmail[100], inputPassword[100], line[512];
    char email[100], password[100], firstName[50], lastName[50];
    int age;
    char filePath[MAX_PATH];

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\users.txt");

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("No registered users found.\n");
        Sleep(1500);
        clearScreen();
        return 0;
    }

    printf("========= User Login =========\n");

    while (1) {
        
        printf("Email (press 0 to go back): ");
        scanf(" %s", inputEmail);

        if (strcmp(inputEmail, "0") == 0) {
            printf("\nReturning to main menu...\n");
            Sleep(1500);
            clearScreen();
            return 0;  
        }

        
        printf("Password: ");
        getPassword(inputPassword);

        
        int found = 0;
        
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%99[^|]|%99[^|]|%49[^|]|%49[^|]|%d",
                   email, password, firstName, lastName, &age);

            if (strcmp(inputEmail, email) == 0 && strcmp(inputPassword, password) == 0) {
                found = 1;
                break;
            }
        }
        
		        strcpy(loggedInUser.email, email);
		strcpy(loggedInUser.password, password);
		strcpy(loggedInUser.firstName, firstName);
		strcpy(loggedInUser.lastName, lastName);
		loggedInUser.age = age;

        fclose(file);

        if (found) {
            printf("\nLogin successful! Welcome %s %s\n", firstName, lastName);
            Sleep(2000);
            clearScreen();
            return 1;  
        } else {
            printf("\nInvalid email or password. Try again.\n");
            Sleep(2000);
            clearScreen();
        }

       
        file = fopen(filePath, "r");
        if (file == NULL) {
            printf("Error opening user file.\n");
            Sleep(1500);
            clearScreen();
            return 0;
        }
    }
}


void adoptionMenu() {
    int choice;
    char status[50];

    do {
        clearScreen();  

        
        printf("=====================================================\n");
        printf(" __          __  _                          _      \n");
        printf(" \\ \\        / / | |                        | |     \n");
        printf("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___| |     \n");
        printf("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ |     \n");
        printf("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/_|     \n");
        printf("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___(_)\n");
        printf("=====================================================\n");

        
        printf("   [1] Adopt a Child\n");
        printf("   [2] View Adopted Children\n");
        printf("   [3] Submit Application\n");
        printf("   [4] Notification\n");
        printf("   [5] Exit\n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number between 1 and 4.\n");
            while (getchar() != '\n');  
            Sleep(1500);
            continue;
        }

        clearScreen();  

        switch (choice) {
            case 1:
                if (!hasSubmittedApplicationWithStatus(loggedInUser.email, status)) {
                    printf("You need to submit an application before adopting a child.\n");
                } else if (strcmp(status, "Pending") == 0) {
                    printf("Your application is still under review. Status: %s\n", status);
                } else if (strcmp(status, "Approved") == 0) {
                    printf("You are eligible to adopt a child!\n");
                    AdoptChildMenu();
                } else {
                    printf("Your application was not approved. Status: %s\n", status);
                }
                Sleep(2000);
                break;

            case 2:
                if (!hasSubmittedApplicationWithStatus(loggedInUser.email, status)) {
                    printf("You need to submit an application before viewing adopted children.\n");
                } else if (strcmp(status, "Approved") != 0) {
                    printf("Only approved applications can view adopted children. Status: %s\n", status);
                } else {
                    printf("Displaying adopted children...\n");
                    viewMyAdoptedChildren();
                }
                Sleep(2000);
                break;

            case 3:
                submitApplication();
                break;
                
            case 4:
				checkNotifications(loggedInUser.email);
    			break;   

            case 5:
                printf("Exiting adoption section...\n");
                Sleep(1500);
                break;

            default:
                printf("\nInvalid choice. Please select a number between 1 and 4.\n");
                Sleep(1500);
        }

        clearScreen();

    } while (choice != 5);
}



void checkNotifications(const char *email) {
    FILE *file = fopen("notifications.txt", "r");
    if (!file) {
        printf("No notifications available.\n");
        return;
    }

    char line[256], childName[50], status[20], userEmail[100];
    int found = 0;

    printf("==== Your Adoption Notifications ====\n");

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%99[^|]|%49[^|]|%19[^\n]", userEmail, childName, status);

        
        if (strcmp(userEmail, email) == 0) {
            printf("Notification: Your adoption request for %s was %s.\n", childName, status);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("No new notifications.\n");
    }

    system("pause");  
}


void AdminLogin() {
    char adminUsername[100], adminPassword[100];
    const char correctUsername[] = "admin";  
    const char correctPassword[] = "admin123";  

    while (1) {
        printf("========= Admin Login =========\n");
        printf("Enter '0' at any time to return to the main menu.\n");
        printf("Admin Username: ");
        scanf(" %s", adminUsername);

        if (strcmp(adminUsername, "0") == 0) {
            printf("\nReturning to main menu...\n");
            Sleep(1500);
            clearScreen();
            return;
        }

        printf("Admin Password: ");
        getPassword(adminPassword);

        if (strcmp(adminPassword, "0") == 0) {
            printf("\nReturning to main menu...\n");
            Sleep(1500);
            clearScreen();
            return;
        }

        if (strcmp(adminUsername, correctUsername) == 0 && strcmp(adminPassword, correctPassword) == 0) {
            printf("\nAdmin Login successful! Welcome %s\n", adminUsername);
            Sleep(2000);
            clearScreen();
         	adminMenu();
            return;
            
        } else {
            printf("\nInvalid Admin username or password. Try again.\n");
            Sleep(2000);
            clearScreen();
        }
    }
}

void adminMenu() {
    int choice;

    while (1) {
        clearScreen();  

        
        printf("=====================================================\n");
        printf("               _           _                       \n");
        printf("      /\      | |         (_)                      \n");
        printf("     /  \\   __| |_ __ ___  _ _ __                  \n");
        printf("    / /\ \\ / _` | '_ ` _ \\| | '_ \\                 \n");
        printf("   / ____ \\ (_| | | | | | | | | | |                \n");
        printf("  /_/    \\_\\__,_|_| |_| |_|_|_| |_|                \n");
        printf("=====================================================\n");
        
        
        printf("   [1] Add Child Profile\n");
        printf("   [2] Delete Child Profile\n");
        printf("   [3] View All Children\n");
        printf("   [4] View Adopted Children\n");
        printf("   [5] View Registered Users\n");
        printf("   [6] Review Applications\n");
        printf("   [7] Review Adoption\n");
        printf("   [8] Exit\n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice (1-8): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number between 1 and 8.\n");
            while (getchar() != '\n'); 
            Sleep(1500);
            continue;
        }

        clearScreen();  

        switch (choice) {
            case 1:
                addChild();
                break;
            case 2:
                deleteChild();
                break;
            case 3:
                viewAllChildren();
                break;
            case 4:
                viewAdoptedChildren();
                break;
            case 5:
                printf("View Registered Users - Feature to be implemented.\n");
                break;
            case 6:
                reviewApplications();
                break;
            case 7:
                reviewAdoptions();
                break;
            case 8:
                printf("Returning to main menu...\n");
                Sleep(1500);
                clearScreen();
                return;
            default:
                printf("\nInvalid choice. Please select a number between 1 and 8.\n");
                Sleep(1500);
                clearScreen();
        }
    }
}


//admin menu functions:

void generateChildID(char id[], char genderInitial) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int i;
    int idExists = 1;

    srand((unsigned int)time(NULL)); 

    while (idExists) {
        id[0] = genderInitial; 

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
    FILE *file;
    char filePath[MAX_PATH];
    char genderInitial;

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\children.txt");

    printf("========= Add Child Profile =========\n");
    printf("(Enter 0 at any time to go back to the Admin Menu)\n");

    printf("Name: ");
    scanf(" %[^\n]", child.name);
    if (strcmp(child.name, "0") == 0) return;

    while (1) {
        printf("Gender (Male/Female): ");
        scanf(" %9s", child.gender);
        if (strcmp(child.gender, "0") == 0) return;

        if (strcasecmp(child.gender, "Male") == 0) {
            genderInitial = 'M';
            break;
        } else if (strcasecmp(child.gender, "Female") == 0) {
            genderInitial = 'F';
            break;
        } else {
            printf("Invalid input. Please enter 'Male' or 'Female'.\n");
        }
    }

    while (1) {
        printf("Birth Date (YYYY-MM-DD): ");
        scanf(" %19s", child.birthDate);
        if (strcmp(child.birthDate, "0") == 0) return;

        
        if (strlen(child.birthDate) == 10 &&
            child.birthDate[4] == '-' &&
            child.birthDate[7] == '-' &&
            isdigit(child.birthDate[0]) && isdigit(child.birthDate[1]) &&
            isdigit(child.birthDate[2]) && isdigit(child.birthDate[3]) &&
            isdigit(child.birthDate[5]) && isdigit(child.birthDate[6]) &&
            isdigit(child.birthDate[8]) && isdigit(child.birthDate[9])) {
            break;
        } else {
            printf("Invalid format. Please enter in YYYY-MM-DD format.\n");
        }
    }

    while (1) {
        printf("Age: ");
        if (scanf("%d", &child.age) == 1 && child.age > 0) break;
        printf("Invalid age. Please enter a positive number.\n");
        while (getchar() != '\n');
    }

    while (1) {
        printf("Height (in cm): ");
        if (scanf("%f", &child.height) == 1 && child.height > 0) break;
        printf("Invalid height. Please enter a positive number.\n");
        while (getchar() != '\n');
    }

    while (1) {
        printf("Weight (in kg): ");
        if (scanf("%f", &child.weight) == 1 && child.weight > 0) break;
        printf("Invalid weight. Please enter a positive number.\n");
        while (getchar() != '\n');
    }

    child.adopted = 0;

    while (1) {
        printf("Blood Type (A+/A-/B+/B-/AB+/AB-/O+/O-): ");
        scanf(" %4s", child.bloodType);
        if (strcmp(child.bloodType, "0") == 0) return;

        if (strcmp(child.bloodType, "A+") == 0 || strcmp(child.bloodType, "A-") == 0 ||
            strcmp(child.bloodType, "B+") == 0 || strcmp(child.bloodType, "B-") == 0 ||
            strcmp(child.bloodType, "AB+") == 0 || strcmp(child.bloodType, "AB-") == 0 ||
            strcmp(child.bloodType, "O+") == 0 || strcmp(child.bloodType, "O-") == 0) {
            break;
        } else {
            printf("Invalid blood type. Please try again.\n");
        }
    }

    printf("Allergies (type 'None' if no allergies): ");
    scanf(" %[^\n]", child.allergies);
    if (strcmp(child.allergies, "0") == 0) return;

    printf("Medical Conditions (type 'None' if none): ");
    scanf(" %[^\n]", child.medicalConditions);
    if (strcmp(child.medicalConditions, "0") == 0) return;

    printf("Education Level: ");
    scanf(" %[^\n]", child.educationLevel);
    if (strcmp(child.educationLevel, "0") == 0) return;

    printf("Hobbies: ");
    scanf(" %[^\n]", child.hobbies);
    if (strcmp(child.hobbies, "0") == 0) return;

    printf("Languages Spoken: ");
    scanf(" %[^\n]", child.languagesSpoken);
    if (strcmp(child.languagesSpoken, "0") == 0) return;

    generateChildID(child.id, genderInitial);

    file = fopen(filePath, "a");
    if (file == NULL) {
        printf("Error opening file at: %s\n", filePath);
        return;
    }

    fprintf(file, "%s|%s|%s|%s|%d|%.2f|%.2f|%d|%s|%s|%s|%s|%s|%s\n",
        child.id, child.name, child.gender, child.birthDate,
        child.age, child.height, child.weight, child.adopted,
        child.bloodType, child.allergies, child.medicalConditions,
        child.educationLevel, child.hobbies, child.languagesSpoken
    );

    fclose(file);

    if (childCount < MAX_CHILDREN) {
        children[childCount++] = child;
    }

    printf("\nChild profile added successfully!\nGenerated Child ID: %s\n", child.id);
    Sleep(3000);
    clearScreen();
}


void deleteChild() {
    char filePath[MAX_PATH];
    FILE *file;
    char line[512];
    Child tempChildren[MAX_CHILDREN];
    int tempCount = 0;
    int i;

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\children.txt");

    file = fopen(filePath, "r");
    if (!file) {
        printf("Error opening file or no child profiles exist.\n");
        Sleep(2000);
        return;
    }

    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%7[^|]|%49[^|]|%9[^|]|%19[^|]|%d|%f|%f|%d|%4[^|]|%99[^|]|%199[^|]|%49[^|]|%99[^|]|%99[^\n]",
                   tempChildren[tempCount].id, tempChildren[tempCount].name, tempChildren[tempCount].gender,
                   tempChildren[tempCount].birthDate, &tempChildren[tempCount].age,
                   &tempChildren[tempCount].height, &tempChildren[tempCount].weight,
                   &tempChildren[tempCount].adopted, tempChildren[tempCount].bloodType,
                   tempChildren[tempCount].allergies, tempChildren[tempCount].medicalConditions,
                   tempChildren[tempCount].educationLevel, tempChildren[tempCount].hobbies,
                   tempChildren[tempCount].languagesSpoken) == 14) {
            tempCount++;
            if (tempCount >= MAX_CHILDREN) break;
        }
    }
    fclose(file);

    if (tempCount == 0) {
        printf("No child profiles found.\n");
        Sleep(2000);
        return;
    }

    int choice = -1;
    do {
        clearScreen();
        printf("========= Delete Child Profile =========\n");
        for (i = 0; i < tempCount; i++) {
            printf("%d. ID: %s | Name: %s\n", i + 1, tempChildren[i].id, tempChildren[i].name);
        }

        printf("\nEnter the number of the child to delete (0 to cancel): ");
        if (scanf("%d", &choice) != 1 || choice < 0 || choice > tempCount) {
            printf("Invalid input. Please enter a number between 0 and %d.\n", tempCount);
            while (getchar() != '\n'); 
            Sleep(2000);
            choice = -1; 
        }
    } while (choice < 0 || choice > tempCount);

    if (choice == 0) {
        printf("Operation cancelled.\n");
        Sleep(2000);
        return;
    }

    int indexToDelete = choice - 1;

    
    char confirm[10];
    do {
        printf("\nAre you sure you want to delete %s (ID: %s)? (y/n): ",
               tempChildren[indexToDelete].name, tempChildren[indexToDelete].id);
        scanf(" %9s", confirm);

        if (strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") == 0) {
            break;
        } else if (strcmp(confirm, "n") == 0 || strcmp(confirm, "N") == 0) {
            printf("Deletion cancelled.\n");
            Sleep(2000);
            return;
        } else {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    } while (1);

    
    for (i = indexToDelete; i < tempCount - 1; i++) {
        tempChildren[i] = tempChildren[i + 1];
    }
    tempCount--;

    
    file = fopen(filePath, "w");
    if (!file) {
        printf("Error writing to file.\n");
        Sleep(2000);
        return;
    }

    for (i = 0; i < tempCount; i++) {
        fprintf(file, "%s|%s|%s|%s|%d|%.2f|%.2f|%d|%s|%s|%s|%s|%s|%s\n",
            tempChildren[i].id, tempChildren[i].name, tempChildren[i].gender,
            tempChildren[i].birthDate, tempChildren[i].age, tempChildren[i].height,
            tempChildren[i].weight, tempChildren[i].adopted, tempChildren[i].bloodType,
            tempChildren[i].allergies, tempChildren[i].medicalConditions,
            tempChildren[i].educationLevel, tempChildren[i].hobbies,
            tempChildren[i].languagesSpoken);
    }

    fclose(file);

    printf("Child profile deleted successfully.\n");
    Sleep(2000);
    clearScreen();
}


void viewAllChildren() {
    FILE *file, *pendingFile;
    char filePath[MAX_PATH];
    char line[512];
    Child children[MAX_CHILDREN];
    char pendingIDs[MAX_CHILDREN][10]; 
    int childCount = 0, currentIndex = 0, pendingCount = 0;
    int i;

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\children.txt");

    file = fopen(filePath, "r");
    if (file == NULL) {
        printf("No child profiles found or error opening file.\n");
        Sleep(2000);
        return;
    }

   
    pendingFile = fopen("pending_adoptions.txt", "r");
    if (pendingFile != NULL) {
        while (fgets(line, sizeof(line), pendingFile)) {
            sscanf(line, "%9[^|]", pendingIDs[pendingCount]);
            pendingCount++;
        }
        fclose(pendingFile);
    }

    
    while (fgets(line, sizeof(line), file)) {
        Child c;
        if (sscanf(line, "%7[^|]|%49[^|]|%9[^|]|%19[^|]|%d|%f|%f|%d|%4[^|]|%99[^|]|%199[^|]|%49[^|]|%99[^|]|%99[^\n]",
                   c.id, c.name, c.gender, c.birthDate, &c.age, &c.height, &c.weight, &c.adopted,
                   c.bloodType, c.allergies, c.medicalConditions, c.educationLevel, c.hobbies, c.languagesSpoken) == 14) {

           
            int isPending = 0;
            for (i = 0; i < pendingCount; i++) {
                if (strcmp(c.id, pendingIDs[i]) == 0) {
                    isPending = 1;
                    break;
                }
            }

            if (!isPending) {
                children[childCount++] = c;
                if (childCount >= MAX_CHILDREN) break;
            }
        }
    }

    fclose(file);

    if (childCount == 0) {
        printf("No available child profiles.\n");
        printf("\nPress Enter to return to the Admin Menu...");
        getchar();
        getchar();
        clearScreen();
        return;
    }

    while (1) {
        clearScreen();
        printf("========= Child Profile %d of %d =========\n", currentIndex + 1, childCount);
        Child c = children[currentIndex];
        printf("ID: %s\n", c.id);
        printf("Name: %s\n", c.name);
        printf("Gender: %s\n", c.gender);
        printf("Birth Date: %s\n", c.birthDate);
        printf("Age: %d\n", c.age);
        printf("Height: %.2f cm\n", c.height);
        printf("Weight: %.2f kg\n", c.weight);
        printf("Adopted: %s\n", c.adopted ? "Yes" : "No");
        printf("Blood Type: %s\n", c.bloodType);
        printf("Allergies: %s\n", c.allergies);
        printf("Medical Conditions: %s\n", c.medicalConditions);
        printf("Education Level: %s\n", c.educationLevel);
        printf("Hobbies: %s\n", c.hobbies);
        printf("Languages Spoken: %s\n", c.languagesSpoken);
        printf("----------------------------------------\n");

        printf("\nPress 'n' for Next, 'p' for Previous, or 'b' to Go Back to Admin Menu: ");
        char choice[10];
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        if (strcmp(choice, "n") == 0 || strcmp(choice, "N") == 0) {
            if (currentIndex < childCount - 1) currentIndex++;
            else {
                printf("You are already at the last profile.\n");
                Sleep(1500);
            }
        } else if (strcmp(choice, "p") == 0 || strcmp(choice, "P") == 0) {
            if (currentIndex > 0) currentIndex--;
            else {
                printf("You are already at the first profile.\n");
                Sleep(1500);
            }
        } else if (strcmp(choice, "b") == 0 || strcmp(choice, "B") == 0) {
            break;
        } else {
            printf("Invalid choice. Please enter 'n', 'p', or 'b'.\n");
            Sleep(1500);
        }
    }
}


void viewAdoptedChildren() {
    char filePath[MAX_PATH], line[256], id[10], name[50], parentEmail[100];
    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\adopted_children.txt");

    FILE *file = fopen(filePath, "r");
    if (!file) {
        printf("No adopted children found.\n");
        Sleep(2000);
        return;
    }

    printf("=========== Adopted Children ==========\n");
    printf("%-10s %-20s %-30s\n", "ID", "Name", "Parent Email");
    printf("--------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%9[^|]|%49[^|]|%99[^\n]", id, name, parentEmail) == 3) {
            printf("%-10s %-20s %-30s\n", id, name, parentEmail);
        }
    }

    fclose(file);
    printf("\nPress Enter to return...");
    getchar();
    getchar();
}


void reviewApplications() {
    FILE *appFile = fopen("applications.txt", "r");
    FILE *detailsFile = fopen("applicationDetails.txt", "r");

    if (!appFile || !detailsFile) {
        printf("Error: Could not open application files.\n");
        Sleep(2000);
        if (appFile) fclose(appFile);
        if (detailsFile) fclose(detailsFile);
        return;
    }

    char emails[100][100];
    char statuses[100][50];
    char line[1024];
    int appCount = 0, i;

    while (fgets(line, sizeof(line), appFile)) {
        sscanf(line, " %99[^|]|%49[^\n]", emails[appCount], statuses[appCount]);
        appCount++;
    }
    fclose(appFile);

    if (appCount == 0) {
        printf("No applications to review.\n");
        fclose(detailsFile);
        Sleep(2000);
        return;
    }

    int index = 0;
    char choice;

    while (1) {

        while (index < appCount && (strcmp(statuses[index], "Approved") == 0 || strcmp(statuses[index], "Denied") == 0)) {
            index++;
        }

	     if (index >= appCount) {
    printf("No more pending applications to review.\n");

    while (1) {
        printf("Enter [P] to go to previous, [Q] to quit: ");
        char input[100];

        
        fflush(stdin); 

        fgets(input, sizeof(input), stdin);

     
        input[strcspn(input, "\n")] = '\0'; 

       
        if (strlen(input) == 0) {
            printf("Invalid input. Please enter P or Q only.\n");
            continue;
        }

        
        if (strlen(input) != 1 || (strchr("PpQq", input[0]) == NULL)) {
            printf("Invalid input. Please enter P or Q only.\n");
            continue;
        }

       
        choice = toupper(input[0]);

        if (choice == 'P') {
            do {
                index--;
            } while (index >= 0 && (strcmp(statuses[index], "Approved") == 0 || strcmp(statuses[index], "Denied") == 0));

            if (index < 0) {
                printf("You're at the first application.\n");
                index = 0;
            }
            break;
        } else if (choice == 'Q') {
            fclose(detailsFile);
            goto save_changes;
        }
    }

    continue;
}


        rewind(detailsFile);
        int found = 0;

        while (fgets(line, sizeof(line), detailsFile)) {
            char email[100], firstName[50], lastName[50], address[100], occupation[50], phone[20], maritalStatus[20], criminalRecord[10], housingStatus[20], hasChildren[10], reason[201];
            int age, householdSize;

            sscanf(line, "%99[^|]|%49[^|]|%49[^|]|%d|%99[^|]|%49[^|]|%19[^|]|%19[^|]|%d|%9[^|]|%19[^|]|%9[^|]|%200[^\n]",
                   email, firstName, lastName, &age, address, occupation, phone, maritalStatus,
                   &householdSize, criminalRecord, housingStatus, hasChildren, reason);

            if (strcmp(email, emails[index]) == 0) {
                found = 1;

                printf("========== Application #%d ==========\n", index + 1);
                printf("Email: %s\n", email);
                printf("Name: %s %s\n", firstName, lastName);
                printf("Age: %d\n", age);
                printf("Address: %s\n", address);
                printf("Occupation: %s\n", occupation);
                printf("Phone: %s\n", phone);
                printf("Marital Status: %s\n", maritalStatus);
                printf("Household Size: %d\n", householdSize);
                printf("Criminal Record: %s\n", criminalRecord);
                printf("Housing Status: %s\n", housingStatus);
                printf("Has Children: %s\n", hasChildren);
                printf("Reason for Adoption: %s\n", reason);
                printf("Current Status: %s\n", statuses[index]);
                printf("=====================================\n");

               while (1) {
			    printf("\nOptions: [A]pprove, [D]eny, [N]ext, [P]revious, [Q]uit: ");
			    
			    char input[100];
			    
			    
			    fflush(stdin);  
			    
			    fgets(input, sizeof(input), stdin);
			    
			    
			    input[strcspn(input, "\n")] = '\0';  
			    
			    
			    if (strlen(input) == 0) {
			        printf("Invalid input. Please enter A, D, N, P, or Q only.\n");
			        continue;
			    }
			
			  
			    if (strlen(input) != 1 || strchr("AaDdNnPpQq", input[0]) == NULL) {
			        printf("Invalid input. Please enter A, D, N, P, or Q only.\n");
			        continue;
			    }
			    
			    
			    choice = toupper(input[0]);
			
			    if (choice == 'A') {
			        strcpy(statuses[index], "Approved");
			        printf("Application approved.\n");
			        break;
			    } else if (choice == 'D') {
			        strcpy(statuses[index], "Denied");
			        printf("Application denied.\n");
			        break;
			    } else if (choice == 'N') {
			        index++;
			        break;
			    } else if (choice == 'P') {
			        do {
			            index--;
			        } while (index >= 0 && (strcmp(statuses[index], "Approved") == 0 || strcmp(statuses[index], "Denied") == 0));
			
			        if (index < 0) {
			            printf("You're at the first application.\n");
			            index = 0;
			        }
			        break;
			    } else if (choice == 'Q') {
			        fclose(detailsFile);
			        goto save_changes;
			    }
			}


                Sleep(1500);
                clearScreen();
                break;
            }
        }

        if (!found) {
            printf("Details for email %s not found.\n", emails[index]);
            Sleep(1500);
            index++;
        }
    }

    fclose(detailsFile);

save_changes:
    appFile = fopen("applications.txt", "w");
    if (!appFile) {
        printf("Error updating application statuses.\n");
        Sleep(2000);
        return;
    }

    for (i = 0; i < appCount; i++) {
        fprintf(appFile, "%s|%s\n", emails[i], statuses[i]);
    }

    fclose(appFile);
    printf("Application review complete. Changes saved.\n");
    Sleep(2000);
}

void reviewAdoptions() {
    FILE *pendingFile = fopen("pending_adoptions.txt", "r");
    if (!pendingFile) {
        printf("Error: Could not open pending adoptions file.\n");
        return;
    }

    typedef struct {
        char childID[10];
        char childName[50];
        char parentEmail[100];
    } PendingRequest;

    PendingRequest requests[100];
    int count = 0;

    char pendingLine[256];
    while (fgets(pendingLine, sizeof(pendingLine), pendingFile)) {
        if (sscanf(pendingLine, "%9[^|]|%49[^|]|%99[^\n]", 
                   requests[count].childID, 
                   requests[count].childName, 
                   requests[count].parentEmail) == 3) {
            count++;
        }
    }
    fclose(pendingFile);

    if (count == 0) {
        printf("No pending adoption requests.\n");
        return;
    }

    int i, j;
    int index = 0;
    char choice[10];
    while (1) {
        system("cls");  

        printf("========== Adoption Review ==========\n");
        printf("Request %d of %d\n", index + 1, count);
        printf("Child ID    : %s\n", requests[index].childID);
        printf("Child Name  : %s\n", requests[index].childName);
        printf("Parent Email: %s\n", requests[index].parentEmail);
        printf("-------------------------------------\n");
        printf("Options: [A]pprove  [D]ecline  [N]ext  [P]revious  [B]ack to Menu\n");
        printf("Enter your choice: ");
        scanf(" %9s", choice);

        if (strcasecmp(choice, "A") == 0) {
            
            FILE *childrenFile = fopen("children.txt", "r");
            FILE *tempChildrenFile = fopen("children_temp.txt", "w");
            FILE *adoptedFile = fopen("adopted_children.txt", "a");
            FILE *notifFile = fopen("notifications.txt", "a"); // Add notification to file

            if (!childrenFile || !tempChildrenFile || !adoptedFile || !notifFile) {
                printf("Error opening necessary files.\n");
                if (childrenFile) fclose(childrenFile);
                if (tempChildrenFile) fclose(tempChildrenFile);
                if (adoptedFile) fclose(adoptedFile);
                if (notifFile) fclose(notifFile);
                return;
            }

            char line[512];
            while (fgets(line, sizeof(line), childrenFile)) {
                char currentID[10];
                sscanf(line, "%9[^|]", currentID);
                if (strcmp(currentID, requests[index].childID) == 0) {
                    fprintf(adoptedFile, "%s|%s|%s\n", 
                            requests[index].childID, 
                            requests[index].childName, 
                            requests[index].parentEmail);
                    // Notify parent of approval
                    fprintf(notifFile, "%s|%s|Approved\n", requests[index].parentEmail, requests[index].childName);
                } else {
                    fputs(line, tempChildrenFile);  
                }
            }

            fclose(childrenFile);
            fclose(tempChildrenFile);
            fclose(adoptedFile);
            fclose(notifFile);

            remove("children.txt");
            rename("children_temp.txt", "children.txt");

            
            for (j = index; j < count - 1; j++) {
                requests[j] = requests[j + 1];
            }
            count--;
            if (index >= count) index = count - 1;
            if (count == 0) break;

        } else if (strcasecmp(choice, "D") == 0) {
            
            FILE *notifFile = fopen("notifications.txt", "a");
            if (!notifFile) {
                printf("Error opening notifications file.\n");
                return;
            }

            
            fprintf(notifFile, "%s|%s|Declined\n", requests[index].parentEmail, requests[index].childName);
            fclose(notifFile);

            
            for (j = index; j < count - 1; j++) {
                requests[j] = requests[j + 1];
            }
            count--;
            if (index >= count) index = count - 1;
            if (count == 0) break;

        } else if (strcasecmp(choice, "N") == 0) {
            index = (index + 1) % count;

        } else if (strcasecmp(choice, "P") == 0) {
            index = (index - 1 + count) % count;

        } else if (strcasecmp(choice, "B") == 0) {
            break;

        } else {
            printf("Invalid input. Please try again.\n");
            Sleep(1500);
        }

        if (count == 0) {
            printf("All pending requests reviewed.\n");
            break;
        }
    }

    
    FILE *finalPending = fopen("pending_adoptions.txt", "w");
    if (!finalPending) {
        printf("Error writing back pending requests.\n");
        return;
    }
    for (i = 0; i < count; i++) {
        fprintf(finalPending, "%s|%s|%s\n", 
                requests[i].childID, 
                requests[i].childName, 
                requests[i].parentEmail);
    }
    fclose(finalPending);

    printf("Review process complete.\n");
    Sleep(2000);
}

//User menu funtions

int hasSubmittedApplication(const char *email) {
    char line[256], fileEmail[100];
    FILE *file = fopen("applications.txt", "r");

    if (!file) return 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, " %99[^|]", fileEmail);
        if (strcmp(fileEmail, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int hasSubmittedApplicationWithStatus(const char *email, char *status) {
    char line[256], fileEmail[100], fileStatus[50];
    FILE *file = fopen("applications.txt", "r");

    if (!file) return 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, " %99[^|]|%49[^\n]", fileEmail, fileStatus);
        if (strcmp(fileEmail, email) == 0) {
            strcpy(status, fileStatus);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void AdoptChildMenu() {
    int choice;

    do {
        clearScreen();  

       
        printf("====================================================================\n");
        printf("               _             _              _____ _     _ _     _ \n");
        printf("     /\\      | |           | |            / ____| |   (_) |   | |\n");
        printf("    /  \\   __| | ___  _ __ | |_    __ _  | |    | |__  _| | __| |\n");
        printf("   / /\\ \\ / _` |/ _ \\| '_ \\| __|  / _` | | |    | '_ \\| | |/ _` |\n");
        printf("  / ____ \\ (_| | (_) | |_) | |_  | (_| | | |____| | | | | | (_| |\n");
        printf(" /_/    \\_\\__,_|\\___/| .__/ \\__|  \\__,_|  \\_____|_| |_|_|_|\\__,_|\n");
        printf("                     | |                                        \n");
        printf("                     |_|                                        \n");
        printf("====================================================================\n");

        
        printf("   [1] View All Children\n");
        printf("   [2] Search / Filter Children\n");
        printf("   [3] Adopt a Child\n");
        printf("   [4] Return to Previous Menu\n");
        printf("--------------------------------------------------------------------\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number between 1 and 4.\n");
            while (getchar() != '\n');
            Sleep(1500);
            clearScreen();
            continue;
        }

        clearScreen();

        switch (choice) {
            case 1:
                viewAllChildren();
                break;

            case 2:
                filterChildren();
                break;

            case 3:
                adoptChild();
                break;

            case 4:
                printf("Returning to previous menu...\n");
                Sleep(1000);
                break;

            default:
                printf("Invalid choice. Please choose between 1 and 4.\n");
                Sleep(1500);
        }

        clearScreen();

    } while (choice != 4);
}


void filterChildren() {
    FILE *file = fopen("children.txt", "r");
    FILE *pendingFile = fopen("pending_adoptions.txt", "r");
    char line[512];
    int choice, matchCount = 0;
    char search[50];
    int i, j;
    char pendingIDs[MAX_CHILDREN][10];
    int pendingCount = 0;
    Child matches[MAX_MATCHES];

    if (!file) {
        printf("Unable to open children file.\n");
        return;
    }

    if (pendingFile) {
        while (fgets(line, sizeof(line), pendingFile)) {
            sscanf(line, "%9[^|]", pendingIDs[pendingCount++]);
        }
        fclose(pendingFile);
    }

    while (1) {
        printf("Filter by:\n1. Blood Type\n2. Age\n3. Gender\nChoice: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    }

    getchar(); 

    while (1) {
        printf("Enter search term: ");
        fgets(search, sizeof(search), stdin);
        search[strcspn(search, "\n")] = '\0'; // Remove newline

        if (choice == 1) {
            if (strcmp(search, "A+") != 0 && strcmp(search, "A-") != 0 &&
                strcmp(search, "B+") != 0 && strcmp(search, "B-") != 0 &&
                strcmp(search, "AB+") != 0 && strcmp(search, "AB-") != 0 &&
                strcmp(search, "O+") != 0 && strcmp(search, "O-") != 0) {
                printf("Invalid blood type. Try one of: A+, A-, B+, B-, AB+, AB-, O+, O-.\n");
                continue;
            }
        } else if (choice == 2) {
            int validAge = 1;
            for (i = 0; i < strlen(search); i++) {
                if (!isdigit(search[i])) {
                    validAge = 0;
                    break;
                }
            }
            if (!validAge || atoi(search) <= 0) {
                printf("Invalid age. Please enter a positive whole number.\n");
                continue;
            }
        } else if (choice == 3) {
            if (strcasecmp(search, "Male") != 0 && strcasecmp(search, "Female") != 0) {
                printf("Invalid gender. Please enter 'Male' or 'Female'.\n");
                continue;
            }
        }
        break;
    }

    printf("\n%-4s %-10s %-20s %-5s %-10s %-10s %-10s\n", "No", "ID", "Name", "Age", "Gender", "BloodType", "Adopted");
    printf("-------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        Child c;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               c.id, c.name, c.gender, c.birthDate, &c.age, &c.height, &c.weight, &c.adopted,
               c.bloodType, c.allergies, c.medicalConditions, c.educationLevel,
               c.hobbies, c.languagesSpoken);

        int isPending = 0;
        for (j = 0; j < pendingCount; j++) {
            if (strcmp(c.id, pendingIDs[j]) == 0) {
                isPending = 1;
                break;
            }
        }

        if (isPending) continue;

        int match = 0;
        if (choice == 1 && strcasecmp(c.bloodType, search) == 0)
            match = 1;
        else if (choice == 2 && atoi(search) == c.age)
            match = 1;
        else if (choice == 3 && strcasecmp(c.gender, search) == 0)
            match = 1;

        if (match && matchCount < MAX_MATCHES) {
            matches[matchCount++] = c;
            printf("%-4d %-10s %-20s %-5d %-10s %-10s %-10s\n",
                   matchCount, c.id, c.name, c.age, c.gender,
                   c.bloodType, c.adopted ? "Yes" : "No");
        }
    }

    fclose(file);

    if (matchCount == 0) {
        printf("No matching children found.\n");
        system("pause");
        return;
    }

    int selection;
    while (1) {
        printf("\nEnter the number of a child to view full details (0 to cancel): ");
        if (scanf("%d", &selection) != 1 || selection < 0 || selection > matchCount) {
            printf("Invalid selection. Please enter a number between 0 and %d.\n", matchCount);
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    if (selection == 0) {
        printf("Cancelled.\n");
        return;
    }

    Child c = matches[selection - 1];
    printf("\n========= Child Profile =========\n");
    printf("ID: %s\n", c.id);
    printf("Name: %s\n", c.name);
    printf("Gender: %s\n", c.gender);
    printf("Birth Date: %s\n", c.birthDate);
    printf("Age: %d\n", c.age);
    printf("Height: %.2f cm\n", c.height);
    printf("Weight: %.2f kg\n", c.weight);
    printf("Blood Type: %s\n", c.bloodType);
    printf("Adopted: %s\n", c.adopted ? "Yes" : "No");
    printf("Allergies: %s\n", c.allergies);
    printf("Medical Conditions: %s\n", c.medicalConditions);
    printf("Education Level: %s\n", c.educationLevel);
    printf("Hobbies: %s\n", c.hobbies);
    printf("Languages Spoken: %s\n", c.languagesSpoken);
    printf("=================================\n");

    system("pause");
}



void adoptChild() {
    FILE *file;
    FILE *pendingFile;
    char filePath[MAX_PATH];
    char line[512], childID[10];
    int found = 0;
    char pendingIDs[MAX_CHILDREN][10];
    int pendingCount = 0;

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\children.txt");

    file = fopen(filePath, "r");
    if (!file) {
        printf("No children available.\n");
        return;
    }

    
    pendingFile = fopen("pending_adoptions.txt", "r");
    if (pendingFile) {
        while (fgets(line, sizeof(line), pendingFile)) {
            sscanf(line, "%9[^|]", pendingIDs[pendingCount++]);
        }
        fclose(pendingFile);
    }

    Child tempChildren[MAX_CHILDREN];
    int total = 0;
    int j;
    printf("=========== Available Children ===========\n");
    printf("%-10s %-20s %-5s\n", "Child ID", "Name", "Age");
    printf("------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        Child child;
        if (sscanf(line, "%7[^|]|%49[^|]|%9[^|]|%19[^|]|%d|%f|%f|%d|%4[^|]|%99[^|]|%199[^|]|%49[^|]|%99[^|]|%99[^\n]",
                   child.id, child.name, child.gender, child.birthDate, &child.age, &child.height, &child.weight,
                   &child.adopted, child.bloodType, child.allergies, child.medicalConditions,
                   child.educationLevel, child.hobbies, child.languagesSpoken) == 14) {
            if (child.adopted == 0) {
                int isPending = 0;
                for (j = 0; j < pendingCount; j++) {
                    if (strcmp(child.id, pendingIDs[j]) == 0) {
                        isPending = 1;
                        break;
                    }
                }

                if (!isPending) {
                    printf("%-10s %-20s %-5d\n", child.id, child.name, child.age);
                    tempChildren[total++] = child;
                }
            }
        }
    }

    fclose(file);

    if (total == 0) {
    printf("\nNo adoptable children found.\n");
    printf("Press Enter to return to the menu...");
    getchar(); 
    getchar(); 
    return;
}

    printf("\nEnter the Child ID you want to adopt (or 'b' to go back): ");
    scanf(" %9s", childID);

    if (strcmp(childID, "b") == 0 || strcmp(childID, "B") == 0) {
        printf("Returning to previous menu...\n");
        Sleep(1500);
        return;
    }

    int i;
    for (i = 0; i < total; i++) {
        if (strcmp(tempChildren[i].id, childID) == 0) {
            found = 1;
            printf("\n========= Child Details =========\n");
            printf("ID: %s\n", tempChildren[i].id);
            printf("Name: %s\n", tempChildren[i].name);
            printf("Gender: %s\n", tempChildren[i].gender);
            printf("Birth Date: %s\n", tempChildren[i].birthDate);
            printf("Age: %d\n", tempChildren[i].age);
            printf("Height: %.2f cm\n", tempChildren[i].height);
            printf("Weight: %.2f kg\n", tempChildren[i].weight);
            printf("Blood Type: %s\n", tempChildren[i].bloodType);
            printf("Allergies: %s\n", tempChildren[i].allergies);
            printf("Medical Conditions: %s\n", tempChildren[i].medicalConditions);
            printf("Education Level: %s\n", tempChildren[i].educationLevel);
            printf("Hobbies: %s\n", tempChildren[i].hobbies);
            printf("Languages Spoken: %s\n", tempChildren[i].languagesSpoken);
            printf("=================================\n");

            char confirm[10];
            printf("\nDo you want to adopt this child? (yes/no): ");
            scanf(" %9s", confirm);

            if (strcmp(confirm, "yes") == 0 || strcmp(confirm, "YES") == 0) {
                FILE *pendingFile = fopen("pending_adoptions.txt", "a");
                if (!pendingFile) {
                    printf("Error: Could not save pending adoption request.\n");
                    return;
                }

                fprintf(pendingFile, "%s|%s|%s\n", tempChildren[i].id, tempChildren[i].name, loggedInUser.email);
                fclose(pendingFile);

                printf("\nYour adoption request for child %s has been submitted for admin approval.\n", tempChildren[i].name);
            } else {
                printf("\nAdoption cancelled.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("\nNo available child found with ID: %s\n", childID);
    }

    Sleep(3000);
}



void viewMyAdoptedChildren() {
    char filePath[MAX_PATH], line[256];
    FILE *file;

    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, filePath);
    strcat(filePath, "\\adopted_children.txt");

    file = fopen(filePath, "r");
    if (!file) {
        printf("No adopted children found or unable to open the file.\n");
        Sleep(2000);
        return;
    }

    int found = 0;
    printf("\n======== Your Adopted Children ========\n");

    while (fgets(line, sizeof(line), file)) {
        char id[10], name[50], parentEmail[100];

        if (sscanf(line, "%9[^|]|%49[^|]|%99[^\n]", id, name, parentEmail) == 3) {
            if (strcmp(parentEmail, loggedInUser.email) == 0) {
                found = 1;
                printf("Child ID   : %s\n", id);
                printf("Name       : %s\n", name);
                printf("----------------------------------\n");
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("You have not adopted any children yet.\n");
    }

    printf("\nPress Enter to return to the Adoption Menu...");
    getchar(); 
    getchar(); 
    clearScreen();
}


void submitApplication() {
    if (hasSubmittedApplication(loggedInUser.email)) {
        printf("You have already submitted an application.\n");
        Sleep(2000);
        return;
    }

    printf("===== Submit Adoption Application =====\n");
    printf("Registered User Information:\n");
    printf("Name: %s %s\n", loggedInUser.firstName, loggedInUser.lastName);
    printf("Email: %s\n", loggedInUser.email);
    printf("Age: %d\n", loggedInUser.age);
    printf("\n(Enter 0 at any prompt to cancel and go back)\n\n");

    getchar(); 

   
    #define GET_INPUT(prompt, field) do { \
        printf(prompt); \
        fgets(field, sizeof(field), stdin); \
        field[strcspn(field, "\n")] = 0; \
        if (strcmp(field, "0") == 0) { \
            printf("Application cancelled.\n"); \
            Sleep(1500); \
            return; \
        } \
    } while (strlen(field) == 0)

    
    GET_INPUT("Address: ", loggedInUser.address);
    GET_INPUT("Occupation: ", loggedInUser.occupation);
    GET_INPUT("Phone: ", loggedInUser.phone);
    GET_INPUT("Marital Status: ", loggedInUser.maritalStatus);

    
    while (1) {
        char buffer[20];
        printf("Household Size: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (strcmp(buffer, "0\n") == 0) {
            printf("Application cancelled.\n");
            Sleep(1500);
            return;
        }
        if (sscanf(buffer, "%d", &loggedInUser.householdSize) == 1 && loggedInUser.householdSize > 0) {
            break;
        } else {
            printf("Invalid input. Please enter a positive number.\n");
        }
    }

    GET_INPUT("Do you have a criminal record? (Yes/No): ", loggedInUser.criminalRecord);
    GET_INPUT("Housing Status (Owned/Rented): ", loggedInUser.housingStatus);
    GET_INPUT("Do you already have children? (Yes/No): ", loggedInUser.hasChildren);
    GET_INPUT("Why do you want to adopt? (Max 200 characters): ", loggedInUser.reason);

    strcpy(loggedInUser.status, "Pending");

    
    FILE *appFile = fopen("applications.txt", "a");
    if (appFile) {
        fprintf(appFile, "%s|%s\n", loggedInUser.email, loggedInUser.status);
        fclose(appFile);
    } else {
        printf("Warning: Could not save application status.\n");
    }

   
    FILE *detailsFile = fopen("applicationDetails.txt", "a");
    if (detailsFile) {
        fprintf(detailsFile, "%s|%s|%s|%d|%s|%s|%s|%s|%d|%s|%s|%s|%s\n",
            loggedInUser.email,
            loggedInUser.firstName,
            loggedInUser.lastName,
            loggedInUser.age,
            loggedInUser.address,
            loggedInUser.occupation,
            loggedInUser.phone,
            loggedInUser.maritalStatus,
            loggedInUser.householdSize,
            loggedInUser.criminalRecord,
            loggedInUser.housingStatus,
            loggedInUser.hasChildren,
            loggedInUser.reason
        );
        fclose(detailsFile);
    } else {
        printf("Warning: Could not save detailed application info.\n");
    }

    printf("\nApplication submitted successfully! Status: %s\n", loggedInUser.status);
    Sleep(3000);
    clearScreen();

    #undef GET_INPUT
}


int main() {
    int choice;
    int loggedIn = 0;

    while (1) {
        clearScreen(); // Optional: clears the console if implemented
        printf("=====================================================\n");
        printf("               _             _   _                _____           _            \n");
        printf("      /\      | |           | | (_)              / ____|         | |           \n");
        printf("     /  \\   __| | ___  _ __ | |_ _  ___  _ __   | |     ___ _ __ | |_ ___ _ __ \n");
        printf("    / /\ \\ / _` |/ _ \\| '_ \\| __| |/ _ \\| '_ \\  | |    / _ \\ '_ \\| __/ _ \\ '__|\n");
        printf("   / ____ \\ (_| | (_) | |_) | |_| | (_) | | | | | |___|  __/ | | | ||  __/ |   \n");
        printf("  /_/    \\_\\__,_|\\___/| .__/ \\__|_|\\___/|_| |_|  \\_____\\___|_| |_|\__\\___|_|    \n");
        printf("                     | |                                                   \n");
        printf("                     |_|                                                   \n");
        printf("=====================================================\n");
        printf("   [1] Register                                       \n");
        printf("   [2] Login as User                                  \n");
        printf("   [3] Login as Admin                                 \n");
        printf("   [4] Exit                                           \n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number between 1 and 4.\n");
            while (getchar() != '\n'); // clear invalid input
            Sleep(1500);
            continue;
        }

        switch (choice) {
            case 1:
                signUp();
                break;

            case 2:
                loggedIn = loginUser(); 
                if (loggedIn) {
                    adoptionMenu(); 
                }
                break;

            case 3:
                AdminLogin();  
                break;

            case 4:
                printf("\nThank you for using the Child Adoption Center.\n");
                printf("Exiting...");
                Sleep(1500);
                exit(0);  
                break;

            default:
                printf("\nInvalid choice. Please select a number between 1 and 4.\n");
                Sleep(1500);
                break;
        }
    }

    return 0;
}


