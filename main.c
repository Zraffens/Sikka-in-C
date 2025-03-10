#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "account.h"
#include "transaction.h"
#include "ui.h"

int main() {
    int choice, loggedIn = 0;
    User currentUser;
    
    displayWelcomeBanner();
    
    while (1) {
        if (!loggedIn) {
            displayAuthMenu();
            scanf("%d", &choice);
            clearInputBuffer();
            
            switch (choice) {
                case 1: // Login
                    if (loginUser(&currentUser)) {
                        loggedIn = 1;
                        printf("\nLogin successful! Welcome, %s!\n", currentUser.name);
                    } else {
                        printf("\nLogin failed. Please try again.\n");
                    }
                    break;
                case 2: // Register
                    if (registerUser()) {
                        printf("\nRegistration successful! Please login.\n");
                    } else {
                        printf("\nRegistration failed. Please try again.\n");
                    }
                    break;
                case 3: // Exit
                    printf("\nThank you for using our Payment Service. Goodbye!\n");
                    return 0;
                default:
                    printf("\nInvalid choice. Please try again.\n");
            }
        } else {
            displayMainMenu(currentUser.name);
            scanf("%d", &choice);
            clearInputBuffer();
            
            switch (choice) {
                case 1: // Check Balance
                    displayBalance(currentUser.username);
                    break;
                case 2: // Deposit Money
                    handleDeposit(currentUser.username);
                    break;
                case 3: // Withdraw Money
                    handleWithdrawal(currentUser.username);
                    break;
                case 4: // Transfer Money
                    handleTransfer(currentUser.username);
                    break;
                case 5: // Pay Bills
                    handleBillPayment(currentUser.username);
                    break;
                case 6: // Transaction History
                    displayTransactionHistory(currentUser.username);
                    break;
                case 7: // Update Profile
                    updateUserProfile(&currentUser);
                    break;
                case 8: // Logout
                    loggedIn = 0;
                    printf("\nYou have been logged out. Thank you!\n");
                    break;
                case 9: // Exit
                    printf("\nThank you for using our Payment Service. Goodbye!\n");
                    return 0;
                default:
                    printf("\nInvalid choice. Please try again.\n");
            }
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    return 0;
}
