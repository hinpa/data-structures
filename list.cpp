// list implementation
#include <iostream>


// A static list is a data structure that satisfies these points:
// 1. Store given amount of elements of given data type
// 2. Write/Modify element at given position
// 3. Read element at given position
// An implementation of static list is an array

// A dynamic list:
// 1. If no elements, the size is 0
// 2. Can insert
// 3. Can remove
// 4. Count
// 5. W/M element access
// 6. Stores particular data type.
// A typical dynamic array or vector is an example of a list
// However, arrays and vectors have problems with memory inefficiency.
// You have to always allocate memory with some capacity
// What if we've never get to use all the capacity? 
// Another problem is if we still get to use all capacity we have to reallocate the whole thing
// so that all elements fit in one contigous block of memory.
// Let's go through array implementation list big O notation:
// Insert is O(n) (including pushing back)
// Removal is O(n)
// W/m access is O(1)
//


// Let's be more specific and talk about linked list.
// A linked list is a list that associates every element with a link to the next element
// For simplicity, let's imagine that we want to store integers:

/*
struct Node {
	int value; 
	Node* next;
};
*/

// Big O:
// Access is O(n)
// Insert is O(n)
// Removal is O(n)


// Let's now compare list as an array and forward list.
// 1.As you could notice, Big O of linked list and an array in terms of access differ
// drastically. Array wins in this case.
// 2.Considering what you actually store and how much of it, linked list will often win in
// space efficiency. 
// Arrays are fixed-size. That is, you will usually have some unused space at the
// end of an array.
// Linked list don't allocate unused memory. However, they store both pointers and values.
// When I said that linked list will OFTEN win in space efficiency, this is not always the case.
// For example, int on some machines is 4 bytes as well as pointers.
// Imagine an array of 4 elements and a linked list of 4 elements.
// While the capacity of the array may be bigger than 4 elems,
// it only uses 16 bytes of memory for used memory.
// As for linked list, it uses 32 bytes for the same number of elements.
// So, you'd better consider what elements you want to store too.
// 3.Linked list is a fragmentational memory while an array is contiguous block. It's important
// to bear that in mind if there's no way to allocate the whole array.
// A very rare phenomena nonetheless.
// 4.Reallocation of an array will take twice as much as the old array in space (no such problem
// with linked lists)
// 5. 1)Linked list insertion in the beginning is always O(1) while in array it's O(n)
//		2)Insertion at the end for an array (if it's not full) is O(1), 
//		while in linked list is O(n). If it's full, it's O(n) for an array.
//		3)Insertion in i-th position will be O(n) in both cases (but in case of linked list
//		there will be no shifting done!)
//		4)Removal will be very similar to the 3 scenarios above.
// 
// 6. Linked list is harder to implement.  
//
// Now let's implement Linked list:
// Our linked list will look like
//
// Name    first_elem   second_elem  past_the_end
// [link]->[data|link]->[data|link]->NULL
//
// Name is of class type.
// Name is a name of our forward-linked list.
// We'll make linked list of integers
// 
//


struct Node {
	int data;
	Node* next;
};


class linked_list {
	Node* head = NULL;
	size_t sz = 0;
public:
	size_t size(void) { return sz; }
	void print(void);
	void insert(int);
};

// Let's define some functions working with linked list: print() and insert()
// insert(int) inserts data in the beginning
// print(void) prints the whole list

void linked_list::insert(int toPrint) {
	Node *temp = new Node();
	temp->data = toPrint;
	temp->next = NULL;
	if (head != NULL)
		temp->next = head;
	head = temp;

}
void linked_list::print(void) {
	Node *temp = head;
	size_t i = 0;
	std::cout << "LINKED_LIST DATA:" << std::endl;
	while (temp != NULL) {
		std::cout << i << "th element: " << temp->data << std::endl;
		++i;
		temp = temp->next;
	}
	if (i == 0) {
		std::cout << "is empty" << std::endl;
	}
}


int main() {
	int arr[10] = {}; // static list
	int* arrDyn = new int[10]; // a dynamic list
	linked_list LL;
	for (int i = 0; i != 10; ++i) {
		LL.insert(i);
	}
	LL.print();
}
