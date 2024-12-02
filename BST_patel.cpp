// ****************************************PROVIDED CODE STARTS****************************************
#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data) {
    struct node* node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* 1. If the tree is empty, set rootRef to the address of newly created node
 * 2. Otherwise, recur down the tree
*/
void insert(struct node** rootRef, int data) {
    if (*rootRef == NULL) {
        *rootRef = newNode(data);
    } else {
        if (data <= (*rootRef)->data) {
            insert(&((*rootRef)->left), data);
        } else {
            insert(&((*rootRef)->right), data);
        }
    }
}

/*
 * Sorted printing
 * left-root-right
*/
void printTreeInOrder(struct node* root) {
    if (root == NULL) {
        return;
    }
    printTreeInOrder(root->left);
    cout << (root->data) << " ";
    printTreeInOrder(root->right);
}

/*
 * root-left-right
*/
void printTreePreOrder(struct node* root) {
    if (root == NULL) {
        return;
    }
    cout << (root->data) << " ";
    printTreePreOrder(root->left);
    printTreePreOrder(root->right);
}

int size(struct node* root) {
    if (root == NULL) return 0;
    return (size(root->left) + size(root->right) + 1);
}

int maxDepth(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int lheight = maxDepth(root->left);
    int rheight = maxDepth(root->right);

    if (lheight > rheight) {
        return (lheight + 1);
    } else {
        return (rheight + 1);
    }
}

bool lookup(struct node* root, int target) {
    if (root == NULL) return false;

    if (root->data == target) return true;

    if (root->data > target) {
        return (lookup(root->left, target));
    } else {
        return (lookup(root->right, target));
    }
}

// No recursion
int findMaxValue(struct node* root) {
    struct node* temp = root;

    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp->data;
}

// With recursion
struct node* findMaxValueRec(struct node* root) {
    if (root->right == NULL) return root;

    return findMaxValueRec(root->right);
}

// ****************************************PROVIDED CODE ENDS****************************************

// MEHTOD ONE: TO FIND THE MAXIMUM ABSOLUTE DIFFERENCE WITHIN THE BINARY SEARCH TREE
// Helper methods start here

int smallestValue(struct node* root) {
    if (root == NULL) {
        return -1; // Indicate invalid case
    }

    struct node* curr = root;

    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr->data;
}

int largestValue(struct node* root) {
    if (root == NULL) {
        return -1; // Indicate invalid case
    }

    struct node* curr = root;

    while (curr->right != NULL) {
        curr = curr->right;
    }
    return curr->data;
}

// Helper methods end here

// Part one solution starts here

int maxDifference(struct node* root) {
    if (root == NULL) {
        return 0;
    }

    int min = smallestValue(root);
    int max = largestValue(root);
    return max - min;
}

// Part one solution ends here

// MEHTOD TWO: TO DELETE A NODE WITH SPECIFIED VALUE
// Helper methods start here

struct node* findMinNode(struct node* root) {
    struct node* curr = root;
    while (curr && curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

// Helper methods end here

// Part two solution starts here

node* deleteNode(node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }

        node* temp = findMinNode(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Part two solution ends here

void deleteTree(struct node* root) {
    if (root == NULL) return;
    deleteTree(root->left);  
    deleteTree(root->right); 
    delete root;           
}


int main() {
    struct node* root = NULL;

    insert(&root, 41);
    insert(&root, 20);
    insert(&root, 11);
    insert(&root, 29);
    insert(&root, 32);
    insert(&root, 65);
    insert(&root, 70);
    insert(&root, 30);
    insert(&root, 75);

    printTreePreOrder(root);
    cout << endl;

    cout << "Size: " << size(root) << endl;

    cout << "Absolute Max Diff: " << maxDifference(root) << endl;

    cout << "findMaxValue(): " << findMaxValue(root) << endl;
    cout << "findMaxValueRec(): " << findMaxValueRec(root)->data << endl;

    root = deleteNode(root, 29);
    cout << "After deleting 29 (Pre-order): ";
    printTreePreOrder(root);
    cout << endl;

    root = deleteNode(root, 75);
    cout << "After deleting 75 (Pre-order): ";
    printTreePreOrder(root);
    cout << endl;


    root = deleteNode(root, 41);
    cout << "After deleting 41 (Pre-order): ";

    printTreePreOrder(root);
    cout << endl;
    deleteTree(root);
    return 0;
}

