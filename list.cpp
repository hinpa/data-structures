// list implementation
#include <iostream>

// A static list is a data structure that satisfies these points:
// 1. Store given amount of elements of given data type
// 2. Read/Write element at given position
// 3. Read element at given position
// An implementation of static list is an array

// A dynamic list:
// 1. If no elements, the size is 0
// 2. Can insert
// 3. Can remove
// 4. Count
// 5. R/W element access
// 6. Stores particular data type.
// A typical dynamic array or vector is an example of a dynamic list
// However, arrays and vectors have problems with memory inefficiency.
// You have to always allocate memory with some capacity
// What if we've never get to use all the capacity? 
// Another problem is if we still get to use all capacity we have to reallocate the whole thing
// so that all elements fit in one contigous block of memory.
// Let's go through array implementation list big O notation:
// Insert is O(n) (including pushing back)
// Removal is O(n)
// R/W access is O(1)
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
	void push_front(int val) { insert(val); }
	void insert(int,size_t);
	void push_back(int val) { insert(val, sz); };
	void remove(size_t);
	void pop_front(void) { remove(0); }
	void pop_back(void) { remove(sz - 1); }
	int& get(size_t); // gets data member
	void reverse_rec(void); // recursive reverse
	void reverse_it(void); // iterative reverse
	void rprint(void); // check reverse print before writing recursive reverse
	void rec_print(void); // before writing recursive reverse, check recursive print
};


int& linked_list::get(size_t pos) {
	Node* temp = head;
	for (int i = 0; i != pos; ++i) {
		temp = temp->next;
	}
	return temp->data;
}

void linked_list::reverse_rec() {
	if (head == NULL) 
		return;
	static Node *next = head; // a static pointer throughout calls
	Node *curr = next; // local to the call
	if (next->next == NULL) { head = next; return;}
	next = next->next; // we move to the next node
	reverse_rec(); // and call function
	// we'll have adjacent next and curr
	// curr will have next as its next element
	// first we save pointer to 
	curr->next = next->next;
	next->next = curr;
	next = curr;
}

void linked_list::reverse_it() {
	// works even for empty and 1-element forward linked list
	Node *curr = head, *prev = NULL, *next;
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
}

void linked_list::remove(size_t pos) {
	if (pos >= sz || pos < 0 ) { 
		return; 
	}

	Node *traverse = head; 

	if (pos == 0) { 
		head = head->next;
		delete traverse;
		--sz;
		return;
	}

	for (int i = 0; i < pos - 1; ++i) {
		traverse = traverse->next;
	}
	
	Node *toDelete = traverse->next;
	traverse->next = toDelete->next;
	delete toDelete;
	--sz;
	
}



void linked_list::insert(int toInsert) { // O(1);
	Node *temp = new Node(); // create new node with data passed
	temp->data = toInsert;
	temp->next = NULL;
	if (head != NULL) // if linked list is not empty, we point to the first element
		temp->next = head;
	head = temp; // then update the first element
 	++sz;	
}

void linked_list::insert(int valPush, size_t pos) { // O(n)
	if (pos > sz || pos < 0) {// not in range? bad 
		std::cerr << "Inserting in invalid position";
		return;
	}
	else if (pos == 0) {
		insert(valPush);
		return;
	}

	Node *toPush = new Node(); // create new node with value to push
	toPush->data = valPush;
	
	Node *temp = head;
	for (int i = 0; i != pos-1; ++i) {
		temp = temp->next;
	}

	toPush->next = temp->next; // link to the next data block
	temp->next = toPush; // link to our pushed node
	++sz; // add to size
}

void linked_list::rec_print() {
	int toPrint;
	static Node *curr = head;
	if (curr == NULL) {
		curr = head;
		return;
	}
	toPrint = curr->data;
	curr = curr->next;
	std::cout << toPrint;
	rec_print();
}

void linked_list::rprint() {
	int toPrint;
	static Node *curr = head;
	static int cntcall = 0;
	int currcall = cntcall;
	++cntcall;
	if (curr == NULL) {
		curr = head;
		cntcall = 0;
		printf("LINKED_LIST(size=%zu,rprint() method):\n", sz);
		return;
	}
	toPrint = curr->data;
	curr = curr->next;
	rprint();
	printf("%d element: %d\n",currcall,toPrint);
}

void linked_list::print(void) {
	Node *temp = head;
	size_t i = 0;
	std::cout << "LINKED_LIST DATA(size=" << this->sz << ", iterative print):" << std::endl;
	while (temp != NULL) {
		std::cout << i << " element: " << temp->data << std::endl;
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
	LL.print();
	LL.rprint();
	LL.rec_print();
	LL.reverse_it();
	LL.reverse_rec();
	for (int i = 0; i != 10; ++i) {
		LL.push_back(i);
	}
	LL.print();
	LL.reverse_rec();
	LL.print();
}
