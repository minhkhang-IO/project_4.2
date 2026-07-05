#ifndef FILEIO_H
#define FILEIO_H

#include "batch.h"
#include "distribution.h"

void loadDataFromFile(BatchList *bList, DistributionList *dList);
void saveDataToFile(BatchList *bList, DistributionList *dList);

#endif
