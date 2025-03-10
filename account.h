#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    char username[30];
    double balance;
} Account;

int createAccount(const char* username, double initialBalance);
double getBalance(const char* username);
int updateBalance(const char* username, double newBalance);
void displayBalance(const char* username);
void handleDeposit(const char* username);
void handleWithdrawal(const char* username);

#endif /* ACCOUNT_H */
