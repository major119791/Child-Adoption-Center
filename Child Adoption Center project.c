#include<stdio.h>
#include<stdlib.h>

typedef struct Child {
    char name[100];
    int age;
    float height;
    float weight;
    char race[100];
    char birthDate[100];
    char gender[100];
}Child;
//testing
//new
typedef struct Parent {
    int age;
    char name[100];
    char address[200];
    char occupation[100];
    char phoneNum[15];
}Parent;

void Menu() {

    int choice;
    do {
        printf("1. Adopt a Child\n");
        printf("2. View Children\n");
        printf("3. Return a Child\n");
        printf("4. Child Adopted\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
    } while (choice != 5);
}
void GenerateUserID(User *newUser) {
    srand(time(NULL));  
    newUser->userID = 100000 + rand() % 900000; 
}
void SignUp() {
    User newUser;
    FILE *file = fopen("users.txt", "a"); 
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("========= Sign Up =========\n\n");
    printf("Enter Username: ");
    scanf("%s", newUser.username);
    printf("Enter Password: ");
    scanf("%s", newUser.password);
    GenerateUserID(&newUser);
    printf("\nAccount Created Successfully!\n");
    printf("Your User ID: %d\n", newUser.userID);
    printf("Please remember this ID for login.\n");
    fprintf(file, "%d %s %s\n", newUser.userID, newUser.username, newUser.password);
    fclose(file);
}
void Userlogin(){
	int choice;
	char name[100], pass[100];
	do {
		printf("1. Login\n");
		printf("2. Register\n");
		printf("3. Admin\n");
		printf("4 Exit\n");
		printf("Choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: 
			Menu();
			break;
			case 2:
				SignUp(name, pass);
			break;
		}
	}while(choice != 4);
}
void Useradmin() {
}
void AdminMenu(){
}
int main() {
Userlogin();
return 0;	
}

