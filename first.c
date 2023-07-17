#include <stdio.h>
#include <string.h>

#define MAX_SHIPMENTS 100

// структура для зберігання інформації про посилку
typedef struct {
    int shipment_number;
    char date[11];
    char destination_city[50];
    double weight;
} Shipment;

// функція для введення даних про посилку
void input_shipment(Shipment *shipment) {
    printf("Enter shipment number: ");
    scanf("%d", &shipment->shipment_number);
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", shipment->date);
    printf("Enter destination city: ");
    scanf("%s", shipment->destination_city);
    printf("Enter weight (in kg): ");
    scanf("%lf", &shipment->weight);
}

// функція для виведення даних про посилку
void print_shipment(Shipment shipment) {
    printf("Shipment number: %d\n", shipment.shipment_number);
    printf("Date: %s\n", shipment.date);
    printf("Destination city: %s\n", shipment.destination_city);
    printf("Weight: %.2f kg\n", shipment.weight);
}

// функція для виведення даних про всі посилки
void print_all_shipments(Shipment shipments[], int num_shipments) {
    printf("All shipments:\n");
    for (int i = 0; i < num_shipments; i++) {
        print_shipment(shipments[i]);
        printf("\n");
    }
}

// функція для підрахунку загальної ваги посилок за день
double total_weight_for_date(Shipment shipments[], int num_shipments, char date[11]) {
    double total_weight = 0.0;
    for (int i = 0; i < num_shipments; i++) {
        if (strcmp(shipments[i].date, date) == 0) {
            print_shipment(shipments[i]);
            printf("\n");
            total_weight += shipments[i].weight;
        }
    }
    return total_weight;
}

int main() {
    Shipment shipments[MAX_SHIPMENTS];
    int num_shipments = 0;

    while (1) {
        // виводимо меню
        printf("\n");
        printf("1. Add a new shipment\n");
        printf("2. View all shipments\n");
        printf("3. View shipments for a specific date\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: // додати нову посилку
                if (num_shipments < MAX_SHIPMENTS) {
                    input_shipment(&shipments[num_shipments]);
                    num_shipments++;
                    printf("Shipment added successfully.\n");
                } else {
                    printf("Cannot add more shipments, maximum number of shipments reached.\n");
                }
                break;
            case 2: // переглянути всі посилки
                if (num_shipments > 0) {
                    print_all_shipments(shipments, num_shipments);
                } else {
                    printf("No shipments to display.\n");
                }
                break;
            case 3: // пошук посилок за датою та виведення загальної ваги
                if (num_shipments > 0) {
                    char date[11];
                    printf("Enter date to search (YYYY-MM-DD): ");
                    scanf("%s", date);
                    printf("Shipments for %s:\n", date);
                    double total_weight = total_weight_for_date(shipments, num_shipments, date);
                    printf("Total weight for %s: %.2f kg\n", date, total_weight);
                } else {
                    printf("No shipments to display.\n");
                }
                break;
            case 4:
                return 0;
        }
    }
    return 0;
}
