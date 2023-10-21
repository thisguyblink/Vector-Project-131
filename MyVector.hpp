
// Name: Patrick Smith
// CWID: 885416354
// Email: patricksmith@csu.fullerton.edu

/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>


//
template <typename T>
class MyVector
{
	public:
		
		/*******************
		 * Static constants
		 ******************/
		
		/// Default capacity
		static constexpr size_t DEFAULT_CAPACITY = 64;
		
		/// Minimum capacity
		static constexpr size_t MINIMUM_CAPACITY = 8;
		
		/*****************************
		 * Constructors / Destructors
		 ****************************/
		
		/// Normal constructor
		MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {
			if (capacity < MINIMUM_CAPACITY) {
				this->capacity_ = MINIMUM_CAPACITY;
			}
			else {
			this->capacity_ = capacity;
			}
			T* arr = new T[capacity_];
			elements_ = arr;
		}
		
		/// Copy constructor
		MyVector(const MyVector& other) {
			this->copyOther(other);
		}
		
		/**
		 * Destructor
		 * Should call clear() so each element gets its destructor called.
		 * Then, de-allocate the internal array and make it a nullptr, if its not already a nullptr.
		 */
		~MyVector() {
			clear();
			delete[] this->elements_;
			elements_ = nullptr;
			// TODO: Your code here
		}
		
		/************
		 * Operators
		 ************/
		
		///	Assignment operator
		MyVector& operator=(const MyVector& rhs) {
			this->copyOther(rhs);
			return *this;
		}
		
		/// Operator overload to at()
		T& operator[](size_t index) const {
			IndexError(index);
			return this->at(index);
		}
		
		/************
		 * Accessors
		 ************/
		
		/// Return the number of valid elements in our data
		size_t size() const {
			return size_;
		}
		
		/// Return the capacity of our internal array
		size_t capacity() const {
			return capacity_;
		}
		
		/**
		 * Check whether our vector is empty
		 * Return true if we have zero elements in our array (regardless of capacity)
		 * Otherwise, return false
		 */
		bool empty() const {
			return (this->size() == 0) ? true : false;
		}
		
		/// Return a reference to the element at an index
		T& at(size_t index) const {
			IndexError(index);
			return elements_[index];
		}
		
		/***********
		 * Mutators
		 ***********/
		
		/** 
		 * Reserve capacity in advance, if our capacity isn't currently large enough.
		 * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
		 */
		void reserve(size_t capacity) {
			if (capacity > capacity_) {
			this->changeCapacity(capacity);
			}
		}
		
		/**
		 * Set an element at an index.
		 * Throws range error if outside the size boundary.
		 * Returns a reference to the newly set element (not the original)
		 */
		T& set(size_t index, const T& element) {
			IndexError(index);
			elements_[index].~T();
			this->at(index) = element;
			return this->elements_[index];
		}
		
		/**
		 * Add an element onto the end of our vector, increasing the size by 1
		 * Should rely on the insert() function to avoid repeating code.
		 * Returns a reference to the newly inserted element
		 */
		T& push_back(const T& element) {
			Grow();
			this->elements_[size_] = element;
			size_++;
			return this->elements_[size() - 1];
		}
		
		/**
		 * Remove the last element in our vector, decreasing the size by 1
		 * Should rely on the erase() function to avoid repeating code.
		 * Returns the new size.
		 */
		size_t pop_back() {
			if (size_ == 0) {
				throw std::out_of_range ("attempting to pop back in an empty vector");
			}
			size_--;
			Shrink();
			return size_;
		}
		
		/**
		 * Insert an element at some index in our vector, increasing the size by 1
		 * 
		 * Scoot all elements at index and beyond, one to the right. This
		 * makes a "hole" available at the index, where you can then place
		 * the new element.
		 * 
		 * Returns a reference to the newly added element (not the original).
		 */
		T& insert(size_t index, const T& element) {
			
			// TODO: Your code here
			// iterate through except when get to index subract 1 from for loop counter and add value instead
			// need an if statement in for loop
			// add change size function check 
			IndexError(index);
			size_++;
			for (size_t i = size() - 1; i >= index; i--) {
				if (i == index) {
					this->at(i) = element;
				}
				else {
					this->at(i) = this->at(i - 1);
				}
			}
			Grow();
			return this->elements_[index];			
		}
		
		/**
		 * Erase one element in our vector at the specified index, decreasing the size by 1.
		 * 
		 * This means you'd then have to scoot elements to the left to fill the "hole"
		 * 	left by the erased element.
		 * 
		 * Throws std::range_error if the index is out of bounds.
		 * 
		 * Calls the erased element's destructor.
		 * 
		 * Returns the new size.
		 */
		size_t erase(size_t index) {
			// TODO: Your code here
			// need if statement to make sure index isn't out of range, if to throw error
			// do the opposite of insert to iterate through and do i-- to effectively skip over value at the given index
			IndexError(index);
			for (size_t i = index; i < size_; i++) {
				this->elements_[i] = this->elements_[i + 1];
			}
			size_--;
			Shrink();
			return size_;
		}
		
		/**
		 * Calls each element's destructor, then clears our internal
		 * data by setting size to zero and resetting the capacity.
		*/
		void clear() {
			for (size_t i = 0; i < size_; i++) {
				elements_[i].~T();
			}
			size_ = 0;
			capacity_ = DEFAULT_CAPACITY;
			delete[] this->elements_;
			T* arr = new T[capacity_];
			elements_ = arr;
			// TODO: Your code here
		}
		void Grow() {
			if (size_ == capacity_) {
				changeCapacity(capacity_ * 2);
			}
		}
		void Shrink() {
			if ((size_  > 4) && (size_  + 1)== (capacity_ / 3)) {
				changeCapacity(capacity_ / 2);
			}
		}
		void IndexError(size_t index_) const {
			if ((index_ >= size_) || (index_ < 0)) {
				throw std::out_of_range ("index is not in vector []");
			}
		}
	
	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
	private:
		
		/// Number of valid elements currently in our vector
		size_t size_ = 0;
		
		/// Capacity of our vector; The actual size of our internal array
		size_t capacity_ = 0;
		
		/**
		 * Our internal array of elements of type T.
		 * Starts off as a null pointer.
		 */
		T* elements_ = nullptr;
		
		/**
		 * Helper function that is called whenever we need to change the capacity of our vector
		 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
		 * It's probably a good idea to make an additional helper function that decides
		 * 	whether to change capacity at all (and to what new capacity), that your public functions can rely upon.
		 */
		void changeCapacity(size_t c) {
			if (size() >= c) {
				throw std::range_error ("size bigger than capacity Change Capacity");
			}
			T* arr = new T[c];
			//arr.copyOther(this->elements_);
			for (size_t i = 0; i < size(); i++) {
				arr[i] = elements_[i];
			}
			this->capacity_ = c;
			delete[] this->elements_;
			this->elements_ = arr;
		}
		
		/**
		 * Copy another vector's elements into our own, by value.
		 * Does not simply copy the other vector's array's pointer
		 * Does not care about matching the capacity exactly.
		 * This is a helper function relied upon by the copy constructor and the assignment operator,
		 * 	to avoid repeated code.
		 * 
		 * You will probably want to make additional helper functions to make this one easier.
		 * Here is a suggested strategy for copying the internal array:
		 * 1. Deallocate the current array for 'this' (if it is already allocated)
		 * 2. Allocate a new array for 'this' of the appropriate size
		 * 3. Use a loop to copy elements one-by-one (by value)
		 * 4. Copy other relevant properties from the 'other' to 'this'
		 */
		void copyOther(const MyVector& other) {
			delete[] this->elements_;
			T* arr = new T[other.capacity_];
			this->capacity_ = other.capacity_;
			this->size_ = other.size_;
			this->elements_ = arr;
			for (size_t i = 0; i < other.size(); i++) {
				this->elements_[i] = other.elements_[i];
			}
		}
	
};

/*
Generic Notes/Questions:
Do I need to derefrence elements_ when modifrying it or changing it in any way?
Should/Can I use size_t instead of int in for loops?
Whenever I modify the length(size_) of an array do I need to make a new one a just copy the values over with the changes that need to be made?

*/
