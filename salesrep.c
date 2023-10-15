#include <stdio.h>
#include <stdlib.h>

// Global array of month names
const char *months[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// Function to generate the sales report
void generate_sales_report(float sales_data[], int n) {
    printf("Monthly sales report for 2022:\n");
    printf("\nMonth\tSales\n\n");

    for (int i = 0; i < n; i++) {
        printf("%s\t$%.2f\n", months[i], sales_data[i]);
    }
}

// Function to calculate the minimum, maximum, and average sales
void calculate_sales_summary(float sales_data[], int n) {
    float min_sales = sales_data[0];
    float max_sales = sales_data[0];
    float total_sales = sales_data[0];

    int min_month = 0;
    int max_month = 0;

    for (int i = 1; i < n; i++) {
        if (sales_data[i] < min_sales) {
            min_sales = sales_data[i];
            min_month = i;
        }
        if (sales_data[i] > max_sales) {
            max_sales = sales_data[i];
            max_month = i;
        }
        total_sales += sales_data[i];
    }

    float avg_sales = total_sales / n;

    printf("\nSales summary:\n\n");
    printf("Minimum sales: $%.2f (%s)\n", min_sales, months[min_month]);
    printf("Maximum sales: $%.2f (%s)\n", max_sales, months[max_month]);
    printf("Average sales: $%.2f\n", avg_sales);
}

// Function to calculate six-month moving averages
void calculate_six_month_moving_average(float sales_data[], int n) {
    printf("\nSix-Month Moving Average Report:\n\n");

    for (int i = 0; i <= n - 6; i++) {
        float sum = 0;
        for (int j = 0; j < 6; j++) {
            sum += sales_data[i + j];
        }
        float average = sum / 6;
        printf("%s - %s $%.2f\n", months[i], months[i + 5], average);
    }
}

// Function to generate the sales report from highest to lowest
void generate_sales_report_highest_to_lowest(float sales_data[], int n) {
    printf("\nSales Report (Highest to Lowest):\n\n");
    printf("Month\tSales\n");

    // Create an array to store indices
    int indices[n];
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    // Sort indices based on the sales_data array
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sales_data[i] < sales_data[j]) {
                float temp_sales = sales_data[i];
                sales_data[i] = sales_data[j];
                sales_data[j] = temp_sales;
                int temp_index = indices[i];
                indices[i] = indices[j];
                indices[j] = temp_index;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s\t$%.2f\n", months[indices[i]], sales_data[i]);
    }
}

int main() {
    FILE *file = fopen("sales_data.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    float sales_data[12];
    for (int i = 0; i < 12; i++) {
        if (fscanf(file, "%f", &sales_data[i]) != 1) {
            fprintf(stderr, "Error reading from the file\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    generate_sales_report(sales_data, 12);
    calculate_sales_summary(sales_data, 12);
    calculate_six_month_moving_average(sales_data, 12);
    generate_sales_report_highest_to_lowest(sales_data, 12);

    return 0;
}