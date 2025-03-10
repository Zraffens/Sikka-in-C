#ifndef USER_H
#define USER_H

#define MAX_USERNAME 30
#define MAX_PASSWORD 30
#define MAX_NAME 50
#define MAX_EMAIL 50
#define MAX_PHONE 15
#define MAX_ADDRESS 100

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
    char email[MAX_EMAIL];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
} User;

int registerUser();
int loginUser(User* user);
int updateUserProfile(User* user);
int userExists(const char* username);
int validateUser(const char* username, const char* password, User* user);
void clearInputBuffer();
void secureInput(char* buffer, int size);

#endif /* USER_H */
