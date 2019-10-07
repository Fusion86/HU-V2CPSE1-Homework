// Created by Wouter "Fusion86" Visser
// Licensed under the Specerijen met Eigen Risico Public License

#include <ostream>
#include <array>

template <typename T, size_t S>
class set {
  private:
    // Underlying array where items are stored
    std::array<T, S> arr;

    // Number of items in our set, points to the place where the next item will be placed (if our set isn't full)
    size_t ptr = 0;

  public:
    // Add item to set, does nothing when set is full or when item already exists in the set
    void add(T item) {
        // If item is not in set and the set isn't full
        if (!contains(item) && ptr < S)
            arr[ptr++] = item; // Add item to set and increase ptr
    }

    // Remove item from set, or do nothing if the set doesn't contain item
    void remove(T item) {
        // Ex.
        // set.arr = 0, 1, 2, 3, 4
        // set.remove(3)
        // set.arr = 0, 1, 2, 4

        bool shift = false;
        for (size_t i = 0; i < ptr; i++) {
            // If the item we want to remove is found set shift to true
            if (arr[i] == item) shift = true;

            // If shit == true then shift all items one position down.
            // This will replace the item we want to remove with the next item in the array
            // and then shift the rest of the items one positon to the left
            if (shift) arr[i] = arr[i + 1];
        }

        // If shift == true (this is true when an item has been removed) decrease ptr
        if (shift) ptr--;
    }

    // Return true when item exists in set
    bool contains(T item) {
        return indexOf(item) != -1;
    }

    // Return index of item in set, or -1 if the item doesn't exist in the set
    int indexOf(T item) {
        for (size_t i = 0; i < ptr; i++)
            if (arr[i] == item) return i;
        return -1;
    }

    // Return largest item, behaviour is undefined when set contains no items
    T max() {
        T max = arr[0];
        for (size_t i = 1; i < ptr; i++) {
            if (arr[i] > max) max = arr[i];
        }
        return max;
    }

    friend std::ostream& operator<<(std::ostream& os, const set& set) {
        // os << "ptr: " << set.ptr << "\n";

        for (size_t i = 0; i < set.ptr; i++) {
            os << set.arr[i];
            if (i != set.ptr - 1) os << ", ";
        }
        return os;
    }
};
