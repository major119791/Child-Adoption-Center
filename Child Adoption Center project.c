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
    User user;
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Users.txt", "a");
    if (!file) {
        printf("Error: Could not open user file.\n");
        return;
    }

    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        fclose(file);
        return;
    }

    while (1) {
        int choice;
        printf("========= Registration =========\n");
        printf("1. Sign Up\n");
        printf("2. Back\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number (1 or 2).\n");
            Sleep(1500);
            while (getchar() != '\n'); // clear buffer
            clearScreen();
            continue;
        }

        clearScreen();

        if (choice == 2) {
            printf("Going back...\n");
            Sleep(1500);
            clearScreen();
            fclose(file);
            return;
        } else if (choice == 1) {
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

            clearScreen();

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
            userCount++;

            printf("\nAccount Created Successfully!\n");
            Sleep(1500);
            clearScreen();
            break;
        } else {
            printf("\nInvalid choice. Please select 1 (Sign Up) or 2 (Back).\n");
            Sleep(1500);
            clearScreen();
        }
    }
}

int login() {
    int i;
    char email[100], pass[50];
    int choice;

    while (1) {
        printf("\n====== User Login ======\n");
        printf("1. Enter Login Credentials\n");
        printf("2. Back\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number (1 or 2).\n");
            Sleep(1500);
            while (getchar() != '\n'); // clear input buffer
            clearScreen();
            continue;
        }

        if (choice == 2) {
            printf("Going back...\n");
            Sleep(1500);
            clearScreen();
            return 0;  
        } else if (choice == 1) {
            printf("\nEnter Email: ");
            scanf("%s", email);
            printf("Enter Password: ");
            scanf("%s", pass);
            clearScreen();

            int found = 0;
            for (i = 0; i < userCount; i++) {
                if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, pass) == 0) {
                    printf("\nLogin Successful! Welcome, %s %s!\n", users[i].firstName, users[i].lastName);
                    return 1;  
                }
            }

            printf("\nInvalid credentials. Please try again.\n");
            Sleep(1500);
            clearScreen();
        } else {
            printf("\nInvalid choice. Please select 1 (Login) or 2 (Back).\n");
            Sleep(1500);
            clearScreen();
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
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Children.txt", "a");
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
    while (scanf(" %[^\n]", child.name) != 1 || strlen(child.name) == 0) {
        printf("Invalid input. Please enter a valid child name.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Age: ");
    while (scanf(" %d", &child.age) != 1 || child.age <= 0) {
        printf("Invalid age. Please enter a valid age greater than 0.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Gender (M/F): ");
    while (scanf(" %s", child.gender) != 1 || (child.gender[0] != 'M' && child.gender[0] != 'F')) {
        printf("Invalid gender. Please enter M or F.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Birth Date (YYYY-MM-DD): ");
    while (scanf(" %s", child.birthDate) != 1 || strlen(child.birthDate) != 10) {
        printf("Invalid birth date format. Please use YYYY-MM-DD.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Height (cm): ");
    while (scanf(" %f", &child.height) != 1 || child.height <= 0) {
        printf("Invalid height. Please enter a valid height greater than 0.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Weight (kg): ");
    while (scanf(" %f", &child.weight) != 1 || child.weight <= 0) {
        printf("Invalid weight. Please enter a valid weight greater than 0.\n");
        while (getchar() != '\n'); 
    }

    printf("Enter Blood Type: ");
    while (scanf(" %s", child.bloodType) != 1 || strlen(child.bloodType) == 0) {
        printf("Invalid blood type. Please enter a valid blood type.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Allergies (if any): ");
    while (scanf(" %[^\n]", child.allergies) != 1) {
        printf("Invalid input. Please enter valid allergies.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Medical Conditions (if any): ");
    while (scanf(" %[^\n]", child.medicalConditions) != 1) {
        printf("Invalid input. Please enter valid medical conditions.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Education Level: ");
    while (scanf(" %[^\n]", child.educationLevel) != 1) {
        printf("Invalid input. Please enter a valid education level.\n");
        while (getchar() != '\n'); 
    }

    printf("Enter Hobbies & Interests: ");
    while (scanf(" %[^\n]", child.hobbies) != 1) {
        printf("Invalid input. Please enter valid hobbies.\n");
        while (getchar() != '\n');  
    }

    printf("Enter Languages Spoken: ");
    while (scanf(" %[^\n]", child.languagesSpoken) != 1) {
        printf("Invalid input. Please enter valid languages spoken.\n");
        while (getchar() != '\n');  
    }

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
    childCount++;  
    Sleep(1500);
    clearScreen();
}

void loadChildren() {
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Children.txt", "r");
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
        
        // Skip over adopted children (adopted == 1)
        if (children[i].adopted == 1) {
            continue;
        }

        // Only count and display valid profiles
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

        // Only display adopted children (adopted == 1)
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
        }
    } while (choice != 6);
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

void userLogin() {
    int choice;
    
    do {
    	printf("====== Welcome to Adoption Center ======\n");
        printf("\n1. Login\n2. Register\n3. Admin\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        clearScreen();
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
    FILE *file = fopen("C:\\Users\\L65X15W07\\Desktop\\Users.txt", "r");
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
	loadUsers();
	loadChildren();
    userLogin();
    return 0;
}
