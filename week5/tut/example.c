// AVL algorithm


// BST - insert = worsst case log(log(n)) 
// AVL - always lowest height to always log(n) complexity

#include <stdio.h>

/**
 * @brief create algorithm that checks if A 
 * has two elemetns that sum to a given value
 * 
 * // A[i] + A[?] = v; A[?] = v - A[i]
 * // use an AVL tree
 * // pseudocode
 */

/*
hasSumValue(A, n):
  t = new AVL tree

  for i = 0 to n - 1
    if v - A[i] is in t:
      return true
    end if
    insert A[i] into t
  end for
  // n elements in the array: log(n) operation
  return false

*/


