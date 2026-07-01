#ifndef MENU_H
#define MENU_H

#define MAX_SIZE 100
#define MAX_STR 50

typedef enum {
    FRESH = 0,
    DRIED = 1
} StorageType;

typedef struct {
    char batchID[20];
    char productName[MAX_STR];
    char unit[20];
    float StorageTemp;
    char origin[MAX_STR];
    StorageType type;
} Batch;

typedef struct {
    char distributionID[20];
    char supplierName[MAX_STR];
    char destination[MAX_STR];
    char deliveryDate[20];
} Distribution;

void displayMenu();
void runSystem();
void processBatchManager(Batch batches[], int* bCount);
void processDistributionManager(Distribution orders[], int* dCount);
void loadAllData(Batch batches[], int* bCount, Distribution orders[], int* oCount, const char* filename);
void saveAllData(Batch batches[], int bCount, Distribution orders[], int oCount, const char* filename);

void addBatch(Batch list[], int* count, Batch newBatch);
void displayBatches(Batch list[], int count);
void updateBatch(Batch list[], int count, char* batchID);
void searchBatch(Batch list[], int count, char* keyword);
void searchBatchByOrigin(Batch list[], int count, char* origin);

void addDistribution(Distribution list[], int* count, Distribution newDist);
void trackDistribution(Distribution list[], int count, char* keyword);
void groupDistributionByDestination(Distribution list[], int count);

void loadDataFromFile(Batch bList[], int* bCount, Distribution dList[], int* dCount);
void saveDataToFile(Batch bList[], int bCount, Distribution dList[], int dCount);

#endif