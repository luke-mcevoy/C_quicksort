/*******************************************************************************
 * Name        : quicksort.c
 * Author      : Luke McEvoy
 * Date        : February 21, 2020
 * Description : Quicksort implementation.
 * Pledge      : I pledge my Honor I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*comp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*comp) (const void*, const void*));

/**
 * Compares two integers passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to int pointers.
 * Returns:
 * -- 0 if the integers are equal
 * -- a positive number if the first integer is greater
 * -- a negative if the second integer is greater
 */
int int_cmp(const void *a, const void *b) {
    int *c = (int *)a;
    int *d = (int *)b;
    if (*c == *d) {
      return 0;
    }
    if (*c > *d) {
      return 1;
    }
    else {
      return -1;
    }
}

/**
 * Compares two doubles passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to double pointers.
 * Returns:
 * -- 0 if the doubles are equal
 * -- 1 if the first double is greater
 * -- -1 if the second double is greater
 */
int dbl_cmp(const void *a, const void *b) {
    double *c = (double *)a;
    double *d = (double *)b;
    if (*c == *d) {
      return 0;
    }
    if (*c > *d) {
      return 1;
    }
    else {
      return -1;
    }
}

/**
 * Compares two char arrays passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to char* pointers (i.e. char**).
 * Returns the result of calling strcmp on them.
 */
int str_cmp(const void *a, const void *b) { 
    char **aChar = (char**)a;
    char **bChar = (char**)b;
    return strcmp (*aChar, *bChar);
}

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to character types and works with them as char
 * pointers for the remainder of the function.
 * Swaps one byte at a time, until all 'size' bytes have been swapped.
 * For example, if ints are passed in, size will be 4. Therefore, this function
 * swaps 4 bytes in a and b character pointers.
 */
static void swap(void *a, void *b, size_t size) {

    char* aChar = (char*)a;
    char* bChar = (char*)b;

    char temp;

    for(int i = 0; i < size; i++) {
      temp = aChar[i];
      aChar[i] = bChar[i];
      bChar[i] = temp;
      // temp = *(aChar+i);
      // *(aChar+i) = *(bChar+i);
      // *(bChar+1) = temp;
    }



}

/**
 * Partitions array around a pivot, utilizing the swap function.
 * Each time the function runs, the pivot is placed into the correct index of
 * the array in sorted order. All elements less than the pivot should
 * be to its left, and all elements greater than or equal to the pivot should be
 * to its right.
 * The function pointer is dereferenced when it is used.
 * Indexing into void *array does not work. All work must be performed with
 * pointer arithmetic.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*comp) (const void*, const void*)) {
    // Pseudo Lomuto Algorith
    //  p <- A[l]
    //  s <- l
    //  for i <- l + 1 to r do
    //    if A[i] < p
    //      s <- s + 1
    //      swap(A[s], A[i])
    //  swap(A[l], A[s])
    //  return s
  char *p = (char*)array;
  char *p_left = p + (left*elem_sz);
  int s = left;
  for (int i = left + 1; i <= right; i++) {
    if ( comp(p+(i*elem_sz), p_left) <= 0) {
      s++;
      swap(p+(s*elem_sz), p+(i*elem_sz), elem_sz);
    }
  }
  swap(p_left, p+(s*elem_sz), elem_sz);
  return s;

  //lomuto is going to need some work to be ready
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*comp) (const void*, const void*)) {
    //  if left < right
    //    s <- Partition(A[left .. right])
    //    Quicksort(A[left .. s-1])
    //    Quicksort(A[s+1 .. right])

    if (left < right) {
      int s = lomuto(array, left, right, elem_sz, comp);
      quicksort_helper(array, left, s-1, elem_sz, comp);
      quicksort_helper(array, s+1, right, elem_sz, comp);
    }
}

/**
 * Quicksort function exposed to the user.
 * Calls quicksort_helper with left = 0 and right = len - 1.
 */
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*comp) (const void*, const void*)) {
    // call helper here
    // the comp type is passed through the helper based on what type is called over flag
  quicksort_helper(array, 0, len-1, elem_sz, comp);

}
