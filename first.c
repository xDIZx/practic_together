#include <stdio.h>
#include <string.h>

#define MAX_SHIPMENTS 100
#define FILENAME "shipments.txt"

typedef struct {
    int shipment_number;
    char date[11];
    char destination_city[50];
    double weight;
} Shipment;

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

void print_shipment(Shipment shipment) {
    printf("Shipment number: %d\n", shipment.shipment_number);
    printf("Date: %s\n", shipment.date);
    printf("Destination city: %s\n", shipment.destination_city);
    printf("Weight: %.2f kg\n", shipment.weight);
}

void print_all_shipments(Shipment shipments[], int num_shipments) {
    printf("All shipments:\n");
    for (int i = 0; i < num_shipments; i++) {
        print_shipment(shipments[i]);
        printf("\n");
    }
}

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

void save_shipments_to_file(Shipment shipments[], int num_shipments) {
    FILE *file = fopen(FILENAME, "w");
    if (file != NULL) {
        for (int i = 0; i < num_shipments; i++) {
            fprintf(file, "%d %s %s %.2f\n", shipments[i].shipment_number, shipments[i].date, shipments[i].destination_city, shipments[i].weight);
        }
        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

int load_shipments_from_file(Shipment shipments[]) {
    FILE *file = fopen(FILENAME, "r");
    int num_shipments = 0;

    if (file != NULL) {
        while (fscanf(file, "%d %s %s %lf\n", &shipments[num_shipments].shipment_number,
                      shipments[num_shipments].date, shipments[num_shipments].destination_city,
                      &shipments[num_shipments].weight) == 4) {
            num_shipments++;
        }
        fclose(file);
    }

    return num_shipments;
}

void remove_shipment(Shipment shipments[], int num_shipments, int index) {
    if (index < 0 || index >= num_shipments) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index; i < num_shipments - 1; i++) {
        shipments[i] = shipments[i + 1];
    }
}

int is_shipment_number_duplicate(Shipment shipments[], int num_shipments, int shipment_number) {
    for (int i = 0; i < num_shipments; i++) {
        if (shipments[i].shipment_number == shipment_number) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Shipment shipments[MAX_SHIPMENTS];
    int num_shipments = load_shipments_from_file(shipments);

    while (1) {
        printf("\n");
        printf("1. Add a new shipment\n");
        printf("2. View all shipments\n");
        printf("3. View shipments for a specific date\n");
        printf("4. Delete a shipment\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (num_shipments < MAX_SHIPMENTS) {
                    Shipment new_shipment;
                    input_shipment(&new_shipment);

                    if (is_shipment_number_duplicate(shipments, num_shipments, new_shipment.shipment_number)) {
                        printf("A shipment with the same shipment number already exists. Please enter a different shipment number.\n");
                    } else {
                        shipments[num_shipments] = new_shipment;
                        num_shipments++;
                        printf("Shipment added successfully.\n");
                        save_shipments_to_file(shipments, num_shipments);
                    }
                } else {
                    printf("Cannot add more shipments, the maximum number of shipments has been reached.\n");
                }
                break;
            case 2:
                if (num_shipments > 0) {
                    print_all_shipments(shipments, num_shipments);
                } else {
                    printf("No shipments to display.\n");
                }
                break;
            case 3:
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
                if (num_shipments > 0) {
                    int index;
                    printf("Enter the index of the shipment to delete: ");
                    scanf("%d", &index);
                    remove_shipment(shipments, num_shipments, index);
                    num_shipments--;
                    save_shipments_to_file(shipments, num_shipments);
                    printf("Shipment deleted successfully.\n");
                } else {
                    printf("No shipments to delete.\n");
                }
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}
