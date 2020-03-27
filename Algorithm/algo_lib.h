#include <algorithm>

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