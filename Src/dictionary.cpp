//
// Brian Mack, Juan Ipina, Blake Jackson, James Su
// Project #3 Word Search
// Implementation for the dictionary class
// (file loading, selection sort, binary find)
//
#include "dictionary.hpp"
#include "heap.hpp"

void dictionary::store(const string& filename)
{
    /* Reads words from filename and stores them in _words
     * parameters - filename: dictionary file to read from
     */
    /* Make sure opening the file doesn't fail. */
    std::ifstream in(filename);
    if (!in)
    {
        throw fileOpenError(filename);
    }
    
    /* If opening was successful, read the words into the vector. */
    // Clear the current vector
    _words.clear();
    std::string word;
    while (getline(in, word))
    {
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.size() - 1);
        }
        _words.push_back(word);
    }
}

void dictionary::sort(void)
{
    /* Sorts _words using selection sort */
    int n = _words.size();

    for (int i = 0; i < (n - 1); i++)
    {
        int minIndex = i;

        /* Find index of smallest element. */
        for (int j = (i + 1); j < n; j++)
        {
            if (_words[j] < _words[minIndex])
            {
                minIndex = j;
            }
        }

        /* Swap if needed. */
        if (minIndex != i)
        {
            std::swap(_words[i], _words[minIndex]);
        }
    }
}

void dictionary::sortWordsUsingQuicksortAlgorithm(void)
{
    /* Sorts _words using the quicksort algorithm */
    if (_words.empty())
    {
        return;
    }

    quicksortWordsInRange(0, static_cast<int>(_words.size()) - 1);
}

void dictionary::sortWordsUsingHeapsortAlgorithm(void)
{
    /* Sorts _words using the heapsort algorithm */
    heap<std::string> dictionary_word_heap;
    dictionary_word_heap.initializeMaxHeap(_words);
    _words = dictionary_word_heap.heapsort();
}

int dictionary::find(const std::string& target) const
{
    /* Searches for target using binary search
     * parameters - target: word to search for
     * returns - index of target if found, otherwise -1
     * assumptions - _words is already sorted
     */
    int left = 0;
    int right = _words.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (_words[mid] == target)
        {
            // If we've found the target, then return its index
            return mid;
        }
        else if (_words[mid] < target)
        {
            // If the target is to the right of the midpoint,
            // search the right half.
            left = mid + 1;
        }
        else
        {
            // If the target is to the left of the midpoint,
            // search the left half.
            right = mid - 1;
        }
    }

    /* If we reach this point, the target isn't in the dictionary,
     * so return -1.
     */
    return -1;
}

int dictionary::partitionWordsAroundPivotForQuicksort(
    int first_index,
    int last_index)
{
    /* Partitions words around a pivot for quicksort and returns pivot index */
    const std::string pivot_word = _words[last_index];
    int index_of_smaller_or_equal_region_end = first_index - 1;

    for (
        int current_index = first_index;
        current_index < last_index;
        current_index++)
    {
        if (_words[current_index] <= pivot_word)
        {
            index_of_smaller_or_equal_region_end++;
            std::swap(
                _words[index_of_smaller_or_equal_region_end],
                _words[current_index]);
        }
    }

    int final_pivot_index = index_of_smaller_or_equal_region_end + 1;
    std::swap(_words[final_pivot_index], _words[last_index]);
    return final_pivot_index;
}

void dictionary::quicksortWordsInRange(int first_index, int last_index)
{
    /* Recursively applies quicksort to _words in [first_index, last_index] */
    if (first_index >= last_index)
    {
        return;
    }

    int pivot_index = partitionWordsAroundPivotForQuicksort(
        first_index,
        last_index);
    quicksortWordsInRange(first_index, pivot_index - 1);
    quicksortWordsInRange(pivot_index + 1, last_index);
}

std::ostream& operator<<(std::ostream& os, const dictionary& dict)
{
    /* Overloaded << to print all words in the dictionary
     * parameters - os: output stream, dict: dictionary to print
     * assumptions - os is valid
     */
    for (int i = 0; i < dict._words.size(); i++)
    {
        os << dict._words[i] << '\n';
    }
    return os;
}