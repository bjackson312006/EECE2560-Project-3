//
// Brian Mack, Juan Ipina, Blake Jackson, James Su
// Project #3 Word Search
// Header for the heap template class (max-heap utilities and heapsort)
//
#pragma once

#include <algorithm>
#include <vector>
#include "d_except.h"

template <typename T>
class heap
{
    private:
        std::vector<T> _heap_items; // Items stored in the heap
        int _current_heap_size;     // Number of active heap items

        bool doesIndexExistInCurrentHeap(int index) const
        // Returns true if index is inside the active heap region
        {
            return index >= 0 && index < _current_heap_size;
        }

        void swapItemsAtIndices(int first_index, int second_index)
        // Swaps the items at first_index and second_index
        {
            std::swap(_heap_items[first_index], _heap_items[second_index]);
        }

    public:
        heap(void): _current_heap_size(0) {}
        // Constructor that initializes an empty heap

        int parent(int child_index) const
        // Returns the parent index for child_index
        {
            return (child_index - 1) / 2;
        }

        int left(int parent_index) const
        // Returns the left-child index for parent_index
        {
            return 2 * parent_index + 1;
        }

        int right(int parent_index) const
        // Returns the right-child index for parent_index
        {
            return 2 * parent_index + 2;
        }

        T getItem(int n) const
        // Returns the nth item in the underlying heap vector
        // assumptions - n is a valid index in the underlying vector
        {
            if (n < 0 || n >= static_cast<int>(_heap_items.size()))
            {
                throw indexRangeError(
                    "heap::getItem() invalid index",
                    n,
                    static_cast<int>(_heap_items.size()));
            }

            return _heap_items[n];
        }

        void initializeMaxHeap(const std::vector<T>& input_items)
        // Copies input_items into the heap and builds a max-heap
        {
            _heap_items = input_items;
            _current_heap_size = static_cast<int>(_heap_items.size());
            buildMaxHeap();
        }

        void maxHeapify(int node_index)
        // Restores max-heap order starting from node_index downward
        {
            int largest_index = node_index;
            int left_child_index = left(node_index);
            int right_child_index = right(node_index);

            if (
                doesIndexExistInCurrentHeap(left_child_index) &&
                _heap_items[left_child_index] > _heap_items[largest_index])
            {
                largest_index = left_child_index;
            }

            if (
                doesIndexExistInCurrentHeap(right_child_index) &&
                _heap_items[right_child_index] > _heap_items[largest_index])
            {
                largest_index = right_child_index;
            }

            if (largest_index != node_index)
            {
                swapItemsAtIndices(node_index, largest_index);
                maxHeapify(largest_index);
            }
        }

        void buildMaxHeap(void)
        // Converts _heap_items into a valid max-heap in-place
        {
            int last_parent_index = (_current_heap_size / 2) - 1;
            for (int index = last_parent_index; index >= 0; index--)
            {
                maxHeapify(index);
            }
        }

        std::vector<T> heapsort(void)
        // Sorts items using heap sort and returns the sorted vector
        {
            int original_heap_size = _current_heap_size;
            buildMaxHeap();

            for (
                int end_index = _current_heap_size - 1;
                end_index > 0;
                end_index--)
            {
                swapItemsAtIndices(0, end_index);
                _current_heap_size--;
                maxHeapify(0);
            }

            _current_heap_size = original_heap_size;
            return _heap_items;
        }
};
