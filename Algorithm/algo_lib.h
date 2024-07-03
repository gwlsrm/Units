#pragma once
#include <algorithm>
#include <utility>
#include <vector>


/**
 * @brief max_element_if returns max element between iterators, which satisfies predicate
*/
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p) {
    ForwardIterator maxElemIt = std::find_if(first, last, p);
    for (ForwardIterator cur = maxElemIt; cur != last; ++cur) {
        // cur != maxElemIt is checked to avoid re-calculation of p(*maxElemIt) at first iteration
        if (cur != maxElemIt && p(*cur) && *maxElemIt < *cur) {
            maxElemIt = cur;
        }
    }
    return maxElemIt;
}

/**
 * if consecutive elements are equal (comparing by CompareBinaryPredicate) they sum to first
 * first, last - the range of elements to process
 * cmp - binary predicate which returns ​true if the elements should be treated as equal
 *      signature: bool pred(const Type &a, const Type &b);
 * sump - binary function wich sums first to second and stores sum to first
 *      signature: bool pred(Type &target, const Type &item);
 * return value - past-the-end iterator for new logical range
*/
template<typename ForwardIt, typename CompareBinaryPredicate, typename SumPredicate>
ForwardIt sumEqual(ForwardIt first, ForwardIt last, CompareBinaryPredicate cmp, SumPredicate sump)
{
    if (first == last)
        return last;

    ForwardIt result = first;
    while (++first != last) {
        if (cmp(*first, *result)) {
            sump(*result, *first);
        } else {
            ++result;
            if (result != first)
                *result = std::move(*first);
        }
    }

    return ++result;
}

/**
 * @brief sumVectors -- sums vFrom to vTo: vTo += vFrom elementwise
*/
template <typename T>
void sumVectors(std::vector<T>& vTo, const std::vector<T>& vFrom) {
    std::transform(vTo.begin(), vTo.end(), vFrom.begin(), vTo.begin(), std::plus<T>());
}