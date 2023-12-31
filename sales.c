#include <stdio.h>
#include <string.h>

// Structure to represent a record
struct Record
{
    char item_code[10];
    char item_name[50];
    int quantity;
    float price;
    float cost;
};

int main()
{
    FILE *file = fopen("STOCK.DAT", "ab+");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int choice;
    struct Record record;

    do
    {
        printf("\n1. Append Record\n2. Display Records\n3. Search Record\n4. Delete Record\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Item Code: ");
            scanf("%s", record.item_code);
            printf("Enter Item Name: ");
            scanf("%s", record.item_name);
            printf("Enter Quantity: ");
            scanf("%d", &record.quantity);
            printf("Enter Price: ");
            scanf("%f", &record.price);

            // Calculate the total cost
            record.cost = record.quantity * record.price;

            // Append the record to the file
            fwrite(&record, sizeof(struct Record), 1, file);
            break;

        case 2:
            // Display records from the file
            rewind(file); // Move the file cursor to the beginning
            printf("%-15s%-20s%-10s%-10s%-10s\n", "Item Code", "Item Name", "Quantity", "Price", "Cost");

            while (fread(&record, sizeof(struct Record), 1, file) == 1)
            {
                printf("%-15s%-20s%-10d%-10.2f%-10.2f\n", record.item_code, record.item_name, record.quantity, record.price, record.cost);
            }
            break;

        case 3:
            printf("Enter Item Name to Search: ");
            char searchItemName[50];
            scanf("%s", searchItemName);

            // Search for records by item name
            rewind(file);
            printf("%-15s%-20s%-10s%-10s%-10s\n", "Item Code", "Item Name", "Quantity", "Price", "Cost");

            while (fread(&record, sizeof(struct Record), 1, file) == 1)
            {
                if (strstr(record.item_name, searchItemName) != NULL)
                {
                    printf("%-15s%-20s%-10d%-10.2f%-10.2f\n", record.item_code, record.item_name, record.quantity, record.price, record.cost);
                }
            }
            break;

        case 4:
            printf("Enter Item Code to Delete: ");
            char deleteItemCode[10];
            scanf("%s", deleteItemCode);

            FILE *tempFile = fopen("temp.dat", "wb");
            rewind(file);

            while (fread(&record, sizeof(struct Record), 1, file) == 1)
            {
                if (strcmp(record.item_code, deleteItemCode) != 0)
                {
                    fwrite(&record, sizeof(struct Record), 1, tempFile);
                }
            }

            fclose(file);
            remove("STOCK.DAT");

            fclose(tempFile);
            rename("temp.dat", "STOCK.DAT");
            file = fopen("STOCK.DAT", "ab+");
            break;

        case 0:
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    fclose(file);

    return 0;
}
