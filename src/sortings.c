#include "sortings.h"
#include "string_compare.h"

#define COUNT_ELEMENTS_IN_CHARSET 128

/*Bubble sort*/

void bubble(strings_array_t arr, array_size_t array_size, comparator_func_t comparator) {
	for (int i = 0; i < (int) array_size - 1; i++) {
		for (int j = 0; j < (int) array_size - 1 - i; j++) {
			if(comparator(arr[j], arr[j + 1]) == 1) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

/*Insertion sort*/

void insertion(strings_array_t arr, array_size_t array_size, comparator_func_t comparator) {
	for (int i = 1; i < (int) array_size; i++) {
		int j = i - 1;
		while(j >= 0 && comparator(arr[j], arr[j + 1]) == 1) {
			swap(&arr[j], &arr[j + 1]);
			j--;
		}
	}
}

/*Merge sort*/

void mergeSort2(strings_array_t arr, int left, int mid, int right, comparator_func_t comparator) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    char *left_m[n1], *right_m[n2];
    for (int i = 0; i < n1; i++) {
        left_m[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        right_m[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (comparator(left_m[i], right_m[j]) == 2) {
            arr[k] = left_m[i];
            i++;
        } else {
            arr[k] = right_m[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = left_m[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = right_m[j];
        j++;
        k++;
    }
}

void mergeSort(strings_array_t arr, int left, int right, comparator_func_t comparator) {
    if (left >= right) {
        return;
    }
    int mid = (left + right - 1) / 2;
    mergeSort(arr, left, mid, comparator);
    mergeSort(arr, mid + 1, right, comparator);
    mergeSort2(arr, left, mid, right, comparator);
}

void merge(strings_array_t arr, array_size_t array_size, comparator_func_t comparator) {
    mergeSort(arr, 0, (int) array_size - 1, comparator);
}

/*Quick sort*/

int partition(strings_array_t arr, int left, int right, comparator_func_t comparator) {
	char* pivot = arr[(left + right) / 2];
	int i = left;
	int j = right;
	while (1) {
		while (comparator(arr[i], pivot) == 2) i++;
		while (comparator(arr[j], pivot) == 1) j--;
		if (i >= j) {
			if (comparator == string_compare_asc) return j;
			else return i;
		} 
		swap(&arr[i], &arr[j]);
	}
}

void quick1(strings_array_t arr, int left, int right, comparator_func_t comparator) {
	if (left < right) {
		int it = partition(arr, left, right, comparator);
		quick1(arr, left, it - 1, comparator);
		quick1(arr, it + 1, right, comparator);
	}
}

void quick(strings_array_t arr, array_size_t array_size, comparator_func_t comparator) {
	quick1(arr, 0, array_size - 1, comparator);
}

/*Radix sort*/

void radix(strings_array_t arr, array_size_t array_size, comparator_func_t comparator) {
	int max_string_size = strlen(arr[0]);
	for (int i = 1; i < (int) array_size; i++) {
		if ((int) strlen(arr[i]) > max_string_size) max_string_size = strlen(arr[i]);
	}
	
	for (int i = max_string_size - 1; i >= 0; i--) {
		char *intermediate_arr[array_size];
		int count[COUNT_ELEMENTS_IN_CHARSET] = { 0 };

		for (int j = 0; j < (int) array_size; j++) {
			count[(int) arr[j][i]]++;
		}
		for (int j = 1; j < COUNT_ELEMENTS_IN_CHARSET; j++) {
			count[j] += count[j - 1];
		}
		for (int j = array_size - 1; j >= 0; j--) {
			intermediate_arr[count[(int) arr[j][i]] - 1] = arr[j];
			count[(int) arr[j][i]]--;
		}
		for (int j = array_size - 1; j >= 0; j--) {
			if (i > 0 || comparator == string_compare_asc) {
				arr[j] = intermediate_arr[j];
			}
			else {
				arr[array_size - 1 - j] = intermediate_arr[j];
			}
		}
	}
}
