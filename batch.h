#ifndef BATCH_H
#define BATCH_H

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
    Batch *arr;
    int count;
    int capacity;
} BatchList;

void initBatchList(BatchList *list);
void freeBatchList(BatchList *list);

int addBatch(BatchList *list, Batch newBatch);
int displayBatches(BatchList *list);
int updateBatch(BatchList *list, char* batchID);
int searchBatch(BatchList *list, char* keyword);
int searchBatchByOrigin(BatchList *list, char* origin);

#endif
