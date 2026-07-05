#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "batch.h"
#include "distribution.h"
#include "fileIO.h"

void pressToContinue() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); 
    getchar();
}

void displayMenu() {
    printf("\n==================================================\n");
    printf("   ORGANIC FOOD DISTRIBUTION & BATCH TRACKING\n");
    printf("==================================================\n");
    printf("1. BatchManager\n");
    printf("2. DistributionManager\n");
    printf("0. Exit\n");
    printf("==================================================\n");
    printf("Enter your choice (0-2): ");
}

void processBatchManager(BatchList *bList) {
    int subChoice;
    char tempStr[MAX_STR];

    do {
        system("cls");
        printf("\n=== BATCH MANAGER ===\n");
        printf("1. addBatch (1.1)\n");
        printf("2. displayBatches (1.2)\n");
        printf("3. updateBatch (1.3)\n");
        printf("4. searchBatch (1.4)\n");
        printf("5. searchBatchByOrigin (1.5)\n");
        printf("6. Back (1.6)\n");
        printf("Get your choice? (1-6): ");

        if (scanf("%d", &subChoice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            pressToContinue();
            continue;
        }

        switch(subChoice) {
            case 1: {
                Batch newBatch;
                printf("\n--- Add New Batch ---\n");
                printf("Enter Batch ID: ");
                scanf("%19s", newBatch.batchID);
                
                printf("Enter Product Name: ");
                while(getchar() != '\n');
                fgets(newBatch.productName, MAX_STR, stdin);
                newBatch.productName[strcspn(newBatch.productName, "\n")] = 0;

                printf("Enter Unit: ");
                scanf("%19s", newBatch.unit);

                printf("Enter Storage Temp: ");
                if (scanf("%f", &newBatch.StorageTemp) != 1) newBatch.StorageTemp = -1;

                printf("Enter Origin: ");
                while(getchar() != '\n');
                fgets(newBatch.origin, MAX_STR, stdin);
                newBatch.origin[strcspn(newBatch.origin, "\n")] = 0;

                printf("Enter Type (0 for FRESH, 1 for DRIED): ");
                int typeInput;
                if (scanf("%d", &typeInput) == 1 && (typeInput == 0 || typeInput == 1)) {
                    newBatch.type = (StorageType)typeInput;
                } else {
                    newBatch.type = (StorageType)-1; // Invalid
                }

                int res = addBatch(bList, newBatch);
                if (res == 0) printf("[Success] Batch added successfully!\n");
                else if (res == -1) printf("[Error] Memory allocation failed!\n");
                else if (res == -2) printf("[Error] Batch ID '%s' already exists!\n", newBatch.batchID);
                else if (res == -3) printf("[Error] Invalid data input!\n");
                
                pressToContinue(); 
                break;
            }
            case 2:
                displayBatches(bList);
                pressToContinue(); 
                break;
            case 3:
                printf("Enter Batch ID to update: ");
                scanf("%19s", tempStr);
                int res = updateBatch(bList, tempStr);
                if (res == -2) printf("[Error] Batch ID '%s' not found!\n", tempStr);
                else if (res == -3) printf("[Error] Invalid data during update!\n");
                pressToContinue();
                break;
            case 4:
                printf("Enter ID or Name to search: ");
                scanf(" %[^\n]", tempStr);
                searchBatch(bList, tempStr);
                pressToContinue();
                break;
            case 5:
                printf("Enter Origin to search: ");
                scanf(" %[^\n]", tempStr);
                searchBatchByOrigin(bList, tempStr);
                pressToContinue();
                break;
            case 6:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("[Error] Invalid Choice! Please enter 1-6.\n");
                pressToContinue();
        }
    } while (subChoice != 6);
}

void processDistributionManager(DistributionList *dList, BatchList *bList) {
    int subChoice;
    char tempStr[MAX_STR];

    do {
        system("cls"); 
        printf("\n=== DISTRIBUTION MANAGER ===\n");
        printf("1. addDistribution \n");
        printf("2. trackDistribution \n");
        printf("3. groupDistributionByDestination \n");
        printf("4. sortDistributionsByDeliveryDate \n");
        printf("5. sortDistributionsByProductOrigin \n");
        printf("6. Back \n");
        printf("Get your choice? (1-6): ");

        if (scanf("%d", &subChoice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            pressToContinue();
            continue;
        }

        switch(subChoice) {
            case 1: {
                Distribution newDist;
                printf("\n--- Add New Distribution ---\n");
                printf("Enter Distribution ID: ");
                scanf("%19s", newDist.distributionID);
                
                printf("Enter Supplier Name: ");
                while(getchar() != '\n');
                fgets(newDist.supplierName, MAX_STR, stdin);
                newDist.supplierName[strcspn(newDist.supplierName, "\n")] = 0;

                printf("Enter Destination: ");
                fgets(newDist.destination, MAX_STR, stdin);
                newDist.destination[strcspn(newDist.destination, "\n")] = 0;

                printf("Enter Delivery Date (YYYY-MM-DD): ");
                scanf("%19s", newDist.deliveryDate);
                
                printf("Enter Batch ID to link (or NONE): ");
                scanf("%19s", newDist.batchID);
                
                strcpy(newDist.productOrigin, "Unknown");
                if (strcmp(newDist.batchID, "NONE") != 0) {
                    for (int i=0; i<bList->count; i++) {
                        if (strcmp(bList->arr[i].batchID, newDist.batchID) == 0) {
                            strcpy(newDist.productOrigin, bList->arr[i].origin);
                            break;
                        }
                    }
                }

                int res = addDistribution(dList, newDist);
                if (res == 0) printf("[Success] Distribution added successfully!\n");
                else if (res == -1) printf("[Error] Memory allocation failed!\n");
                else if (res == -2) printf("[Error] Distribution ID '%s' already exists!\n", newDist.distributionID);
                else if (res == -3) printf("[Error] Invalid data input!\n");
                
                pressToContinue();
                break;
            }
            case 2:
                printf("Enter Supplier Name or Destination to track: ");
                scanf(" %[^\n]", tempStr);
                trackDistribution(dList, tempStr);
                pressToContinue();
                break;
            case 3:
                groupDistributionByDestination(dList);
                pressToContinue();
                break;
            case 4:
                sortDistributionsByDeliveryDate(dList);
                pressToContinue();
                break;
            case 5:
                sortDistributionsByProductOrigin(dList);
                pressToContinue();
                break;
            case 6:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("[Error] Invalid Choice! Please enter 1-6.\n");
                pressToContinue();
        }
    } while (subChoice != 6);
}

void runSystem() {
    BatchList bList;
    DistributionList dList;
    
    initBatchList(&bList);
    initDistributionList(&dList);
    
    printf("[System] Automatically loading data...\n");
    loadDataFromFile(&bList, &dList);
   
    int choice;
    do {
        system("cls");
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            pressToContinue();
            continue;
        }

        switch(choice) {
            case 1:
                processBatchManager(&bList); 
                break;
            case 2:
                processDistributionManager(&dList, &bList);
                break;
            case 0:
                printf("\n[System] Saving data and exiting...\n");
                saveDataToFile(&bList, &dList);
                freeBatchList(&bList);
                freeDistributionList(&dList);
                printf("Goodbye!\n");
                break;
            default:
                printf("Error: Invalid choice! Please select between 0 and 2.\n");
                pressToContinue();
        }
    } while (choice != 0);
}