#include <iostream>

/* author: Tuan Hoang
   email: minhtuan592a@gmail.com
   last fix date: 1/22/2019
   
   MIT license (C) Coppyright TuanHoang on github
   
problem: 
 According to computer architecture and operating system,
 an array data structure can not add or remote elements.
 We need to generate a data structure is able to do that
 
 LinkedList full methods:
 	- isEmpty()
	- pushHead( newElemnt)
        - pushBack( newElement)
	- insertAfter( index, newElement)
	- insertBefore( index, newElement)
	- freeAll()  -> delete all
	- popHead()
	- popBack()
	- getBack()
	- getHead()
	- length()
	- at( index)
	- removeAt( index)
	- insertSort( newElement)
	- indexOf( elemnt)  
*/

template <class T>
class Node{
public:
	T value;
	Node* next;
	
	
	Node()
	{
		value = 0;
		next = NULL;
	}
	
	~Node()
	{
		delete value;
		delete next;
		next = NULL;
	}
	
	Node(const T& value)
	{
		this->value = value;
		this->next = NULL;
	}
	
	
	Node* linkTo(Node* node)
	{
		this->next = node;
 		return this;
	}
	
};




template <class T>
class LinkedList{
	
	Node<T>* head;
	Node<T>* tail;
	
	
	Node<T>* nodeAt(int N)
	{
		Node<T>* cur = head;
		
		for(int i=0; i<N; i++)
			cur = cur->next;
			
		return cur;	
	}
	

	void remove_when_having_1_element()
	{
		delete head;
		head = tail = NULL;
	}
	
	
	Node<T>* getNodeHasValue(const T& lookupedValue)
	{
		Node<T>* cur = head;
		
		while (cur != NULL)
		{
			if (cur->value == lookupedValue)
				break;
			else
				cur = cur->next;
		}	

		return cur;	
	}

	
	
	
public:

	
	LinkedList()
	{
		head = tail = NULL;
	}
	
	

	bool isEmpty()
	{ 
		return head == NULL;
	}
	

	
	void pushHead(const T& newValue)
	{		
		if ( this->isEmpty())
		{
			head = tail = new Node<T>(newValue);
			return;
		}	
			
		Node<T>* newNode = new Node<T>(newValue);
		
		newNode->linkTo(head);
		
		head = newNode; 
	}
	
	

	void pushBack(const T& newValue)
	{
		if( isEmpty())
		{
			head  =  tail =  new Node<T>(newValue);
			return;
		}
		
		tail->linkTo(new Node<T>(newValue));
		
		tail = tail->next;
	}
	

	
	void insertAfter(int n, const T& newValue)
	{		
		Node<T>* A = nodeAt(n);
		Node<T>* B = A->next;
		Node<T>* newNode = new Node<T>(newValue);

		newNode->linkTo(B);
		A->linkTo(newNode);
		
		if(A == tail)
			tail = tail->next;
	}
	


	void insertBefore(int n, const T& newValue)
	{
		Node<T>* A = nodeAt(n);


        /*   step1:               A_vA -- B
                                         /
                                  NEW_vA
 		*/  
		Node<T>* newNode = new Node<T>;
		*newNode = *A;
		

		/*   step2:       A_vA      B
                            |     /
                            NEW_vA
 		*/  
		A->linkTo(newNode);
		

		/*   step3:      A_vNew     B
                         	|      /
                            NEW_vA
 		*/  
		A->value = newValue; 


		// if A is tail, newNode is new tail pos. the tail pass tail flag to newNode  
		if( A == tail )
			tail = tail->next;
	}
	

	
	void freeAll()
	{
		Node<T>* followerHead;
		
		while (head != NULL)
		{
			followerHead = head;
			head = head->next;
			delete followerHead;
		}
	}
	
	
	
	void popHead()
	{
		if(head == tail)
		{
			remove_when_having_1_element();
			return;
		}
		
		Node<T>* helper = head;
		
		head = head->next;
		
		delete helper; 
	}
	
	
	
	void popBack()
	{
		if( head == tail)
		{
			this->remove_when_having_1_element();	
			return;
		}
		
		Node<T>* cur = head;  
		while (cur->next != tail)
			cur = cur->next;
 		Node<T>* previousTail = cur;


		delete tail;
		tail = previousTail; 
		tail->linkTo(NULL);
	}
	

	
	T getBack()
	{
		return  tail->value;
	}


	
	T getHead()
	{
		return head->value;
	}
	
	
	
	int length()
	{
		int count = 0;
		for(Node<T>* cur = head; cur != NULL; cur = cur->next)
			count++;
			
		return count;
	}
	

	T at(int n)
	{ 
		return nodeAt(n)->value;
	}
	
	

	void removeAt(int n)
	{	
		// to delete A,  step1: let A become B, step 2: delete B
		
		if (head == tail)
		{
			remove_when_having_1_element();
			return;
		}
		
		Node<T>* A = nodeAt(n);
	
		if(A == tail)
			this->popBack();
		
		Node<T>* B = A->next;

		//step1: A become B
		*A = *B;
		
 		//step2:
		delete B;
	}
	
	
	
	
	void insertSort(const T& newValue)
	{	
		if( this->isEmpty()){
			this->pushBack(newValue);
			return;
		}
		
		Node<T>* A = (new Node<T>)->linkTo(head);
		Node<T>* B = head;

		
		while( B != NULL  &&  B->value < newValue)
		{
			A = A->next;
			B = B->next;
		}
		

		Node<T>* newNode = new Node<T>(newValue);
		A->linkTo(newNode);
		newNode->linkTo(B);
		

		if ( A == tail)
			tail = tail->next;

		if ( B == head)
			head = newNode;		
				
	}
	
	
    
	int getPosOf(const T& cmpValue)
	{		
		Node<T>* target = getNodeHasValue(cmpValue);
		if(target == NULL)
			return -1;
		
		int pos = 0;
		for ( Node<T>* cur = head; cur != target; cur = cur->next)	
			pos++;
		
		return pos;
	}
	



	void show(){
		std::cout << "---------------------------------------\n"; 
		std::cout << "length of list: " << this->length() << std::endl;
		std::cout << "elemetns : ";
		for ( Node<T>* cur = head; cur != NULL; cur = cur->next)	
			std::cout<< cur->value << ", ";
			
		std::cout<< std::endl;
		std::cout<< "head : " << getHead() << std::endl;
		std::cout<< "tail : " << getBack() << std::endl;
		std::cout << "---------------------------------------\n"; 
	}
	
};



int main(){
	LinkedList<int>* lst = new LinkedList<int>;
	lst->insertSort(5);
	lst->insertSort(2);
	lst->insertSort(3);
	lst->insertSort(4);
	lst->show();
}
