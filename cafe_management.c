#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_ORDERS 100

// Structure to represent a menu item
typedef struct {
    int id;
    char name[50];
    float price;
} MenuItem;

// Structure to represent an order
typedef struct {
    int itemId;
    int quantity;
} OrderItem;

// Function prototypes
void displayMenu(MenuItem menu[], int size);
void takeOrder(MenuItem menu[], int size, OrderItem order[], int *orderCount);
float calculateTotal(MenuItem menu[], int size, OrderItem order[], int orderCount);

int main() {
    int menuSize = 3; // Number of items in the menu
    MenuItem menu[MAX_ITEMS] = {
        {1, "Coffee", 3.50},
        {2, "Tea", 2.75},
        {3, "Sandwich", 5.00}
    };

    OrderItem order[MAX_ORDERS];
    int orderCount = 0;

    int choice;
    do {
        printf("\nCafe Management System\n");
        printf("1. Display Menu\n");
        printf("2. Take Order\n");
        printf("3. Calculate Total\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(menu, menuSize);
                break;
            case 2:
                takeOrder(menu, menuSize, order, &orderCount);
                break;
            case 3:
                printf("Total Bill: $%.2f\n", calculateTotal(menu, menuSize, order, orderCount));
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}

void displayMenu(MenuItem menu[], int size) {
    printf("\n--- Menu ---\n");
    for (int i = 0; i < size; i++) {
        printf("ID: %d, Name: %s, Price: $%.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

void takeOrder(MenuItem menu[], int size, OrderItem order[], int *orderCount) {
    int id, quantity;
    printf("\nEnter item ID and quantity (0 to stop):\n");
    while (1) {
        printf("Item ID: ");
        scanf("%d", &id);
        if (id == 0) break;

        printf("Quantity: ");
        scanf("%d", &quantity);

        // Validate item ID
        int validItem = 0;
        for (int i = 0; i < size;i++ ) {
            if (menu[i].id == id) {
                validItem = 1;
                break;
            }
        }
        
        if (validItem && quantity > 0) {
            if (*orderCount < MAX_ORDERS) {
                order[*orderCount].itemId = id;
                order[*orderCount].quantity = quantity;
                (*orderCount)++;
            } else {
                printf("Order limit reached. Cannot add more items.\n");
                break;
            }
        } else {
            printf("Invalid item ID or quantity. Please try again.\n");
        }
    }
}

float calculateTotal(MenuItem menu[], int size, OrderItem order[], int orderCount) {
    float total = 0.0;
    for (int i = 0; i < orderCount; i++) {
        int itemFound = 0;
        for (int j = 0; j < size; j++) {
            if (menu[j].id == order[i].itemId) {
                total += menu[j].price * order[i].quantity;
                itemFound = 1;
                break;
            }
        }
        if (!itemFound) {
            printf("Item with ID %d not found in the menu.\n", order[i].itemId);
        }
    }
    return total;
}

