#include <stdio.h>
#include <string.h>

void title() 
{
    printf("\n");
    printf("=======================================\n");
    printf("         Emart - Sky-Market            \n");
    printf("=======================================\n\n");
}

void password(char user[20], char pass[20])
{
    while(1){
        printf("\n\n Enter Username: ");
        scanf("%s", user);
        
        printf("\n Enter Password: ");
        scanf("%s", pass);
        
        if(strcmp(user, "admin")==0 && strcmp(pass, "1234")==0){
            printf("Login successful! Welcome Admin.\n");
            break;
        }
        else if(strcmp(user, "customer")==0 && strcmp(pass, "4321")==0){
            printf("Login successful! Welcome Customer.\n");
            break;
        }
        else{
            printf("Wrong Password or Username try again.\n");
        }
    }
}

// Main Store Inventory Global Variables
int sno[100];
char name[100][50];
int stock[100];
int price[100];
int total_items = 0; 

// Global Variables for the Shopping Cart
int cart_sno[100];
char cart_name[100][50];
int cart_qty[100];
int cart_price[100];
int cart_count = 0; 

void restock() {
    char repeat;

    do {
        printf("Enter the S.no of the Item you wish to add: ");
        scanf("%d", &sno[total_items]);

        printf("Enter the Name of the Item you wish to add: ");
        scanf("%s", name[total_items]); 

        printf("Enter the stock of the Item you wish to add: ");
        scanf("%d", &stock[total_items]);

        printf("Enter the price of the Item you wish to add: ");
        scanf("%d", &price[total_items]);

        total_items++; 

        printf("Do you wish to add another Item (Type Y or N): ");
        scanf(" %c", &repeat); 

    } while ((repeat == 'Y' || repeat == 'y') && total_items < 100);
}

// Forward declaring functions so the compiler knows they exist below
void cart();
void billing();

void inventory() {
    char repeat_selection;
    int input_sno;

    do {
        printf("\n====================================================\n");
        printf("               Welcome to Inventory                 \n");
        printf("====================================================\n");
        printf("%-10s %-20s %-10s %-10s\n", "S.No", "Item Name", "Stock", "Price");
        printf("----------------------------------------------------\n");
        
        for (int j = 0; j < total_items; j++) {
            printf("%-10d %-20s %-10d %-10d\n", sno[j], name[j], stock[j], price[j]);
        }
        printf("----------------------------------------------------\n");

        if (total_items == 0) {
            printf("\nThere are no items in stock yet! Admin needs to log in and restock.\n");
            return; 
        }

        printf("\nEnter the S.No of the item you want to buy: ");
        scanf("%d", &input_sno);

        // Find match index in stock array
        int found_index = -1;
        for (int j = 0; j < total_items; j++) {
            if (sno[j] == input_sno) {
                found_index = j;
                break;
            }
        }

        if (found_index != -1) {
            cart_sno[cart_count] = sno[found_index];
            strcpy(cart_name[cart_count], name[found_index]);
            cart_price[cart_count] = price[found_index];

            printf("How many '%s' do you want to buy? ", cart_name[cart_count]);
            scanf("%d", &cart_qty[cart_count]);

            cart_count++;
            printf("Added to cart successfully!\n");
        } else {
            printf("Item not found in inventory!\n");
        }

        printf("\nDo you wish to select another item? (Y/N): ");
        scanf(" %c", &repeat_selection);

    } while (repeat_selection == 'Y' || repeat_selection == 'y');

    cart();
}

void cart() {
    int final_total = 0;
    char move_to_billing;

    printf("\n====================================================\n");
    printf("                 YOUR SHOPPING CART                 \n");
    printf("====================================================\n");
    printf("%-10s %-20s %-10s %-10s %-10s\n", "S.No", "Item Name", "Qty", "Price", "Subtotal");
    printf("----------------------------------------------------\n");

    for (int j = 0; j < cart_count; j++) {
        int subtotal = cart_qty[j] * cart_price[j];
        printf("%-10d %-20s %-10d %-10d %-10d\n", 
               cart_sno[j], cart_name[j], cart_qty[j], cart_price[j], subtotal);
        
        final_total += subtotal;
    }

    printf("----------------------------------------------------\n");
    printf("%-40s Rs %d\n", "FINAL TOTAL:", final_total);
    printf("====================================================\n");

    printf("\nDo you want to proceed to billing? (Y/N): ");
    scanf(" %c", &move_to_billing);

    if (move_to_billing == 'Y' || move_to_billing == 'y') {
        billing();
    }
}

void billing() {
    char customer_name[50];
    char customer_phone[15];
    int grand_total = 0;

    printf("\n====================================================\n");
    printf("                  CHECKOUT & BILLING                \n");
    printf("====================================================\n");
    
    printf("Enter Customer Name: ");
    scanf("%s", customer_name);
    printf("Enter Phone Number: ");
    scanf("%s", customer_phone);

    printf("\n====================================================\n");
    printf("                     FINAL BILL                     \n");
    printf("====================================================\n");
    printf("Customer: %s\n", customer_name);
    printf("Phone:    %s\n", customer_phone);
    printf("----------------------------------------------------\n");
    printf("%-10s %-20s %-10s %-10s %-10s\n", "S.No", "Item Name", "Qty", "Price", "Subtotal");
    printf("----------------------------------------------------\n");

    for (int j = 0; j < cart_count; j++) {
        int subtotal = cart_qty[j] * cart_price[j];
        printf("%-10d %-20s %-10d %-10d %-10d\n", 
               cart_sno[j], cart_name[j], cart_qty[j], cart_price[j], subtotal);
        grand_total += subtotal;
    }

    printf("----------------------------------------------------\n");
    printf("%-40s Rs %d\n", "GRAND TOTAL:", grand_total);
    printf("====================================================\n");
    printf("            Thank you for shopping with us!         \n");
    printf("====================================================\n");
}

int main() {
    char current_user[20];
    char current_pass[20];

    title(); 

    // Infinite app loop
    while(1) {
        printf("\n--- System Login Screen ---\n");
        
        // Call the login system
        password(current_user, current_pass);

        // Check who logged in
        if (strcmp(current_user, "admin") == 0) {
            printf("\nLoading Admin Panel...\n");
            restock();
            printf("\nRestocking completed successfully. Moving back to login portal...\n");
            // Admin returns seamlessly to the top of the while(1) loop
        } 
        else if (strcmp(current_user, "customer") == 0) {
            printf("\nLoading Customer Storefront...\n");
            inventory();
            
            // Once customer processes through inventory -> cart -> billing, session ends.
            printf("\nSession closed. Thank you!\n");
            break; 
        }
    }

    return 0;
}
