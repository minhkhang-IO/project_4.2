#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "batch.h"

typedef struct {
    char distributionID[20];
    char supplierName[MAX_STR];
    char destination[MAX_STR];
    char deliveryDate[20];
    char batchID[20]; 
    char productOrigin[MAX_STR]; 
} Distribution;

typedef struct {
    Distribution *arr;
    int count;
    int capacity;
} DistributionList;

void initDistributionList(DistributionList *list);
void freeDistributionList(DistributionList *list);

int addDistribution(DistributionList *list, Distribution newDist);
int trackDistribution(DistributionList *list, char* keyword);
int groupDistributionByDestination(DistributionList *list);
int sortDistributionsByDeliveryDate(DistributionList *list);
int sortDistributionsByProductOrigin(DistributionList *list);

#endif
