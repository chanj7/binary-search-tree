

#ifndef BST_H
#define BST_H
#include <sstream>
#include <string>
using namespace std;

template <typename T>
class BST {
public:
	BST();                          // Constructor
	~BST();                         // Destructor
    BST(const BST &);               // Copy constructor
    BST& operator=(const BST &);    // Overloaded operator
	bool contains(T);               // if BST contains an item
	void insert(T);                 // inserts items into tree
	void remove(T);                 // remove item from BST
	string getPreOrderTraversal();  // returns preorder traversal
	string getInOrderTraversal();   // returns inorder traversal
	string getPostOrderTraversal(); // returns postorder traversal
    int getLevel(T);                // returns which level an item is at
    string getAncestors(T);         // returns the ancestors of an item
    int size();                     // returns size of the BST
    int getLeafCount();             // returns how many leaves are in the BST
    int getHeight();                // returns the height of the BST
    bool empty();                   // returns if the BST is empty or not
private:
	struct Node {                   // Node to be used to traverse BST
		T data;
		Node * left;
		Node * right;
	};
	Node * root;
	
	void getPreOrderTraversal(Node *, stringstream&);   // helper function for preorder traversal
    void getInOrderTraversal(Node *, stringstream&);    // helper function for inorder traversal
    void getPostOrderTraversal(Node *, stringstream&);  // helper function for postorder traversal
	bool contains(Node *, T);                           // helper function for contains
    void insert(Node *&, Node *&);                      // helper function for insert
	void remove(Node *&, T);                            // helper function for remove
	void makeDeletion(Node *&, T);                      // called when need to remove a node
	void destroyTree(Node *&);                          // called from destructor
    void getLevel(Node *, T, int&);                     // helper function for finding level of item
    void getLeafCount(Node *, int&);                    // helper function for counting number of leaves
    void size(Node *, int&);                            // helper function for finding size of BST
    int getHeight(Node *);                              // helper function to find height of BST
    void getAncestors(Node *, stringstream &, T);       // helper function to get string of ancestors
};

template <typename T>
BST<T>::BST() {
/**
 * Constructor of BST class; initializes root to nullptr
 */
    root = nullptr;
}

template <typename T>
BST<T>::~BST() {
/**
 * Destructor of BST class; calls destroyTree function
 */
    destroyTree(root);
}

template <typename T>
void BST<T>::destroyTree(Node *&ptr) {
/**
 * called from destructor; deletes all nodes in the BST
 * @param ptr passes in the root (named ptr) from the destructor
 */
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}


template <typename T>
BST<T>::BST(const BST &obj) {
/**
 * copy constructor of BST class
 * @param obj in reference to obj
 */
    obj.root = nullptr;
}

template <typename T>
BST<T>& BST<T>::operator=(const BST &obj) {
/**
 * overloaded equals operator function deletes the contents of one instance and copies it to another
 * @param obj passes in the reference to obj
 */
    if (this != &obj) {
        // deallocate memory
        destroyTree(root);
        // insert data into obj
        obj.insert(root->data);
    }
    return *this;
}

template <typename T>
int BST<T>::size() {
/**
 * size function determines how many nodes are in the BST
 * @return int of how many nodes were counted
 */
    int nodeCount = 0;
    size(root, nodeCount);
    return nodeCount;
}

template <typename T>
void BST<T>::size(Node *ptr, int & nodeCount) {
/**
 * helper function to size; increments the nodeCount variable
 * @param ptr pointer to a node
 * @param nodeCount reference to keep track of how many nodes are counted
 */
    if (ptr != nullptr) {
        nodeCount++;
        size(ptr->left, nodeCount);
        size(ptr->right, nodeCount);
    }
}

template <typename T>
bool BST<T>:: contains(T item) {
/**
 * contains function determines if the BST contains a certain item
 * @param item the thing we are looking for in the BST
 * @return boolean returns true or false depending if item is in BST or not
 */
    bool doesContain = contains(root, item);
    if (doesContain)
        return true;
    else
        return false;
}

template <typename T>
bool BST<T>::contains(Node * ptr, T item) {
/**
 * helper function for contains traverses through BST to see if contains item
 * @param ptr the node being referenced
 * @param item the item looking for
 * @return whether or not item was found in the BST
 */
    if (ptr == nullptr)
        return false;
    else {
        if (ptr->data == item)
            return true;
        else if (ptr->data > item)
            return contains(ptr->left, item);
        else if (ptr->data < item)
            return contains(ptr->right, item);
    }
    return false;
}

template <typename T>
void BST<T>::insert(T item) {
/**
 * insert function inserts a new item into the BST
 * @param item new thing to add as a node to the BST
 */
    Node * newNode = new Node;
    newNode->data = item;
    newNode->left = newNode->right = nullptr;

    insert(root, newNode);
}

template <typename T>
void BST<T>::insert(Node *& ptr, Node *& newNode) {
/**
 * helper function for insert; places in correct spot
 * @param ptr the node we are at when traversing
 * @param newNode the new node we want to add into the BST
 */
    if (ptr == nullptr)
        ptr = newNode;
    else if (ptr->data > newNode->data)
        insert(ptr->left, newNode);
    else
        insert(ptr->right, newNode);
}

template <typename T>
void BST<T>::remove(T item) {
/**
 * remove function removes one item
 * @param item the item to be removed
 */
    remove(root, item);
}

template <typename T>
void BST<T>::remove(Node *& ptr, T item) {
/**
 * helper function for remove; finds item and deletes it
 * @param ptr the node we are referencing
 * @param item the item to be removed
 */
    if (ptr != nullptr) {
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr, item);
    }
}

template <typename T>
void BST<T>::makeDeletion(Node *& ptr, T item) {
/**
 * makeDeletion function called from remove function to delete node
 * @param ptr the node we are referencing
 * @param item the item to be deleted
 */
    Node * curr = nullptr;
    if (ptr != nullptr) {
        if (ptr->left == nullptr) {
            curr = ptr;
            ptr = ptr->right;
            delete curr;
        } else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr;
        } else {
            curr = ptr->right;
            while (curr->left != nullptr)
                curr = curr->left;
            ptr->data = curr->data;
            remove(ptr->right, curr->data);
        }
    }
}

template <typename T>
string BST<T>::getPreOrderTraversal() {
/**
 * getPreOrderTraversal function returns the string of preorder traversal of the BST
 * @return the preorder traversal as a string
 */
    stringstream sPre;
    getPreOrderTraversal(root, sPre);
    string str = sPre.str();
    return str;
}

template <typename T>
void BST<T>::getPreOrderTraversal(Node * ptr, stringstream &sPre) {
/**
 * helper function for preorder traversal; adds values to a stringstream
 * @param ptr the node we are referencing
 * @param sPre the reference to the stringstream to hold values
 */
    string str;
    if (ptr != nullptr) {
        sPre << ptr->data << " ";
        str = sPre.str();
        getPreOrderTraversal(ptr->left, sPre);
        getPreOrderTraversal(ptr->right, sPre);
    }
}

template <typename T>
string BST<T>::getInOrderTraversal() {
/**
 * getInOrderTraversal function returns the string of inorder traversal of the BST
 * @return the inorder traversal as a string
 */
    stringstream sIn;
    getInOrderTraversal(root, sIn);
    string str = sIn.str();
    return str;
}

template <typename T>
void BST<T>::getInOrderTraversal(Node * ptr, stringstream &sIn) {
/**
 * helper function for inorder traversal; adds values to a stringstream
 * @param ptr the node we are referencing
 * @param sIn the reference to the stringstream to hold values
 */
    string str;
    if (ptr != nullptr) {
        getInOrderTraversal(ptr->left, sIn);
        sIn << ptr->data << " ";
        str = sIn.str();
        getInOrderTraversal(ptr->right, sIn);
    }
}

template <typename T>
string BST<T>::getPostOrderTraversal() {
/**
 * getPostOrderTraversal function returns the string of postorder traversal of the BST
 * @return the postorder traversal as a string
 */
    stringstream sPost;
    getPostOrderTraversal(root, sPost);
    string str = sPost.str();
    return str;
}

template <typename T>
void BST<T>::getPostOrderTraversal(Node * ptr, stringstream& sPost) {
/**
 * helper function for postorder traversal; adds values to a stringstream
 * @param ptr the node we are referencing
 * @param sPost the reference to the stringstream to hold values
 */
    string str;
    if (ptr != nullptr) {
        getPostOrderTraversal(ptr->left, sPost);
        getPostOrderTraversal(ptr->right, sPost);
        sPost << ptr->data << " ";
        str = sPost.str();
    }
}

template <typename T>
int BST<T>::getLevel(T item) {
/**
 * getLevel function finds the level a specific item can be found
 * @param item the item we want to find the level for
 * @return the level the item is found
 */
    int level = 0;
    getLevel(root, item, level);
    return level;
}

template <typename T>
void BST<T>::getLevel(Node * ptr, T item, int &level) {
/**
 * helper function for getLevel; traverses through BST until finds item
 * @param ptr the node we are referencing
 * @param item the item we want to find to figure out the level
 * @param level the level we are currently at
 */
    if (ptr == nullptr)
        return;
    if (ptr->data == item)
        return;
    else if (ptr->data > item) {
        getLevel(ptr->left, item, ++level);
    }
    else {
        getLevel(ptr->right, item, ++level);
    }
}

template <typename T>
string BST<T>::getAncestors(T item) {
/**
 * getAncestors function finds the ancestors of a given item
 * @param item the item we want to find ancestors for
 * @return the string of ancestors for a given item
 */
    stringstream ss;
    getAncestors(root, ss, item);
    string nums;
    string reverse = "";
    getline(ss, nums);
    istringstream iss {nums};
    while (iss) {
        string eachNum;
        iss >> eachNum;
        reverse = eachNum + " " + reverse;
    }

    return reverse;
}

template <typename T>
void BST<T>::getAncestors(Node * ptr, stringstream &str, T item) {
/**
 * helper function for getAncestors; traverses BST to find item and its ancestors
 * @param ptr the node we are referencing
 * @param str reference to stringstream to collect ancestors
 * @param item the item want to find ancestors for
 */
    if (ptr == nullptr) {
        getAncestors(ptr, str, item);
    }
    if (ptr->data != item) {
        str << ptr->data << " ";
        string ss = str.str();
        if (ptr->data > item) {
            getAncestors(ptr->left, str, item);
        }
        else {
            getAncestors(ptr->right, str, item);
        }
    }
}

template <typename T>
int BST<T>::getLeafCount() {
/**
 * getLeafCount function counts how many leaves are in the BST
 * @return the number of leaves in the BST
 */
    int leafCount = 0;
    getLeafCount(root, leafCount);
    return leafCount;
}

template <typename T>
void BST<T>::getLeafCount(Node * ptr, int& leafCount) {
/**
 * helper function for getLeafCount traverses BST to count the number of leaves
 * @param ptr the node that is being referenced
 * @param leafCount reference to keep track of how many leaves are found
 */
    if (ptr == nullptr) {
        return;
    }
    if (ptr->left == nullptr && ptr->right == nullptr) {
        leafCount++;
    }
    getLeafCount(ptr->left, leafCount);
    getLeafCount(ptr->right, leafCount);
}

template <typename T>
int BST<T>::getHeight() {
/**
 * getHeight function finds the height of the BST
 * @return the height of the BST
 */
    int height = getHeight(root);
    return height;
}

template <typename T>
int BST<T>::getHeight(Node * ptr) {
/**
 * helper function for getHeight traverses through BST to find maximum depth
 * @param ptr the node being referenced
 * @return the height of the BST
 */
    if (ptr == nullptr) {
        return 0;
    }

    int leftHeight = getHeight(ptr->left);
    int rightHeight = getHeight(ptr->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    else if (leftHeight < rightHeight) {
        return rightHeight + 1;
    }
    else {
        return leftHeight + 1;
    }
}

template <typename T>
bool BST<T>::empty() {
/**
 * empty function determines if the BST is empty or not
 * @return boolean if BST is empty or not
 */
    if (root == nullptr)
        return true;
    else
        return false;
}

#endif
