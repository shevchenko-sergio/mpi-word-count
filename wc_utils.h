//
// Created by Sergio Shevchenko on 27/05/2020.
//

#ifndef MPI_WORD_COUNT_WC_UTILS_H
#define MPI_WORD_COUNT_WC_UTILS_H

#include "errors.h"

struct LinkedList **split_files_equally(struct LinkedList *file_list, unsigned int groups, enum wc_error *status);

#endif //MPI_WORD_COUNT_WC_UTILS_H
