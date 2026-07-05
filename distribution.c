#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "distribution.h"

void initDistributionList(DistributionList *list) {
    list->capacity = 10;
    list->arr = (Distribution*)malloc(list->capacity * sizeof(Distribution));
    list->count = 0;
}

void freeDistributionList(DistributionList *list) {
    if (list->arr != NULL) {
        free(list->arr);
        list->arr = NULL;
    }
    list->count = 0;
    list->capacity = 0;
}

int addDistribution(DistributionList *list, Distribution newDist) {
    if (list->count == list->capacity) {
        int newCap = list->capacity * 2;
        Distribution *tmp = (Distribution*)realloc(list->arr, newCap * sizeof(Distribution));
        if (tmp == NULL) return -1;
        list->arr = tmp;
        list->capacity = newCap;
    }

    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->arr[i].distributionID, newDist.distributionID) == 0) {
            return -2; // Duplicate ID
        }
    }
    
    if (strlen(newDist.distributionID) == 0 || strlen(newDist.supplierName) == 0 || strlen(newDist.destination) == 0) {
        return -3; // Invalid data
    }
    
    list->arr[list->count] = newDist;
    list->count++;
    return 0;
}

int trackDistribution(DistributionList *list, char* keyword) {
    printf("\n--- Track Results for '%s' ---\n", keyword);
    int found = 0;
    printf("%-15s %-20s %-20s %-15s %-15s\n", "Dist ID", "Supplier", "Destination", "Date", "Batch ID");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < list->count; i++) {
        if (strstr(list->arr[i].supplierName, keyword) != NULL || strstr(list->arr[i].destination, keyword) != NULL) {
            printf("%-15s %-20s %-20s %-15s %-15s\n",
                list->arr[i].distributionID, list->arr[i].supplierName, 
                list->arr[i].destination, list->arr[i].deliveryDate, list->arr[i].batchID);
            found = 1;
        }
    }
    if (!found) {
        printf("No tracking records found.\n");
    }
    return 0;
}

int compareDestination(const void *a, const void *b) {
    Distribution *da = (Distribution*)a;
    Distribution *db = (Distribution*)b;
    return strcmp(da->destination, db->destination);
}

int groupDistributionByDestination(DistributionList *list) {
    if (list->count == 0) {
        printf("No data available.\n");
        return 0;
    }
    
    qsort(list->arr, list->count, sizeof(Distribution), compareDestination);
    
    printf("\n--- Distributions Grouped By Destination ---\n");
    char currentDest[MAX_STR] = "";
    
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->arr[i].destination, currentDest) != 0) {
            strcpy(currentDest, list->arr[i].destination);
            printf("\n>> Destination: %s\n", currentDest);
            printf("%-15s %-20s %-15s %-15s\n", "Dist ID", "Supplier", "Date", "Batch ID");
            printf("-----------------------------------------------------------------\n");
        }
        printf("%-15s %-20s %-15s %-15s\n",
            list->arr[i].distributionID, list->arr[i].supplierName, 
            list->arr[i].deliveryDate, list->arr[i].batchID);
    }
    return 0;
}

int compareDeliveryDate(const void *a, const void *b) {
    Distribution *da = (Distribution*)a;
    Distribution *db = (Distribution*)b;
    return strcmp(da->deliveryDate, db->deliveryDate);
}

int sortDistributionsByDeliveryDate(DistributionList *list) {
    qsort(list->arr, list->count, sizeof(Distribution), compareDeliveryDate);
    printf("[System] Distributions sorted by Delivery Date.\n");
    return 0;
}

int compareOrigin(const void *a, const void *b) {
    Distribution *da = (Distribution*)a;
    Distribution *db = (Distribution*)b;
    return strcmp(da->productOrigin, db->productOrigin);
}

int sortDistributionsByProductOrigin(DistributionList *list) {
    qsort(list->arr, list->count, sizeof(Distribution), compareOrigin);
    printf("[System] Distributions sorted by Product Origin.\n");
    return 0;
}
