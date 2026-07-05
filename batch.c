#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batch.h"

void initBatchList(BatchList *list) {
    list->capacity = 10;
    list->arr = (Batch*)malloc(list->capacity * sizeof(Batch));
    list->count = 0;
}

void freeBatchList(BatchList *list) {
    if (list->arr != NULL) {
        free(list->arr);
        list->arr = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

int addBatch(BatchList *list, Batch newBatch) {
    if (list->count == list->capacity) {
        int newCap = list->capacity * 2;
        Batch *tmp = (Batch*)realloc(list->arr, newCap * sizeof(Batch));
        if (tmp == NULL) return -1; // Memory error
        list->arr = tmp;
        list->capacity = newCap;
    }

    // Check duplicate ID
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->arr[i].batchID, newBatch.batchID) == 0) {
            return -2; // Duplicate ID
        }
    }
    
    // Validation
    if (newBatch.StorageTemp <= 0) return -3; // Invalid temp
    if (newBatch.type != FRESH && newBatch.type != DRIED) return -3;
    if (strlen(newBatch.batchID) == 0 || strlen(newBatch.productName) == 0) return -3;
    
    list->arr[list->count] = newBatch;
    list->count++;
    return 0;
}

int displayBatches(BatchList *list) {
    printf("\n--- List of Batches ---\n");
    if (list->count == 0) {
        printf("No batches available.\n");
        return 0;
    }
    printf("%-15s %-20s %-10s %-10s %-20s %-10s\n", "ID", "Product Name", "Unit", "Temp", "Origin", "Type");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < list->count; i++) {
        printf("%-15s %-20s %-10s %-10.2f %-20s %-10s\n",
            list->arr[i].batchID, list->arr[i].productName, list->arr[i].unit,
            list->arr[i].StorageTemp, list->arr[i].origin, 
            list->arr[i].type == FRESH ? "FRESH" : "DRIED");
    }
    return 0;
}

int updateBatch(BatchList *list, char* batchID) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->arr[i].batchID, batchID) == 0) {
            printf("\n--- Update Batch ID: %s ---\n", batchID);
            printf("Enter new Product Name: ");
            while(getchar() != '\n');
            fgets(list->arr[i].productName, MAX_STR, stdin);
            list->arr[i].productName[strcspn(list->arr[i].productName, "\n")] = 0;

            printf("Enter new Unit: ");
            scanf("%19s", list->arr[i].unit);

            printf("Enter new Storage Temp: ");
            float temp;
            if (scanf("%f", &temp) != 1 || temp <= 0) {
                printf("[Error] Storage Temp must be > 0.\n");
                return -3;
            }
            list->arr[i].StorageTemp = temp;

            printf("Enter new Origin: ");
            while(getchar() != '\n');
            fgets(list->arr[i].origin, MAX_STR, stdin);
            list->arr[i].origin[strcspn(list->arr[i].origin, "\n")] = 0;

            printf("Enter new Type (0 for FRESH, 1 for DRIED): ");
            int typeInput;
            if (scanf("%d", &typeInput) != 1 || (typeInput != 0 && typeInput != 1)) {
                printf("[Error] Invalid Type.\n");
                return -3;
            }
            list->arr[i].type = (typeInput == 0) ? FRESH : DRIED;

            printf("[Success] Batch updated successfully!\n");
            return 0;
        }
    }
    return -2; // Not found
}

int searchBatch(BatchList *list, char* keyword) {
    printf("\n--- Search Results for '%s' ---\n", keyword);
    int found = 0;
    printf("%-15s %-20s %-10s %-10s %-20s %-10s\n", "ID", "Product Name", "Unit", "Temp", "Origin", "Type");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < list->count; i++) {
        if (strstr(list->arr[i].batchID, keyword) != NULL || strstr(list->arr[i].productName, keyword) != NULL) {
            printf("%-15s %-20s %-10s %-10.2f %-20s %-10s\n",
                list->arr[i].batchID, list->arr[i].productName, list->arr[i].unit,
                list->arr[i].StorageTemp, list->arr[i].origin, 
                list->arr[i].type == FRESH ? "FRESH" : "DRIED");
            found = 1;
        }
    }
    if (!found) {
        printf("No matching batches found.\n");
    }
    return 0;
}

int searchBatchByOrigin(BatchList *list, char* origin) {
    printf("\n--- Search Results for Origin: '%s' ---\n", origin);
    int found = 0;
    printf("%-15s %-20s %-10s %-10s %-20s %-10s\n", "ID", "Product Name", "Unit", "Temp", "Origin", "Type");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < list->count; i++) {
        if (strstr(list->arr[i].origin, origin) != NULL) {
            printf("%-15s %-20s %-10s %-10.2f %-20s %-10s\n",
                list->arr[i].batchID, list->arr[i].productName, list->arr[i].unit,
                list->arr[i].StorageTemp, list->arr[i].origin, 
                list->arr[i].type == FRESH ? "FRESH" : "DRIED");
            found = 1;
        }
    }
    if (!found) {
        printf("No matching batches found.\n");
    }
    return 0;
}
