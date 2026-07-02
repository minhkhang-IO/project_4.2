#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Menu.h"

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

void runSystem() {
    Batch batches[MAX_SIZE];
    Distribution orders[MAX_SIZE];
    int batchCount = 0;
    int orderCount = 0;
    int choice;

    printf("[System] Automatically loading data...\n");
    loadDataFromFile(batches, &batchCount, orders, &orderCount);
   
   do {
        system("cls"); // LÀM SẠCH MÀN HÌNH trước khi in Menu chính
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            pressToContinue();
            continue;
        }

    switch(choice) {
            case 1:
                processBatchManager(batches, &batchCount); 
                break;
            case 2:
                processDistributionManager(orders, &orderCount);
                break;
            case 0:
                printf("\n[System] Saving data and exiting...\n");
                saveDataToFile(batches, batchCount, orders, orderCount);
                printf("Goodbye!\n");
                break;
            default:
                printf("Error: Invalid choice! Please select between 0 and 2.\n");
                pressToContinue();
        }
    } while (choice != 0);
}


// ================= XỬ LÝ SUB-MENU BATCH MANAGER =================
void processBatchManager(Batch batches[], int* bCount) {
    int subChoice;
    char tempStr[MAX_STR];
    Batch newBatch; 

    do {
        system("cls"); // LÀM SẠCH MÀN HÌNH để chỉ hiển thị duy nhất Menu thực đơn con của Batch
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
            case 1:
                addBatch(batches, bCount, newBatch);
                pressToContinue(); 
                break;
            case 2:
                displayBatches(batches, *bCount);
                pressToContinue(); 
                break;
            case 3:
                printf("Enter Batch ID to update: ");
                scanf("%19s", tempStr);
                updateBatch(batches, *bCount, tempStr);
                pressToContinue();
                break;
            case 4:
                printf("Enter ID or Name to search: ");
                scanf(" %[^\n]", tempStr);
                searchBatch(batches, *bCount, tempStr);
                pressToContinue();
                break;
            case 5:
                printf("Enter Origin to search: ");
                scanf(" %[^\n]", tempStr);
                searchBatchByOrigin(batches, *bCount, tempStr);
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

// --- TINH NANG NHO CUA BATCHMANAGER
void addBatch(Batch list[], int* count, Batch newBatch) {
    if (*count >= MAX_SIZE) {
        printf("[Error] Batch list is full!\n");
        return;
    }
    printf("\n--- Add New Batch ---\n");
    printf("Enter Batch ID: ");
    scanf("%19s", newBatch.batchID);
    
    for (int i = 0; i < *count; i++) {
        if (strcmp(list[i].batchID, newBatch.batchID) == 0) {
            printf("[Error] Batch ID '%s' already exists!\n", newBatch.batchID);
            return;
        }
    }

    printf("Enter Product Name: ");
    while(getchar() != '\n');
    fgets(newBatch.productName, MAX_STR, stdin);
    newBatch.productName[strcspn(newBatch.productName, "\n")] = 0;

    printf("Enter Unit: ");
    scanf("%19s", newBatch.unit);

    printf("Enter Storage Temp: ");
    scanf("%f", &newBatch.StorageTemp);

    printf("Enter Origin: ");
    while(getchar() != '\n');
    fgets(newBatch.origin, MAX_STR, stdin);
    newBatch.origin[strcspn(newBatch.origin, "\n")] = 0;

    printf("Enter Type (0 for FRESH, 1 for DRIED): ");
    int typeInput;
    scanf("%d", &typeInput);
    newBatch.type = (typeInput == 0) ? FRESH : DRIED;

    list[*count] = newBatch;
    (*count)++;
    printf("[Success] Batch added successfully!\n");
}

void displayBatches(Batch list[], int count) {
    printf("\n--- List of Batches ---\n");
    if (count == 0) {
        printf("No batches available.\n");
        return;
    }
    printf("%-15s %-20s %-10s %-10s %-20s %-10s\n", "ID", "Product Name", "Unit", "Temp", "Origin", "Type");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-15s %-20s %-10s %-10.2f %-20s %-10s\n",
            list[i].batchID, list[i].productName, list[i].unit,
            list[i].StorageTemp, list[i].origin, 
            list[i].type == FRESH ? "FRESH" : "DRIED");
    }
}

void updateBatch(Batch list[], int count, char* batchID) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].batchID, batchID) == 0) {
            printf("\n--- Update Batch ID: %s ---\n", batchID);
            printf("Enter new Product Name: ");
            while(getchar() != '\n');
            fgets(list[i].productName, MAX_STR, stdin);
            list[i].productName[strcspn(list[i].productName, "\n")] = 0;

            printf("Enter new Unit: ");
            scanf("%19s", list[i].unit);

            printf("Enter new Storage Temp: ");
            scanf("%f", &list[i].StorageTemp);

            printf("Enter new Origin: ");
            while(getchar() != '\n');
            fgets(list[i].origin, MAX_STR, stdin);
            list[i].origin[strcspn(list[i].origin, "\n")] = 0;

            printf("Enter new Type (0 for FRESH, 1 for DRIED): ");
            int typeInput;
            scanf("%d", &typeInput);
            list[i].type = (typeInput == 0) ? FRESH : DRIED;

            printf("[Success] Batch updated successfully!\n");
            return;
        }
    }
    printf("[Error] Batch ID '%s' not found!\n", batchID);
}

void searchBatch(Batch list[], int count, char* keyword) {
    printf("\n--- Search Results for '%s' ---\n", keyword);
    int found = 0;
    printf("%-15s %-20s %-10s %-10s %-20s %-10s\n", "ID", "Product Name", "Unit", "Temp", "Origin", "Type");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (strstr(list[i].batchID, keyword) != NULL || strstr(list[i].productName, keyword) != NULL) {
            printf("%-15s %-20s %-10s %-10.2f %-20s %-10s\n",
                list[i].batchID, list[i].productName, list[i].unit,
                list[i].StorageTemp, list[i].origin, 
                list[i].type == FRESH ? "FRESH" : "DRIED");
            found = 1;
        }
    }
    if (!found) {
        printf("No matching batches found.\n");
    }
}

void searchBatchByOrigin(Batch list[], int count, char* origin) {
    printf("\n--- Search Results for Origin: '%s' ---\n", origin);
    int found = 0;
    printf("%-15s %-20s %-10s %-10s %-20s %-10s\n", "ID", "Product Name", "Unit", "Temp", "Origin", "Type");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (strstr(list[i].origin, origin) != NULL) {
            printf("%-15s %-20s %-10s %-10.2f %-20s %-10s\n",
                list[i].batchID, list[i].productName, list[i].unit,
                list[i].StorageTemp, list[i].origin, 
                list[i].type == FRESH ? "FRESH" : "DRIED");
            found = 1;
        }
    }
    if (!found) {
        printf("No matching batches found.\n");
    }
}
//==================DISTRIBUTIONMANAGER==================================
void processDistributionManager(Distribution orders[], int* dCount) {
    int subChoice;
    char tempStr[MAX_STR];
    Distribution newDist;

    do {
        system("cls"); // Làm sạch màn hình cho thực đơn con
        printf("\n=== DISTRIBUTION MANAGER ===\n");
        printf("1. addDistribution \n");
        printf("2. trackDistribution \n");
        printf("3. groupDistributionByDestination \n");
        printf("4. Back \n");
        printf("Get your choice? (1-4): ");

        if (scanf("%d", &subChoice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            pressToContinue();
            continue;
        }

        switch(subChoice) {
            case 1:
                addDistribution(orders, dCount, newDist);
                pressToContinue();
                break;
            case 2:
                printf("Enter Supplier Name or Destination to track: ");
                scanf(" %[^\n]", tempStr);
                trackDistribution(orders, *dCount, tempStr);
                pressToContinue();
                break;
            case 3:
                groupDistributionByDestination(orders, *dCount);
                pressToContinue();
                break;
            case 4:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("[Error] Invalid Choice! Please enter 1-4.\n");
                pressToContinue();
        }
    } while (subChoice != 4);
}

<<<<<<< HEAD
// --- KHUNG KHAI BÁO CÁC HÀM CON DIST4RIBUTION  ---
=======
// --- KHUNG KHAI BÁO CÁC HÀM CON DISTRIBUTION  ---
>>>>>>> 2da649b8e993c33c544111bf65130322efcf8e2a
void addDistribution(Distribution list[], int* count, Distribution newDist) {
    printf("\n--> [Executing] addDistribution...\n");
}

void trackDistribution(Distribution list[], int count, char* keyword) {
    printf("\n--> [Executing] trackDistribution for keyword: %s...\n", keyword);
}

void groupDistributionByDestination(Distribution list[], int count) {
    printf("\n--> [Executing] groupDistributionByDestination...\n");
}
// ================= XỬ LÝ LƯU/NẠP DỮ LIỆU (FILE I/O) =================

void saveDataToFile(Batch bList[], int bCount, Distribution dList[], int dCount) {
    FILE *file = fopen("organic_data.txt", "w");
    if (file == NULL) {
        printf("[Error] Cannot open file to save data!\n");
        return;
    }

    // 1. Lưu danh sách Batch
    fprintf(file, "%d\n", bCount); // Lưu tổng số lượng lô hàng trước
    for (int i = 0; i < bCount; i++) {
        fprintf(file, "%s,%s,%s,%.2f,%s,%d\n",
                bList[i].batchID, 
                bList[i].productName, 
                bList[i].unit,
                bList[i].StorageTemp, 
                bList[i].origin, 
                bList[i].type); 
    }

    // 2. Lưu danh sách Distribution
    fprintf(file, "%d\n", dCount); // Lưu tổng số lượng phân phối
    for (int i = 0; i < dCount; i++) {
        fprintf(file, "%s,%s,%s,%s\n",
                dList[i].distributionID, 
                dList[i].supplierName,
                dList[i].destination, 
                dList[i].deliveryDate);
    }

    fclose(file);
    printf("[System] Data saved successfully to organic_data.txt!\n");
}

void loadDataFromFile(Batch bList[], int* bCount, Distribution dList[], int* dCount) {

    FILE *file = fopen("organic_data.txt", "r");
    if (file == NULL) {
        printf("[System] No existing data file found. Starting fresh.\n");
        *bCount = 0;
        *dCount = 0;
        return;
    }

    // 1. Đọc danh sách Batch
    if (fscanf(file, "%d\n", bCount) == 1) {
        for (int i = 0; i < *bCount; i++) {
            int typeInt;
            fscanf(file, "%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                   bList[i].batchID, 
                   bList[i].productName, 
                   bList[i].unit,
                   &bList[i].StorageTemp, 
                   bList[i].origin, 
                   &typeInt);
            bList[i].type = (StorageType)typeInt;
        }
    }

    // 2. Đọc danh sách Distribution
    if (fscanf(file, "%d\n", dCount) == 1) {
        for (int i = 0; i < *dCount; i++) {
            fscanf(file, "%[^,],%[^,],%[^,],%[^\n]\n",
                   dList[i].distributionID, 
                   dList[i].supplierName,
                   dList[i].destination, 
                   dList[i].deliveryDate);
        }
    }

    fclose(file);
    printf("[System] Existing data loaded successfully!\n");
}