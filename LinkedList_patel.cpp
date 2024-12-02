//PROVIDED CODE STARTS
#include <iostream>
using namespace std;

struct node{
  int data;
  struct node* next;
};

void Push(struct node** headRef, int data){
  struct node* newNode = new struct node;
  newNode->data = data;
  newNode->next = *headRef;
  *headRef = newNode;
}	

void Print(struct node* head){
  struct node* current = head;

  while(current != NULL){
     cout << current->data << "->";
     current = current->next;
  }
}

int Length(struct node* head){

   struct node* current = head;
   int counter = 0;

   while(current != NULL){
     current = current->next;
     counter++;
   }
   return counter;

}

void AddToEnd(struct node** headRef, int data){

  struct node* current = *headRef;
  if(current == NULL){
     Push(headRef, data);
  }else{
     while(current->next != NULL){
        current = current->next;
     }
     Push( &(current->next), data);
  }
}

struct node* FindFromTheEnd(struct node* head, int k){
   struct node* current = head;
   struct node* runner = head;

   for(int i=0; (i<k); i++){
     if(runner == NULL){
       return NULL;
     }
     runner = runner->next;
   } 
   
   while(runner != NULL){
     current = current->next;
     runner = runner->next;
   }

   return current;

}

void InsertSorted(struct node** headRef, int data){
   struct node* newNode = new struct node;
   newNode->data = data;

   struct node* current = *headRef;
   if(current == NULL || (*headRef)->data >= data){
      newNode->next = *headRef;
      *headRef = newNode;
   }else{
   
      while( (current->next != NULL) && ((current->next)->data < data)  ){
          current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;	
   }
}

void RemoveNode(struct node** headRef, int data){
   struct node* current = *headRef;
   struct node* prev = NULL;

   if((*headRef)->data == data){   
      prev = *headRef;
      *headRef = (*headRef)->next;
      delete prev;
      return;
   }else{
     while(current != NULL){
        if(current->data > data){ 
          return;
	}
        if(current->data == data){  
          prev->next = current->next;
          delete current;
	  return;
	}
        prev = current;
	current = current->next;
     }
   }
}

bool RemoveDuplicatesSorted(struct node* head){
  
   bool removed = false;
   struct node* current = head;

   while(current && current->next){ 
     if (current->data == current->next->data){
        struct node* temp = current->next;
	current->next = temp->next;
	delete temp;
	removed = true;
     }else{
       current = current->next;
     }
   }
   return removed;

}
// PROVIDED CODE ENDS

// VALID PALINDROME CHECK STARTS

bool isPalindrome(struct node* head) {
    if (!head || !head->next) return true; 

    struct node* one = head;
    struct node* two = head;
    while (two && two->next) {
        one = one->next;
        two = two->next->next;
    }

    struct node* prev = NULL;
    struct node* curr = one;
    while (curr) {
        struct node* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    struct node* firstHalf = head;
    struct node* secondHalf = prev; 
    while (secondHalf) {
        if (firstHalf->data != secondHalf->data) {
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    return true;
}
// VALID PALINDROME CHECK ENDS

//MERGE LIST

node* mergeSortedLists(node* head1, node* head2) {
    node dummy;
    node* tail = &dummy;
    dummy.next = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            tail->next = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }

    if (head1 != NULL) {
        tail->next = head1;
    } else {
        tail->next = head2;
    }

    return dummy.next; 
}

void FreeList(node* head) {
    while (head != NULL) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

//MERGE LIST ENDS

int main() {
    struct node* head = NULL;

    AddToEnd(&head, 2);
    AddToEnd(&head, 3);
    AddToEnd(&head, 4);
    AddToEnd(&head, 3);
    AddToEnd(&head, 2);
	Print(head);
    cout <<endl<< "Test Case 1: ";
    if (isPalindrome(head)) {
        cout << "The list is a palindrome." << endl;
    } else {
        cout << "The list is not a palindrome." << endl;
    }

    // Test case 2: Non-palindrome list
    struct node* head2 = NULL;
    AddToEnd(&head2, 2);
    AddToEnd(&head2, 1);
    AddToEnd(&head2, 4);
    AddToEnd(&head2, 3);
    AddToEnd(&head2, 2);
	
	Print(head2);

    cout<< endl << "Test Case 2: ";
    if (isPalindrome(head2)) {
        cout << "The list is a palindrome." << endl;
    } else {
        cout << "The list is not a palindrome." << endl;
    }
	
	struct node* head3 = NULL;
    AddToEnd(&head3, 1);
    AddToEnd(&head3, 1);

    struct node* head4 = NULL;
    AddToEnd(&head4, 6);
    AddToEnd(&head4, 10);
    AddToEnd(&head4, 9);

    struct node* mergedHead = mergeSortedLists(head3, head4);

    cout << "Merged List: ";
    Print(mergedHead);
    cout << endl;
	
	FreeList(head);
	FreeList(head2);
	FreeList(head3);
    FreeList(head4);
    FreeList(mergedHead);
	
    return 0;
}
