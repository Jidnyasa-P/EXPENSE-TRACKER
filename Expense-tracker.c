#include <stdio.h>
#include <stdlib.h>

struct MonthData {
    float budget;
    float total_expense;
    float savings;
    float *expenses;
    int num_expenses;
};

// Function to accept expenses and calculate total expenses for a given month
void acceptExpenses(struct MonthData *monthData) {
    float total = 0;
    printf("Enter the number of items on which money was spent: ");
    
    // Validate input
    if (scanf("%d", &monthData->num_expenses) != 1 || monthData->num_expenses < 0) {
        printf("Invalid number of expenses. Please enter a positive integer.\n");
        return;
    }

    // Dynamically allocate memory for storing expense amounts
    monthData->expenses = (float *)malloc(monthData->num_expenses * sizeof(float));
    
    // Check if malloc was successful
    if (monthData->expenses == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter the amounts for each expense:\n");
    for (int i = 0; i < monthData->num_expenses; i++) {
        printf("Expense %d: ", i + 1);
        
        // Validate input for each expense
        if (scanf("%f", &monthData->expenses[i]) != 1 || monthData->expenses[i] < 0) {
            printf("Invalid expense value. Please enter a positive number.\n");
            free(monthData->expenses);
            return;
        }
        total += monthData->expenses[i];
    }

    monthData->total_expense = total;
    monthData->savings = monthData->budget - total;
}

// Recursive function to accept budget and expenses for each month
void acceptMonthData(struct MonthData *months, int month, int totalMonths) {
    if (month == totalMonths) {
        return;
    }

    printf("\n--- Month %d ---\n", month + 1);
    printf("Enter the total budget for month %d: ", month + 1);
    
    // Validate budget input
    if (scanf("%f", &months[month].budget) != 1 || months[month].budget < 0) {
        printf("Invalid budget amount. Please enter a positive number.\n");
        return;
    }

    acceptExpenses(&months[month]);

    // Recursively call for the next month
    acceptMonthData(months, month + 1, totalMonths);
}

// Function to display overview (total budget, total expense, and savings)
void displayOverview(struct MonthData *months, int totalMonths) {
    float totalBudget = 0, totalExpense = 0, totalSavings = 0;

    for (int i = 0; i < totalMonths; i++) {
        totalBudget += months[i].budget;
        totalExpense += months[i].total_expense;
        totalSavings += months[i].savings;
    }

    printf("\nOverview:\n");
    printf("Total Budget: %.2f\n", totalBudget);
    printf("Total Expense: %.2f\n", totalExpense);
    printf("Total Savings: %.2f\n", totalSavings);
}

// Function to display a detailed review (monthly breakdown)
void displayDetailedReview(struct MonthData *months, int totalMonths) {
    for (int i = 0; i < totalMonths; i++) {
        printf("\n--- Month %d ---\n", i + 1);
        printf("Budget: %.2f\n", months[i].budget);
        printf("Total Expense: %.2f\n", months[i].total_expense);
        printf("Savings: %.2f\n", months[i].savings);

        printf("Expenses on individual items:\n");
        for (int j = 0; j < months[i].num_expenses; j++) {
            printf("  Expense %d: %.2f\n", j + 1, months[i].expenses[j]);
        }
    }
}

int main() {
    int totalMonths;
    char reviewChoice;

    printf("Enter the number of months: ");
    
    // Validate number of months input
    if (scanf("%d", &totalMonths) != 1 || totalMonths <= 0) {
        printf("Invalid input for number of months.\n");
        return 1;
    }

    // Dynamically allocate memory for month data
    struct MonthData *months = (struct MonthData *)malloc(totalMonths * sizeof(struct MonthData));
    
    // Check if malloc was successful
    if (months == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Accept data for each month using recursion
    acceptMonthData(months, 0, totalMonths);

    // Ask user for the type of review they want
    printf("\nDo you want an overview or a detailed review? (o/d): ");
    scanf(" %c", &reviewChoice);

    if (reviewChoice == 'o' || reviewChoice == 'O') {
        displayOverview(months, totalMonths);
    } else if (reviewChoice == 'd' || reviewChoice == 'D') {
        displayDetailedReview(months, totalMonths);
    } else {
        printf("Invalid choice!\n");
    }

    // Free allocated memory
    for (int i = 0; i < totalMonths; i++) {
        free(months[i].expenses);
    }
    free(months);

    return 0;
}