#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user.h"
#include "account.h" // Add this include to resolve the createAccount function

#define USERS_FILE "users.txt"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void secureInput(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
}

int userExists(const char* username) {
    FILE* file = fopen(USERS_FILE, "r");
    if (file == NULL) return 0;
    
    User tempUser;
    while (fscanf(file, "%s %s %s %s %s %s", tempUser.username, tempUser.password, 
                 tempUser.name, tempUser.email, tempUser.phone, tempUser.address) == 6) {
        if (strcmp(username, tempUser.username) == 0) {
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return 0;
}

int validateUser(const char* username, const char* password, User* user) {
    FILE* file = fopen(USERS_FILE, "r");
    if (file == NULL) return 0;
    
    while (fscanf(file, "%s %s %s %s %s %s", user->username, user->password, 
                 user->name, user->email, user->phone, user->address) == 6) {
        if (strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return 0;
}

int registerUser() {
    User newUser;
    FILE* file;
    
    printf("\n===== REGISTER NEW ACCOUNT =====\n");
    
    printf("Username (no spaces): ");
    scanf("%s", newUser.username);
    clearInputBuffer();
    
    if (userExists(newUser.username)) {
        printf("Username already exists. Please choose a different one.\n");
        return 0;
    }
    
    printf("Password (no spaces): ");
    scanf("%s", newUser.password);
    clearInputBuffer();
    
    printf("Full Name (use underscores_for_spaces): ");
    scanf("%s", newUser.name);
    clearInputBuffer();
    
    printf("Email: ");
    scanf("%s", newUser.email);
    clearInputBuffer();
    
    printf("Phone: ");
    scanf("%s", newUser.phone);
    clearInputBuffer();
    
    printf("Address (use_underscores_for_spaces): ");
    scanf("%s", newUser.address);
    clearInputBuffer();
    
    file = fopen(USERS_FILE, "a");
    if (file == NULL) {
        printf("Error opening users file!\n");
        return 0;
    }
    
    fprintf(file, "%s %s %s %s %s %s\n", 
            newUser.username, newUser.password, newUser.name, 
            newUser.email, newUser.phone, newUser.address);
    fclose(file);
    
    // Create initial account with 0 balance
    createAccount(newUser.username, 0.0);
    
    return 1;
}

int loginUser(User* user) {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    printf("\n===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);
    clearInputBuffer();
    
    printf("Password: ");
    scanf("%s", password);
    clearInputBuffer();
    
    return validateUser(username, password, user);
}

int updateUserProfile(User* currentUser) {
    User users[100];
    int userCount = 0;
    FILE* file;
    
    printf("\n===== UPDATE PROFILE =====\n");
    
    // Read all users into array
    file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        printf("Error opening users file!\n");
        return 0;
    }
    
    while (fscanf(file, "%s %s %s %s %s %s", users[userCount].username, users[userCount].password, 
                 users[userCount].name, users[userCount].email, users[userCount].phone, 
                 users[userCount].address) == 6 && userCount < 100) {
        userCount++;
    }
    fclose(file);
    
    // Find and update current user
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, currentUser->username) == 0) {
            int choice;
            printf("What would you like to update?\n");
            printf("1. Password\n");
            printf("2. Name\n");
            printf("3. Email\n");
            printf("4. Phone\n");
            printf("5. Address\n");
            printf("6. Go back\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            clearInputBuffer();
            
            switch (choice) {
                case 1:
                    printf("New Password: ");
                    scanf("%s", users[i].password);
                    clearInputBuffer();
                    break;
                case 2:
                    printf("New Name (use_underscores_for_spaces): ");
                    scanf("%s", users[i].name);
                    clearInputBuffer();
                    break;
                case 3:
                    printf("New Email: ");
                    scanf("%s", users[i].email);
                    clearInputBuffer();
                    break;
                case 4:
                    printf("New Phone: ");
                    scanf("%s", users[i].phone);
                    clearInputBuffer();
                    break;
                case 5:
                    printf("New Address (use_underscores_for_spaces): ");
                    scanf("%s", users[i].address);
                    clearInputBuffer();
                    break;
                case 6:
                    return 1;
                default:
                    printf("Invalid choice!\n");
                    return 0;
            }
            
            // Update the current user struct with the new data
            strcpy(currentUser->password, users[i].password);
            strcpy(currentUser->name, users[i].name);
            strcpy(currentUser->email, users[i].email);
            strcpy(currentUser->phone, users[i].phone);
            strcpy(currentUser->address, users[i].address);
            
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("User not found in database!\n");
        return 0;
    }
    
    // Write all users back to file
    file = fopen(USERS_FILE, "w");
    if (file == NULL) {
        printf("Error opening users file for writing!\n");
        return 0;
    }
    
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %s %s %s %s\n", 
                users[i].username, users[i].password, users[i].name, 
                users[i].email, users[i].phone, users[i].address);
    }
    fclose(file);
    
    printf("Profile updated successfully!\n");
    return 1;
}
