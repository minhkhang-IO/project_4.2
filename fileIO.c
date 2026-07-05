#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"

void saveDataToFile(BatchList *bList, DistributionList *dList) {
    FILE *file = fopen("organic_data.txt", "w");
    if (file == NULL) {
        printf("[Error] Cannot open file to save data!\n");
        return;
    }

    fprintf(file, "%d\n", bList->count);
    for (int i = 0; i < bList->count; i++) {
        fprintf(file, "%s|%s|%s|%.2f|%s|%d\n",
                bList->arr[i].batchID, 
                bList->arr[i].productName, 
                bList->arr[i].unit,
                bList->arr[i].StorageTemp, 
                bList->arr[i].origin, 
                bList->arr[i].type); 
    }

    fprintf(file, "%d\n", dList->count);
    for (int i = 0; i < dList->count; i++) {
        fprintf(file, "%s|%s|%s|%s|%s|%s\n",
                dList->arr[i].distributionID, 
                dList->arr[i].supplierName,
                dList->arr[i].destination, 
                dList->arr[i].deliveryDate,
                dList->arr[i].batchID,
                dList->arr[i].productOrigin);
    }

    fclose(file);
    printf("[System] Data saved successfully to organic_data.txt!\n");
}

void loadDataFromFile(BatchList *bList, DistributionList *dList) {
    FILE *file = fopen("organic_data.txt", "r");
    if (file == NULL) {
        printf("[System] No existing data file found. Starting fresh.\n");
        return;
    }

    char line[300];
    int bCount = 0;
    if (fgets(line, sizeof(line), file) != NULL && sscanf(line, "%d", &bCount) == 1) {
        for (int i = 0; i < bCount; i++) {
            if (fgets(line, sizeof(line), file) != NULL) {
                Batch newBatch;
                int typeInt;
                int parsed = sscanf(line, "%[^|]|%[^|]|%[^|]|%f|%[^|]|%d",
                       newBatch.batchID, 
                       newBatch.productName, 
                       newBatch.unit,
                       &newBatch.StorageTemp, 
                       newBatch.origin, 
                       &typeInt);
                if (parsed == 6) {
                    newBatch.type = (StorageType)typeInt;
                    addBatch(bList, newBatch);
                }
            }
        }
    }

    int dCount = 0;
    if (fgets(line, sizeof(line), file) != NULL && sscanf(line, "%d", &dCount) == 1) {
        for (int i = 0; i < dCount; i++) {
            if (fgets(line, sizeof(line), file) != NULL) {
                Distribution newDist;
                strcpy(newDist.batchID, "N/A");
                strcpy(newDist.productOrigin, "N/A");
                
                int parsed = sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                       newDist.distributionID, 
                       newDist.supplierName,
                       newDist.destination, 
                       newDist.deliveryDate,
                       newDist.batchID,
                       newDist.productOrigin);
                       
                if (parsed >= 4) {
                    addDistribution(dList, newDist);
                }
            }
        }
    }

    fclose(file);
    printf("[System] Existing data loaded successfully!\n");
}
