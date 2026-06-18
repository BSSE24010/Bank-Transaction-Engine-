#ifndef ALL_STRUCTURES_H
#define ALL_STRUCTURES_H

#pragma once // modern alternative of include guards added by my vs code extension (i know nothing about it hehe)

#include <iostream>
using namespace std;

//treeNode implemented by Izza
template <typename T>
class TreeNode
{
    T data;
    TreeNode<T> **children;
    int childrenCount;

public:
    TreeNode(T value)
    {
        data = value; // constructor
        childrenCount = 0;
        children = nullptr;
    }
    ~TreeNode()
    {
        if (children != nullptr)
        {
            delete[] children;
            children = nullptr;
        }
    }

    TreeNode<T> *getChild(int index)
    {
        if (index < 0 || index >= childrenCount)
        { // if index out of bound
            return nullptr;
        }
        else
        {
            return children[index]; // if valid index return child
        }
    }
    T getData()
    {
        return data; // return data
    }
    int getChildrenCount()
    {
        return childrenCount; // return no of children of specific node
    }
    void addChild(TreeNode<T> *node)
    {
        TreeNode<T> **nc = new TreeNode<T> *[childrenCount + 1];
        for (int i = 0; i < childrenCount; i++)
        {
            nc[i] = children[i]; // copying previous children
        }
        nc[childrenCount] = node;
        childrenCount++;
        delete[] children;
        children = nc;
    }

    void setChildrenCount(int c)
    {
        childrenCount = c;
    }
    void setChildrenArray(TreeNode<T> *arr[])
    {
        children = arr;
    }
    TreeNode<T> **getChildrenArray()
    {
        return children;
    }

    void setChild(int x, TreeNode<T> *n)
    {
        if (x < 0 || x > childrenCount)
        {
            return;
        }
        else
        {
            children[x] = n;
        }
    }
};
//Tree implemented by izza
template <typename T>
class Tree
{
    TreeNode<T> *root;

public:
    Tree()
    {
        root = nullptr; // initially root is nullptr
    }

    ~Tree()
    {
        del(root);
    }

    void del(TreeNode<T> *n)
    {
        if (n == nullptr)
        {
            return;
        }

        for (int i = 0; i < n->getChildrenCount(); i++)
        {
            del(n->getChild(i));
        }

        delete n;
    }

    bool insert(TreeNode<T> *n, T pd, TreeNode<T> *nd)
    {
        if (n->getData() == pd)
        {
            n->addChild(nd); // if data of node is equal to parent data then, new node will be added in its array of children
            return true;     // so that I can know that value is inserted succesfully
        }
        for (int i = 0; i < n->getChildrenCount(); i++)
        {
            bool t = insert(n->getChild(i), pd, nd); // if the children of its node inserted the new node then, they would return true
            if (t)
            {
                return true; // if returned true, I will not execute further and will exit
            }
        }
        return false; // if not inserted till now, then, I will return false
    }

    TreeNode<T> *findNODE(TreeNode<T> *n, T pd)
    {
        if (n->getData() == pd)
        {
            return n; // if the data of current node is equal to intended data then, I will return this node
        }
        for (int i = 0; i < n->getChildrenCount(); i++)
        {
            TreeNode<T> *t = findNODE(n->getChild(i), pd); // for searching in the array of children of each child
            if (t != nullptr)
            {
                return t; // if node is found in its children then, no need to execute further
            }
        }
        return nullptr; // if still not found, return nullptr
    }

    void insertNode(T parentData, T value)
    {
        TreeNode<T>* t = new TreeNode<T>(value);

    // Case 1: Tree empty → create root
    if (root == nullptr)
    {
        root = t;
        //cout << "Root inserted successfully"<<endl;
        return;
    }

    // Case 2: Insert as child
    bool inserted = insert(root, parentData, t);

    if (!inserted)
    {
        cout << "Parent Not Found" << endl;
        delete t; // avoid memory leak
    }
    else
    {
        cout << "Inserted successfully" << endl;
    }
    }

    TreeNode<T> *findNode(T data)
    {
        return findNODE(root, data);
    }

    TreeNode<T> *getRoot()
    {
        return root;
    }

    int getH(TreeNode<T> *n)
    {
        if (n == nullptr)
        {
            return -1;
        }
        if (n->getChildrenCount() == 0)
        {
            return 0;
        }
        int o = n->getChildrenCount();
        int arr[o];
        for (int i = 0; i < n->getChildrenCount(); i++)
        {
            int l = getH(n->getChild(i));
            arr[i] = l;
        }
        int max = -1;
        for (int j = 0; j < o; j++)
        {
            if (arr[j] > max)
            {
                max = arr[j];
            }
        }
        return 1 + max;
    }

    int getHeight(T data)
    {
        TreeNode<T> *n = findNODE(root, data);
        int h = getH(n);
        return h;
    }

    int getDegree(T data)
    {
        TreeNode<T> *n = findNODE(root, data);
        if (n == nullptr)
        {
            return -1;
        }
        return n->getChildrenCount();
    }

    TreeNode<T> *findPARENT(TreeNode<T> *n, T data)
    {
        if (n == nullptr)
        {
            return nullptr;
        }

        for (int i = 0; i < n->getChildrenCount(); i++)
        {
            if (n->getChild(i)->getData() == data)
            {
                return n;
            }
            TreeNode<T> *found = findPARENT(n->getChild(i), data);
            if (found != nullptr)
            {
                return found;
            }
        }
        return nullptr;
    }

    void removeChd(TreeNode<T> *parent, int in)
    {
        int c = parent->getChildrenCount();
        if (in < 0 || in >= c)
        {
            return;
        }

        TreeNode<T> **newArr = new TreeNode<T> *[c - 1];
        int j = 0;
        for (int i = 0; i < c; i++)
        {
            if (i == in)
            {
                continue;
            }
            newArr[j] = parent->getChild(i);
            j++;
        }
        parent->setChildrenCount(c - 1);

        delete[] parent->getChildrenArray();
        parent->setChildrenArray(newArr);
    }

    void deleteNode(T data)
    {
        if (root == nullptr)
        {
            return;
        }
        if (root->getData() == data)
        {
            if (root->getChildrenCount() == 0)
            {
                delete root;
                root = nullptr;
                return;
            }
            TreeNode<T> *nR = root->getChild(0); // set first node in place of node to delete
            for (int i = 1; i < root->getChildrenCount(); i++)
            {
                nR->addChild(root->getChild(i)); // now, add children of root to new root
            }
            delete root;
            root = nR;
            return;
        }

        TreeNode<T> *parent = findPARENT(root, data);
        if (parent == nullptr)
        {
            return;
        }

        int x = -1;
        for (int i = 0; i < parent->getChildrenCount(); i++)
        {
            if (parent->getChild(i)->getData() == data)
            {
                x = i;
                break;
            }
        }
        if (x == -1)
        {
            return;
        }

        TreeNode<T> *t = parent->getChild(x);
        int childCount = t->getChildrenCount();

        if (childCount == 0)
        {
            removeChd(parent, x);
            delete t;
            return;
        }

        TreeNode<T> *p = t->getChild(0); // store first child to place in place of node to be deleted

        for (int i = 1; i < childCount; i++)
        {
            p->addChild(t->getChild(i)); // to attach the remaining childre of node to be deleted to node that is promoted
        }

        parent->setChild(x, p);

        delete t;
    }

    void pre_order(TreeNode<T> *n)
    {
        if (n == nullptr)
        {
            return;
        }
        else
        {
            cout << n->getData() << " ";
            for (int i = 0; i < n->getChildrenCount(); i++)
            {
                pre_order(n->getChild(i));
            }
        }
    }

    void print_pre0rder(T data)
    {
        TreeNode<T> *n = findNODE(root, data);
        pre_order(n);
    }

    void in_order(TreeNode<T> *n)
    {
        if (n == nullptr)
        {
            return;
        }
        else
        {
            int k = n->getChildrenCount() / 2;
            for (int j = 0; j < k; j++)
            {
                in_order(n->getChild(j));
            }
            cout << n->getData() << " ";
            for (int l = k; l < n->getChildrenCount(); l++)
            {
                in_order(n->getChild(l));
            }
        }
    }

    void print_in0rder(T data)
    {
        TreeNode<T> *n = findNODE(root, data);
        in_order(n);
    }

    void post_order(TreeNode<T> *n)
    {
        if (n == nullptr)
        {
            return;
        }
        else
        {
            for (int i = 0; i < n->getChildrenCount(); i++)
            {
                post_order(n->getChild(i));
            }
        }
        cout << n->getData() << " ";
    }

    void print_post0rder()
    {
        post_order(root);
    }
};

// ================ TreeNode ==================
//implemented by azka
template <typename T>
class TreeNodeB
{
    T data;
    TreeNodeB *left;
    TreeNodeB *right;

public:
    TreeNodeB(T val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }

    void setData(T d) { data = d; }
    void setLeftChild(TreeNodeB *node) { left = node; }
    void setRightChild(TreeNodeB *node) { right = node; }

    T& getData() { return data; }
    T& getData1() { 
        return data;
    }
    TreeNodeB *getLeftChild() const { return left; }
    TreeNodeB *getRightChild() const { return right; }
};

//============== Node of queue ================
//implemented by azka
template <typename T>
class NodeQ
{
    T data;
    NodeQ<T> *next;

public:
    NodeQ(T d)
    {
        data = d;
        next = nullptr;
    }

    ~NodeQ()
    {
        next = nullptr;
    }

    NodeQ<T> *getNext()
    {
        return next;
    }

    void setNext(NodeQ<T> *var)
    {
        next = var;
    }

    T getData()
    {
        return data;
    }

    void setData(T data)
    {
        this->data = data;
    }
};

// ============= LinkedQueue ============
//implemented by azka
template <typename T>
class LinkedQueue
{
    NodeQ<T> *front;
    NodeQ<T> *rear;
    int size;

public:
    LinkedQueue()
    {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    ~LinkedQueue()
    {
        NodeQ<T> *temp = front;
        while (temp != nullptr)
        {
            NodeQ<T> *next = temp->getNext();
            delete temp;
            temp = next;
        }
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void enqueue(T data)
    {
        NodeQ<T> *newNode = new NodeQ<T>(data);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->setNext(newNode);
            rear = newNode;
        }
        size++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "list is empty" << endl;
            return T();
        }

        NodeQ<T> *temp = front;
        T var = temp->getData();
        front = front->getNext();

        if (front == nullptr)
            rear = nullptr;

        delete temp;
        size--;
        return var;
    }

    T peek()
    {
        if (isEmpty())
        {
            cout << "list is empty" << endl;
            return T();
        }
        return front->getData();
    }

    void print()
    {
        NodeQ<T> *temp = front;
        while (temp != nullptr)
        {
            cout << "data is of template type: " << temp->getData() << endl;
            temp = temp->getNext();
        }
        cout << endl;
    }
    int getSize() const {
        return size;
    }
    
    NodeQ<T>* getFrontNode() const {
        return front;
    }
    
    // to ensure CIRCULAR BEHAVIOR
    void moveToRear() {
        if (size <= 1) {
        return; 
    }
    // dequeue
    NodeQ<T>* oldFront = front;
    front = front->getNext();
    // to reset old front next to nullptr
    oldFront->setNext(nullptr); 
    
    // enqueue
    rear->setNext(oldFront);
    rear = oldFront;
    }
};

// ============ BinarySearchTree ===========
//implemented by azka
template <typename T>
class BinarySearchTree
{
    TreeNodeB<T> *root;

    void deleteTree(TreeNodeB<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteTree(node->getLeftChild());
        deleteTree(node->getRightChild());

        delete node;
        node = nullptr;
    }

public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    ~BinarySearchTree()
    {
        deleteTree(root);
    }

    TreeNodeB<T> *getRoot()
    {
        return root;
    }

    void insertNodeInBST(T value)
    {
        TreeNodeB<T> *newNode = new TreeNodeB<T>(value);

        if (root == nullptr)
        {
            root = newNode;
            return;
        }

        TreeNodeB<T> *current = root;
        TreeNodeB<T> *parent = nullptr;

        while (current != nullptr)
        {
            parent = current;

            if (value < current->getData())
            {
                current = current->getLeftChild();
            }
            else
            {
                current = current->getRightChild();
            }
        }

        if (value < parent->getData())
        {
            parent->setLeftChild(newNode);
        }
        else
        {
            parent->setRightChild(newNode);
        }
    }

    bool searchNode(T value)
    {
        TreeNodeB<T> *curr = root;

        while (curr != nullptr)
        {
            if (value == curr->getData())
                return true;
            else if (value < curr->getData())
                curr = curr->getLeftChild();
            else
                curr = curr->getRightChild();
        }
        return false;
    }

    TreeNodeB<T> *FindNodeInBST(T value)
    {
        TreeNodeB<T> *current = root;
        while (current != nullptr)
        {
            if (current->getData() == value)
            {
                return current;
            }
            else if (current->getData() > value)
            {
                current = current->getLeftChild();
            }
            else
            {
                current = current->getRightChild();
            }
        }
        return nullptr;
    }

    TreeNodeB<T> *deleteNodeHelper(TreeNodeB<T> *node, T value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (value < node->getData())
        {
            node->setLeftChild(deleteNodeHelper(node->getLeftChild(), value));
        }
        else if (value > node->getData())
        {
            node->setRightChild(deleteNodeHelper(node->getRightChild(), value));
        }
        else
        {
            // CASE 1 Leaf node
            if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
            {
                delete node;
                return nullptr;
            }

            // CASE 2 with one right child
            else if (node->getLeftChild() == nullptr)
            {
                TreeNodeB<T> *temp = node->getRightChild();
                delete node;
                return temp;
            }

            // CASE 3 with One left  child
            else if (node->getRightChild() == nullptr)
            {
                TreeNodeB<T> *temp = node->getLeftChild();
                delete node;
                return temp;
            }

            // CASE 4 with Two children
            else
            {

                TreeNodeB<T> *smallestNode = node->getRightChild();
                while (smallestNode->getLeftChild() != nullptr)
                {
                    smallestNode = smallestNode->getLeftChild();
                }

                node->setData(smallestNode->getData());
                node->setRightChild(deleteNodeHelper(node->getRightChild(), smallestNode->getData()));
            }
        }
        return node;
    }

    void deleteNode(T value)
    {
        root = deleteNodeHelper(root, value);
    }

    void printLevelOrderForBST()
    {
        if (root == nullptr)
        {
            cout << "Tree is empty\n";
            return;
        }

        LinkedQueue<TreeNodeB<T> *> q;
        q.enqueue(root);

        while (!q.isEmpty())
        {
            TreeNodeB<T> *temp = q.dequeue();
            cout << temp->getData() << " ";

            if (temp->getLeftChild() != nullptr)
            {
                q.enqueue(temp->getLeftChild());
            }
            if (temp->getRightChild() != nullptr)
            {
                q.enqueue(temp->getRightChild());
            }
        }

        cout << endl;
    }

    void inorderPrintHelper(TreeNodeB<T> *node)
    {
        if (node == nullptr)
            return;

        inorderPrintHelper(node->getLeftChild());
        cout << node->getData() << " ";
        inorderPrintHelper(node->getRightChild());
    }

    void inorderPrintForBST()
    {
        inorderPrintHelper(root);
        cout << endl;
    }

    void preorderPrintHelper(TreeNodeB<T> *node)
    {
        if (node == nullptr)
            return;

        cout << node->getData() << " ";
        preorderPrintHelper(node->getLeftChild());
        preorderPrintHelper(node->getRightChild());
    }

    void preorderPrintForBST()
    {
        preorderPrintHelper(root);
        cout << endl;
    }

    void postorderPrintHelper(TreeNodeB<T> *node)
    {
        if (node == nullptr)
            return;

        postorderPrintHelper(node->getLeftChild());
        postorderPrintHelper(node->getRightChild());
        cout << node->getData() << " ";
    }

    void postorderPrintForBST()
    {
        postorderPrintHelper(root);
        cout << endl;
    }
};

// ================== BINARY TREE ===============
//implemented by azka
template <typename T>
class BinaryTree
{
    TreeNodeB<T> *root;

    void deleteTree(TreeNodeB<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteTree(node->getLeftChild());
        deleteTree(node->getRightChild());

        delete node;
        node = nullptr;
    }

public:
    BinaryTree()
    {
        root = nullptr;
    }

    ~BinaryTree()
    {
        deleteTree(root);
    }

    TreeNodeB<T> *getRoot()
    {
        return root;
    }

    void insertNode(T data)
    {
        TreeNodeB<T> *newNode = new TreeNodeB<T>(data);

        if (root == nullptr)
        {
            root = newNode;
            return;
        }

        LinkedQueue<TreeNodeB<T> *> q;
        q.enqueue(root);

        while (!q.isEmpty())
        {
            TreeNodeB<T> *temp = q.dequeue();

            if (temp->getLeftChild() != nullptr)
            {
                q.enqueue(temp->getLeftChild());
            }
            else
            {
                temp->setLeftChild(newNode);
                return;
            }

            if (temp->getRightChild() != nullptr)
            {
                q.enqueue(temp->getRightChild());
            }
            else
            {
                temp->setRightChild(newNode);
                return;
            }
        }
    }

    int getHeightHelper(TreeNodeB<T> *node)
    {
        if (node == nullptr)
        {
            return -1;
        }
        int max = 0;
        int leftHt = getHeightHelper(node->getLeftChild());
        int RightHt = getHeightHelper(node->getRightChild());
        if (leftHt > RightHt)
        {
            max = leftHt;
        }
        else
        {
            max = RightHt;
        }
        return 1 + max;
    }

    int getTreeHeight()
    {
        return getHeightHelper(root);
    }

    TreeNodeB<T> *findNodeHelper(T data, TreeNodeB<T> *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->getData() == data)
        {
            return node;
        }
        TreeNodeB<T> *left = findNodeHelper(data, node->getLeftChild());
        if (left != nullptr)
        {
            return left;
        }
        TreeNodeB<T> *right = findNodeHelper(data, node->getRightChild());
        return right;
    }

    TreeNodeB<T> *findNode(T data)
    {
        return findNodeHelper(data, root);
    }

    int getHeightNode(T data)
    {
        TreeNodeB<T> *f = findNodeHelper(data, root);
        if (f == nullptr)
        {
            return -1;
        }
        return getHeightHelper(f);
    }

    bool isFull()
    {
        if (root == nullptr)
        {
            return true;
        }

        LinkedQueue<TreeNodeB<T> *> q;
        q.enqueue(root);

        while (!q.isEmpty())
        {
            TreeNodeB<T> *current = q.dequeue();

            TreeNodeB<T> *Left = current->getLeftChild();
            TreeNodeB<T> *Right = current->getRightChild();

            if (Left != nullptr && Right != nullptr)
            {
                q.enqueue(Left);
                q.enqueue(Right);
            }
            else if (Left == nullptr && Right == nullptr)
            {
                continue;
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    void deleteNode(T data)
    {
        if (root == nullptr)
            return;

        TreeNodeB<T> *var = findNodeHelper(data, root);
        if (var == nullptr)
        {
            cout << "such type of node not exist in tree" << endl;
            return;
        }

        LinkedQueue<TreeNodeB<T> *> q;
        q.enqueue(root);
        TreeNodeB<T> *current = nullptr;

        while (!q.isEmpty())
        {
            current = q.dequeue();
            if (current->getLeftChild() != nullptr)
            {
                q.enqueue(current->getLeftChild());
            }
            if (current->getRightChild() != nullptr)
            {
                q.enqueue(current->getRightChild());
            }
        }

        TreeNodeB<T> *last = current;
        var->setData(last->getData());

        q.enqueue(root);
        while (!q.isEmpty())
        {
            TreeNodeB<T> *parent = q.dequeue();

            if (parent->getLeftChild() == last)
            {
                parent->setLeftChild(nullptr);
                delete last;
                return;
            }
            if (parent->getRightChild() == last)
            {
                parent->setRightChild(nullptr);
                delete last;
                return;
            }

            if (parent->getLeftChild() != nullptr)
            {
                q.enqueue(parent->getLeftChild());
            }
            if (parent->getRightChild() != nullptr)
            {
                q.enqueue(parent->getRightChild());
            }
        }
    }

    void printLevelOrderForBinary()
    {
        if (root == nullptr)
        {
            cout << "Tree is empty\n";
            return;
        }

        LinkedQueue<TreeNodeB<T> *> q;
        q.enqueue(root);

        while (!q.isEmpty())
        {
            TreeNodeB<T> *temp = q.dequeue();
            cout << temp->getData() << " ";

            if (temp->getLeftChild() != nullptr)
            {
                q.enqueue(temp->getLeftChild());
            }
            if (temp->getRightChild() != nullptr)
            {
                q.enqueue(temp->getRightChild());
            }
        }

        cout << endl;
    }

    void inorderPrintHelper(TreeNodeB<T> *node)
    {
        if (node == nullptr)
            return;

        inorderPrintHelper(node->getLeftChild());
        cout << node->getData() << " ";
        inorderPrintHelper(node->getRightChild());
    }

    void inorderPrintForBinary()
    {
        inorderPrintHelper(root);
        cout << endl;
    }

    void preorderPrintHelper(TreeNodeB<T> *node)
    {
        if (node == nullptr)
            return;

        cout << node->getData() << " ";
        preorderPrintHelper(node->getLeftChild());
        preorderPrintHelper(node->getRightChild());
    }

    void preorderPrintForBinary()
    {
        preorderPrintHelper(root);
        cout << endl;
    }

    void postorderPrintHelper(TreeNodeB<T> *node)
    {
        if (node == nullptr)
            return;

        postorderPrintHelper(node->getLeftChild());
        postorderPrintHelper(node->getRightChild());
        cout << node->getData() << " ";
    }

    void postorderPrintForBinary()
    {
        postorderPrintHelper(root);
        cout << endl;
    }
};

//implemented by isfa
template <typename T>
class Array
{
    T *array;
    int size;
    int capacity;

public:
    Array(int cap) : size(0), capacity(cap)
    {
        array = new T[capacity];
    }
    ~Array()
    {
        delete[] array;
    }
    int getCapacity()
    {
        return capacity;
    }
    int getSize()
    {
        return size;
    }
    T *getarray()
    {
        return array;
    }
    void radixSortBySeverity()
    {
        if (size <= 1)
            return;

        const int MAX_SEVERITY = 5;

        Array<T> buckets[10] = {
            Array<T>(size), Array<T>(size), Array<T>(size), Array<T>(size), Array<T>(size),
            Array<T>(size), Array<T>(size), Array<T>(size), Array<T>(size), Array<T>(size)};

        // Put defects into buckets
        for (int i = 0; i < size; i++)
        {
            int sev = array[i].getSeverity(); // key
            buckets[sev].append(array[i]);
        }

        // Collect back
        int index = 0;
        for (int i = 1; i <= MAX_SEVERITY; i++)
        {
            for (int j = 0; j < buckets[i].getSize(); j++)
            {
                array[index++] = buckets[i].getarray()[j];
            }
        }
    }

    T* getDataAtIndex(int index){
        if(index < 0 || index >= size){
            cout << "\nInvalid Index!!" << endl;
            return nullptr;
        }
        else{
            return &array[index];
        }
    }
    void regrowSize()
    {

        int newcapacity = capacity * 2;
        T *newArray = new T[newcapacity]; // making new array with double cap
        for (int i = 0; i < size; i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newcapacity;
    }
    void append(T value)
    {
        if (size == capacity)
        {
            regrowSize();
        }
        array[size] = value;
        size++;
    }
    void prepend(T value)
    {
        if (size == capacity)
        {
            regrowSize();
        }

        for (int i = size; i > 0; i--)
        {
            array[i] = array[i - 1];
        }
        array[0] = value;
        size++;
        cout << value << " is prepended" << endl;
    }
    void insertAtIndex(T value, int index)
    {
        if (index < 0 || index > size)
        {
            cout << "invalid" << endl;
            return;
        }
        if (index == 0)
        {
            prepend(value);
            return;
        }
        if (index == size)
        {
            append(value);
            return;
        }
        if (size == capacity)
        {
            regrowSize();
        }
        for (int i = size; i > index; i--)
        {
            array[i] = array[i - 1];
        }

        array[index] = value;
        size++;
        cout << "inserted at index of array" << endl;
    }
    void removeAtIndex(int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "invalid" << endl;
            return;
        }
        else
        {
            for (int i = index; i < size - 1; i++)
            {
                array[i] = array[i + 1]; // moving elemnts
            }
        }
        size--; // decreasing size
        cout << "delete at index " << endl;
    }
    void remooveDuplicateInarray()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (array[i] == array[j])
                {
                    removeAtIndex(j); // calling remove index functiobn remove the duplicate
                    j--;
                }
            }
        }
        cout << "duplicates are removed  " << endl;
    }

    void reverse()
    {
        int startptr = 0;      // start ptr
        int endptr = size - 1; // endptr
        while (startptr < endptr)
        {
            swap(array[startptr], array[endptr]);
            startptr++; // moving form=ward
            endptr--;   // moving backward
        }
        cout << "array is reversed " << endl;
    }
    void bubbleSort()
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (array[j] > array[j + 1])
                { // conditoion for swap
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
        cout << "array is sorted by bubblesort" << endl;
    }
    void selectionSort()
    {
        for (int i = 0; i < size - 1; i++)
        {
            int minindex = i;
            for (int j = i + 1; j < size; j++)
            {
                if (array[j] < array[minindex])
                {
                    minindex = j; // update index
                }
            }

            if (minindex != i)
            { // after finding min ,swap the elements
                T temp = array[i];
                array[i] = array[minindex];
                array[minindex] = temp;
            }
        }
        cout << "array is sorted by selectionsort" << endl;
    }
    void insertionSort()
    {
        for (int i = 1; i < size; i++)
        {
            T key = array[i]; // key
            int j = i - 1;
            while (j >= 0 && array[j] > key)
            {
                array[j + 1] = array[j]; // replacing
                j--;
            }
            array[j + 1] = key; // update key
        }
        cout << "array is sorted by insertionsort" << endl;
    }
    void print()
    {
        cout << "Array is : " << endl;
        for (int i = 0; i < size; i++)
        {

            cout << array[i] << endl;
        }
    }
    void merge(int left, int mid, int right)
    {
        int leftarraysize = mid - left + 1; // size of left
        int rightarraysize = right - mid;   // right
        T *Lef = new T[leftarraysize];      // temprary array to store
        // temprarory arrray on right to store

        T *Rig = new T[rightarraysize];
        for (int i = 0; i < leftarraysize; i++)
            Lef[i] = array[left + i]; // copy elements of left side in L

        for (int j = 0; j < rightarraysize; j++)
            Rig[j] = array[mid + 1 + j]; // in r thr right side

        int i = 0, j = 0, k = left;
        while (i < leftarraysize && j < rightarraysize)
        { // while
            if (Lef[i] <= Rig[j])
            {                      // comparw element
                array[k] = Lef[i]; // store i element
                i++;
            }
            else
            {
                array[k] = Rig[j]; // j element
                j++;
            }
            k++;
        }

        while (i < leftarraysize)
        { // copy remaing elements of left side array
            array[k] = Lef[i];
            i++;
            k++;
        }
        while (j < rightarraysize)
        { // copy remains of array on r8
            array[k] = Rig[j];
            j++;
            k++;
        }

        delete[] Lef; // delete temp array
        delete[] Rig; // delete temp array
    }

    void mergeSortt(int left, int right)
    {
        if (left < right)
        {
            int mid = (left + right) / 2;

            mergeSortt(left, mid);      // recurse to break the array of left
            mergeSortt(mid + 1, right); // of right

            merge(left, mid, right); // merge the sorted part
        }
    }

    void mergeSort()
    {
        if (size > 1)
        {
            mergeSortt(0, size - 1); // call for the function actully doing
        }
        cout << "array is sorted by merge sort" << endl;
    }
    
    void countSortRadix(int divisor) {
    if (size <= 1) return;

    T* outputArray = new T[size];
    int count[10] = {0};

    // Count occurrences of each digit
    for (int i = 0; i < size; i++) {
        int digit = (array[i] / divisor) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++)//count
        count[i] += count[i - 1];
    // Build output array
    for (int i = size - 1; i >= 0; i--) {
        int digit = (array[i] / divisor) % 10;
        outputArray[count[digit] - 1] = array[i];
        count[digit]--;
    }

    // Copy back to original array
    for (int i = 0; i < size; i++)
        array[i] = outputArray[i];

    delete[] outputArray;
}
void radixSort() {
    if (size <= 1) return;

    // Check if all numbers are positive 
    for (int i = 0; i < size; i++) {
        if (array[i] < 0) {
            cout << "Radix sort supports only non-negative integers."<<endl;
            return;
        }
    }

    // Find maximum number
    T maxNumber = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > maxNumber)
            maxNumber = array[i];

    // Apply counting sort for each digit (1s, 10s, 100s…)
    for (int exp = 1; maxNumber / exp > 0; exp *= 10)
        countSortRadix(exp);

    cout << "Array is sorted by radix sort" << endl;
}
int findPivot(int start, int end) {
    int mid = (start + end) / 2;
    T a = array[start];
    T b = array[end];
    T m = array[mid];

    if ((m <= a && m >= b) || (m >= a && m <= b)) {
        return mid;
    } else if ((a <= m && a >= b) || (a >= m && a <= b)) {
        return start;
    } else {
        return end;
    }
}

int pivotPosition(int start, int end, T pivot) {
    int left = start;
    int right = end - 1;

    while (left <= right) {
        while (left <= right && array[left] < pivot)
            left++;
        while (left <= right && array[right] > pivot)
            right--;

        if (left <= right) {
            swap(array[left], array[right]);
            left++;
            right--;
        }
    }

    swap(array[left], array[end]);
    return left;
}

void insertionSortRange(int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        T key = array[i];
        int j = i - 1;
        while (j >= start && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void quickSortRecursion(int start, int end) {
    int subSize = end - start + 1;

    if (subSize <= 3) {
        insertionSortRange(start, end);
        return;
    }

    int pivotIndex = findPivot(start, end);
    T pivot = array[pivotIndex];

    swap(array[pivotIndex], array[end]); // move pivot to end
    int nextPivotPos = pivotPosition(start, end, pivot);

    quickSortRecursion(start, nextPivotPos - 1);
    quickSortRecursion(nextPivotPos + 1, end);
}

void quickSort() {
    if (size > 1){
        quickSortRecursion(0, size - 1);
     } cout << "Array is sorted by quick sort" << endl;
}
};
//MyArray Class
template <typename T>
class MyArray //2D dynamic Array
{
private:
    T **array;
    int *col_size;
    int row_count;

public:
    MyArray()
    {
        row_count = 3;
        this->array = new T *[row_count];

        this->col_size = new int[row_count];

        for (int i = 0; i < row_count; i++)
        {
            col_size[i] = 0;    // array have zero row and rows have 0 size
            array[i] = nullptr; // nothing in array of pointers
        }
    }

    ~MyArray()
    {

        for (int i = 0; i < row_count; i++)
        {
            delete[] array[i]; // array k har index pr jo row hai us k element deletre hongy
        }
        delete[] array;
        // array delete hogi

        delete[] col_size;
        // size delete hoga
    }
    T **getArray()
    {
        return array; // address print
    }
    int getColSize(int row_num)
    {
        if (row_num < 0 || row_num >= row_count)
        {
            cout << "invalid" << endl;
            return -1; // invalid
        }
        return col_size[row_num]; // colum k ronum pr value print krwaye ga
    }
    int getRowSize()
    {
        return row_count;
    }
    void addRow(int row_index)
    {
        // Validation
        if (row_index < 0 || row_index > row_count)
        {
            cout << "Invalid index" << endl;
            return;
        }

        //.     Allocate New Spines (New Arrays of Pointers and Sizes)
        // I create a new "backbone" that is 1 slot larger
        T **newArray = new T *[row_count + 1];
        int *newColSize = new int[row_count + 1];

        //.  Copy Initial Part (Before the insertion index)
        for (int i = 0; i < row_index; i++)
        {
            newArray[i] = array[i];        // Copy the POINTER to the row (not the data itself)
            newColSize[i] = col_size[i];   // Copy the size
        }

        //     Initialize the New Row (The Insertion)
        newArray[row_index] = nullptr;     // The new row is empty initially
        newColSize[row_index] = 0;         // Size is 0

        //Shift the Remaining Part (After the insertion index)
        // Note: I map old index 'i' to new index 'i + 1'
        for (int i = row_index; i < row_count; i++)
        {
            newArray[i + 1] = array[i];      // Shift the pointer
            newColSize[i + 1] = col_size[i]; // Shift the size
        }

        //.    Delete Old Spines
        // CRITICAL: I only delete 'array' (the array of pointers). 
        // I do NOT delete 'array[i]' because those rows are now pointed to by 'newArray'.
        delete[] array; 
        delete[] col_size;

        // 7. Update Class Members
        array = newArray;
        col_size = newColSize;
        row_count++; 
        
        cout << "Row added successfully at index " << row_index << endl;
    }
    void deleteRow(int row_index)
    {
        if (row_index < 0 || row_index >= row_count)
        { // check validity
            cout << "invalid" << endl;
            return;
        }
        delete[] array[row_index];               // dellete array or free memeory in it
        T **array2 = new T *[row_count - 1];     // dma
        int *col_size2 = new int[row_count - 1]; // dma
        for (int i = 0; i < row_index; i++)
        { // loop for copy
            array2[i] = array[i];
            col_size2[i] = col_size[i]; // column
        }

        for (int i = row_index + 1; i < row_count; i++)
        {                             // after index loop starts
            array2[i - 1] = array[i]; // for shifting
            col_size2[i - 1] = col_size[i];
        }

        delete[] array; //
        delete[] col_size;
        array = array2; // update
        col_size = col_size2;
        row_count--; // size decrease
    }
    void append(T value, int row_num)
    {
        if (row_num < 0 || row_num >= row_count)
        { // check validity
            cout << "invalid";
            return;
        }
        // T**array2=new T*[row_count+1];//no need of 2d just append in a row
        int size = col_size[row_num];
        T *row_withthenewsize = new T[size + 1]; // increase size with dma array
        for (int i = 0; i < size; i++)
        { // loop copy
            row_withthenewsize[i] = array[row_num][i];
        }
        row_withthenewsize[size] = value; // append value

        delete[] array[row_num];
        array[row_num] = row_withthenewsize;
        col_size[row_num] = size + 1; // increase size of col
    }
    void prepend(T value, int row_num)
    {
        if (row_num < 0 || row_num >= row_count)
        {
            cout << "invalid"; // validity check
            return;
        }
        // T**array2=new T*[row_count+1];//no need of 2d just append in a row
        int size = col_size[row_num];            // row num provided
        T *row_withthenewsize = new T[size + 1]; // dma increasing size
        for (int i = 0; i < size; i++)
        {
            row_withthenewsize[i + 1] = array[row_num][i]; // copy and shifting
        }
        row_withthenewsize[0] = value; // at 0 index place the value

        delete[] array[row_num]; // delete aray
        array[row_num] = row_withthenewsize;
        col_size[row_num] = size + 1; // size update
    }
    void delete_from_last(int row_num)
    {

        if (row_num < 0 || row_num >= row_count)
        {
            cout << "invalid" << endl; // check validity
            return;
        }
        int size = col_size[row_num];
        if (size == 0)
        {
            cout << "Row is already empty, cannot delete." << endl;
            return;
        }
        T *newarraywithsize = new T[size - 1]; // uisng dma to make new array with 1 less size
        for (int i = 0; i < size - 1; i++)
        {
            newarraywithsize[i] = array[row_num][i]; // copy
        }

        delete[] array[row_num];
        array[row_num] = newarraywithsize;
        col_size[row_num] = size - 1; // decresing size
    }
    void delete_from_start(int row_num)
    {

        if (row_num < 0 || row_num >= row_count)
        { // validity
            cout << "invalid" << endl;
            return;
        }
        int size = col_size[row_num]; // int size for col
        if (size == 0)
        {
            cout << "Row is already empty, cannot delete." << endl;
            return;
        }
        T *newarraywithsize = new T[size - 1]; // decreasing
        for (int i = 1; i < size; i++)
        {
            newarraywithsize[i - 1] = array[row_num][i]; // copy and shiftimg towards start
        }

        delete[] array[row_num];
        array[row_num] = newarraywithsize; // update
        col_size[row_num] = size - 1;      // decrea
    }
    void display()
    {
        for (int i = 0; i < row_count; i++)
        {
            cout << "row  " << i << ": ";
            if (col_size[i] == 0 || array[i] == nullptr)
            {
                cout << "(empty)"; // if row have no col print empty
            }
            else
            {
                for (int j = 0; j < col_size[i]; j++)
                {
                    cout << array[i][j] << " "; // if there are col then print every element of row
                }
            }
            cout << endl;
        }
    }
};

//implemented by bilal
template <typename T>
class Node
{
    T data;
    Node<T> *next;

public:
    // Constructor
    Node()
    {
        data = T();
        next = nullptr;
    }
    // Destructor
    ~Node()
    {
        next = nullptr;
    }

    void setNext(Node<T> *val)
    {
        next = val;
    }
    Node<T> *getNext()
    {
        return next;
    }
    void setData(T data)
    {
        this->data = data;
    }
    // This allows the Billing System in hotel or any other to modify the rEAL object, not just a copy
    T& getDataRef() //returning by reference
    {
        return data;
    }
    T getData()
    {
        return data;
    }
};

//implemented by bilal
template <typename T>
class List
{
    Node<T> *head;
    Node<T> *tail;
    int count;

public:
    List()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Destructor
    ~List()
    {
        if (count == 0)
        {
            head = tail = nullptr;
        }
        else
        {
            while (head != nullptr)
            {
                Node<T> *temp = head;
                head = head->getNext();
                delete temp;
                count--;
            }
            head = tail = nullptr;
            count = 0;
        }
    }

    Node<T> *getHead() { return head; }
    Node<T> *getTail() { return tail; }

    bool isEmpty()
    {
        if (count == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int getCount() { return count; }

    void push_back(T data)
    {
        Node<T> *node_billu = new Node<T>;
        node_billu->setData(data);
        node_billu->setNext(nullptr);

        if (count == 0)
        {
            head = node_billu;
            tail = node_billu;
            count++;
        }
        else
        {
            tail->setNext(node_billu);
            tail = tail->getNext();
            tail->setNext(nullptr);
            count++;
        }
    }

    void push_front(T data)
    {
        Node<T> *node_billu = new Node<T>;
        node_billu->setData(data);
        node_billu->setNext(nullptr);

        if (count == 0)
        {
            head = node_billu;
            tail = node_billu;
            count++;
        }
        else
        {
            Node<T> *temp_billu = head;
            node_billu->setNext(temp_billu);
            head = node_billu;
            count++;
        }
    }

    void pop_back()
    {
        if (count == 0)
        {
            cout << "Cannot delete from end" << endl;
            return;
        }
        else if (count == 1)
        {
            Node<T> *deleteNode = head;
            delete deleteNode;
            head = tail = nullptr;
            count--;
        }
        else
        {
            Node<T> *previousTail = head;
            while (previousTail->getNext() != tail)
            {
                previousTail = previousTail->getNext();
            }

            Node<T> *deleteNode = tail;
            tail = previousTail;
            tail->setNext(nullptr);
            delete deleteNode;
            count--;
        }
    }

    void pop_front()
    {
        if (count > 1)
        {
            Node<T> *temp_head = head;
            head = head->getNext();
            delete temp_head;
            count--;
        }
        else if (count == 1)
        {
            Node<T> *temp_delete = head;
            delete temp_delete;
            head = nullptr;
            tail = nullptr;
            count--;
        }
        else
        {
            return;
        }
    }

    void printList()
    {
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            cout << "Data:" << temp->getData() << endl;
            temp = temp->getNext();
        }
    }

    void insertAtIndex(int index, T data)
    {
        Node<T> *insertNode = new Node<T>;
        insertNode->setData(data);
        insertNode->setNext(nullptr);

        if (index < 0 || index > count)
        {
            cout << "Invalid index " << endl;
            delete insertNode;
            return;
        }
        else if (index == 0)
        {
            if (count == 0)
            {
                head = insertNode;
                tail = insertNode;
            }
            else
            {
                Node<T> *previousHead = head;
                head = insertNode;
                head->setNext(previousHead);
            }
            count++;
        }
        else if (index == count)
        {
            tail->setNext(insertNode);
            tail = insertNode;
            tail->setNext(nullptr);
            count++;
        }
        else
        {
            Node<T> *beforeNode = head;
            for (int i = 0; i < index - 1; i++)
                beforeNode = beforeNode->getNext();

            Node<T> *afterNode = beforeNode->getNext();
            beforeNode->setNext(insertNode);
            insertNode->setNext(afterNode);
            count++;
        }
    }

    void deleteFromIndex(int index)
    {
        if (index < 0 || index >= count)
        {
            cout << "Invalid index" << endl;
            return;
        }
        else if (index == 0)
        {
            pop_front();
            return;
        }
        else if (index == count - 1)
        {
            pop_back();
            return;
        }
        else
        {
            Node<T> *beforeNode = head;
            for (int i = 0; i < index - 1; i++)
                beforeNode = beforeNode->getNext();

            Node<T> *deleteNode = beforeNode->getNext();
            Node<T> *afterNode = deleteNode->getNext();
            beforeNode->setNext(afterNode);
            delete deleteNode;
            count--;
        }
    }

    bool search(T value)
    {
        if (count == 0)
            return false;

        Node<T> *temp = head;
        while (temp != nullptr)
        {
            if (temp->getData() == value)
                return true;

            temp = temp->getNext();
        }
        return false;
    }

    void updateAtIndex(int index, T newValue)
    {
        if (index < 0 || index >= count)
        {
            cout << "Invalid index" << endl;
            return;
        }

        Node<T> *temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->getNext();

        temp->setData(newValue);
    }

    int countOccurrences(T value)
    {
        int c = 0;
        Node<T> *temp = head;

        while (temp != nullptr)
        {
            if (temp->getData() == value)
                c++;

            temp = temp->getNext();
        }
        return c;
    }

    void reverse()
    {
        Node<T> *newTail = head;
        Node<T> *prev = nullptr;
        Node<T> *current = head;
        Node<T> *next = nullptr;

        while (current != nullptr)
        {
            next = current->getNext();
            current->setNext(prev);
            prev = current;
            current = next;
        }

        head = prev;
        tail = newTail;
        tail->setNext(nullptr);
    }

    T getIndexData(int index)
    {
        if (count == 0)
        {
            cout << "The list is empty." << endl;
            return T();
        }

        Node<T> *temp = head;
        for (int i = 0; i < count; i++)
        {
            if (index == i)
                return temp->getData();

            temp = temp->getNext();
        }

        return T();
    }

    Node<T> *getIndex(int index)
    {
        if (count == 0)
        {
            cout << "The list is empty." << endl;
            return nullptr;
        }

        Node<T> *temp = head;
        for (int i = 0; i < count; i++)
        {
            if (index == i)
                return temp;

            temp = temp->getNext();
        }

        return nullptr;
    }

    void swapFunction(Node<T> *a, Node<T> *b)
    {
        //Sanity Checks
        if (a == b || head == nullptr || a == nullptr || b == nullptr) return;

        // Find Predecessors (prevA and prevB)
        Node<T> *prevA = nullptr, *currA = head;
        while (currA != nullptr && currA != a) {
            prevA = currA;
            currA = currA->getNext();
        }

        Node<T> *prevB = nullptr, *currB = head;
        while (currB != nullptr && currB != b) {
            prevB = currB;
            currB = currB->getNext();
        }

        // If either node is not found in the list, stop.
        if (currA == nullptr || currB == nullptr) return;

        // Update Predecessors' pointers
        //If prevA is null, 'a' was head, so 'b' becomes new head
        if (prevA != nullptr) prevA->setNext(b);
        else head = b;

        // If prevB is null, 'b' was head, so 'a' becomes new head
        if (prevB != nullptr) prevB->setNext(a);
        else head = a;

        //Swap the 'next' pointers of the nodes themselves
        Node<T> *temp = a->getNext();
        a->setNext(b->getNext());
        b->setNext(temp);
        
        // Update Tail (only  if necessary)
        if (tail == a) tail = b;
        else if (tail == b) tail = a;
    }




};


//Stack Class Implemented by Hamza
template <typename T>
class Stack {
    Node<T>* top;
public:
    Stack() : top(nullptr) {}
    
    ~Stack() {
        while(!isEmpty()) pop();
    }

    void push(T val) {
        Node<T>* newNode = new Node<T>(); // Using my existing Node class
        newNode->setData(val);
        newNode->setNext(top);
        top = newNode;
    }
    int size()
    {
        int count = 0;
        Node<T> *temp = top;

        while (temp != nullptr)
        {
            count++;
            temp = temp->getNext();
        }

        return count;
    }
    T pop() {
        if(isEmpty()) return T(); // Return empty if null
        Node<T>* temp = top;
        T val = temp->getData();
        top = top->getNext();
        delete temp;
        return val;
    }

    bool isEmpty() { return top == nullptr; }
    
    T peek() {
        if(isEmpty()) return T();
        return top->getData();
    }
};

//============= UNDIRECTED WEIGHTED GRAPH =============
template <typename T>
class Graph
{
    int V;
    T** adjacency_matrix;

public:
    Graph(int  initial_number_of_vertices)
    {
        V=initial_number_of_vertices;
        adjacency_matrix= new T*[V];
        for(int i=0; i<V;i++)
        {
            adjacency_matrix[i]=new T[V];
        }

        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                adjacency_matrix[i][j]=0;
            }
        }
    }

    ~Graph()
    {
        for(int i=0; i<V; i++)
        {
            delete [] adjacency_matrix[i];
        }
        delete [] adjacency_matrix;
    }

    bool isValidVertex(int vertex_index) const
    {
        if(vertex_index<0 || vertex_index>=V)
        {
            return false;
        }
        return true;
    }
    void addEdge(int source, int dest, T distance)
    {
        if(isValidVertex(source) && isValidVertex(dest))
        {
            adjacency_matrix[source][dest]=distance;
            adjacency_matrix[dest][source]=distance;
        }

    }

    void deleteEdge(int source, int dest)
    {
        if(!isValidVertex(source) || !isValidVertex(dest))
        {
            return;
        }
        adjacency_matrix[source][dest]=0;
        adjacency_matrix[dest][source]=0;
    }

    void updateEdge(int old_source, int old_destination, int new_source, int new_destination, T d)
    {
        if(!isValidVertex(old_source) || !isValidVertex(old_destination) ||
                 !isValidVertex(new_source) || !isValidVertex(new_destination) )
        {
            return;
        }

        deleteEdge(old_source,old_destination);
        addEdge(new_source,new_destination,d);
    }
    bool checkEdgeStatus(int source, int dest)
    {
        if(isValidVertex(source) && isValidVertex(dest))
        {
            if(adjacency_matrix[source][dest]>0 && adjacency_matrix[dest][source]>0 &&
                adjacency_matrix[source][dest]==adjacency_matrix[dest][source])
            {
                return true;
            }
        }
        return false;
    }

    int getDegree(int vertex_index)
    {
        int count=0;
        if(isValidVertex(vertex_index))
        {
            for(int i=0; i<V;i++)
            {
                if(adjacency_matrix[vertex_index][i]>0)
                {
                    count++;
                }
            }
        }
        return count;
    }

    T getEdgeWeight(int source, int dest)
    {
        T weight=0;
        if(isValidVertex(source) && isValidVertex(dest))
        {
            weight=adjacency_matrix[source][dest];
        }
        return weight;
    }

    int getVerticesCount() const
    {
        return V;
    }

    int getEdgesCount()
    {
        int count=0;
        for(int i=0; i<V; i++)
        {
            for(int j=i+1; j<V; j++)
            {
                if(adjacency_matrix[i][j]>0 )
                {
                    count++;
                }

            }
        }
        return count;
    }


    void displayGraph( )
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                cout<<""<<adjacency_matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void BFS(int start_vertex)
    {
        if(isValidVertex(start_vertex))
        {
            bool visit[V];
            for(int i=0; i<V; i++)
            {
                visit[i]=false;
            }
            LinkedQueue<int>q;
            q.enqueue(start_vertex);
            visit[start_vertex]=true;
            while (!q.isEmpty())
            {
                int u=q.dequeue();
                cout<<u<<" ";
                for(int i=0; i<V; i++)
                {
                    if( adjacency_matrix[u][i]>0 && visit[i]==false)
                    {
                        q.enqueue(i);
                        visit[i]=true;
                    }
                }
            }
        }else
        {
            cout<<"invalid vertex"<<endl;
        }
    }

    void DFSHelper(int start_vertex, bool visit[])
    {
        int u=start_vertex;
        visit[start_vertex]=true;
        cout<<" "<<u;
        for(int i=0; i<V; i++)
        {
            if(adjacency_matrix[u][i]>0 && visit[i]==false)
            {
                DFSHelper(i,visit);
            }
        }
    }

    void DFS(int start_vertex)
    {
        if (!isValidVertex(start_vertex))
        {
            cout << "Invalid start vertex\n";
            return;
        }

        bool visit[V];
        for(int i=0; i<V; i++)
        {
            visit[i]=false;
        }

        DFSHelper(start_vertex,visit);
    }
};

template <typename T>
struct Edge {
    T destination;
    double weight;
    
    Edge(){

    }
    Edge(T dest, double w){
        destination = dest;
        weight = w;
    }
};

template <typename T>
class GraphNode {
private:
    T data;
    List<Edge<T>> adjacencyList;  // List of edges (neighbors)
    
public:
    GraphNode(){

    }
    GraphNode(T value){
        data = value;
    }
    
    T getData() {
        return data;
    }
    void setData(T value){
        data = value;
    }
    
    void addEdge(T destination, double weight){
        Edge<T> e(destination, weight);
        adjacencyList.push_back(e);
    }
    List<Edge<T>>& getAdjacencyList(){
        return adjacencyList;
}
    
    void displayEdges() {
        Node<Edge<T>>* h = adjacencyList.getHead();
    if (h == nullptr) {
        cout << "no connections!!!";
        return;
    }
    
    while (h != nullptr) {
        Edge<T> edge = h->getData();
        cout << "Destination: " << edge.destination << " (" << edge.weight << " km)";
        h = h->getNext();
    }
    }
    int getDegree(){
        int degree = 0;
        Node<Edge<T>>* j = adjacencyList.getHead();
        while (j != nullptr) {
        degree++;
        j = j->getNext();
        }
        return degree;
    }
};

template <typename T>
class GraphF {
private:
    List<GraphNode<T>*> vertices;
    int vertexCount;
    bool isDirected;
    
public:
    // Constructor
    GraphF(bool directed = false) {
        vertexCount = 0;
        isDirected = directed;
    }
    
    // Destructor
    ~GraphF() {
        Node<GraphNode<T>*>* h = vertices.getHead();
        while (h != nullptr) {
            delete h->getData();
            h = h->getNext();
        }
    }

    GraphNode<T>* findVertex(T data) {
        Node<GraphNode<T>*>* h = vertices.getHead();
        while (h != nullptr) {
            if (h->getData()->getData() == data) {
                return h->getData();
            }
            h = h->getNext();
        }
        return nullptr;
    }
    
    // Checks if vertex exists
    bool vertexExists(T data) {
        GraphNode<T> *h = findVertex(data);
        if(h != nullptr){
            return true;
        }
        return false;
    }
    

    bool addVertex(T data) {
        // Check if already exists
        if (vertexExists(data) == true) {
            cout << "City '" << data << "' already exists!" << endl;
            return false;
        }
        
        GraphNode<T>* newV = new GraphNode<T>(data);
        vertices.push_back(newV);
        vertexCount++;
        cout << "City '" << data << "' added successfully!" << endl;
        return true;
    }
    
    // Add highway/edge between two cities
    void addEdge(T source, T destination, double weight) {
        GraphNode<T>* srcNode = findVertex(source);
        GraphNode<T>* destNode = findVertex(destination);
        
        if (srcNode == nullptr || destNode == nullptr) {
            cout << "Error: One or both cities not found!" << endl;
            return;
        }
        
        // Add edge from source to destination
        srcNode->addEdge(destination, weight);
        
        // If undirected (two-way highway), add reverse edge
        if (!isDirected) {
            destNode->addEdge(source, weight);
        }
        
        cout << "Highway added: " << source << " to " << destination 
             << " with weight: " << weight << " km" << endl;
    }
    
    
    // Get vertex index (for Dijkstra later)
    int getVertexIndex(T data) {
        Node<GraphNode<T>*>* k = vertices.getHead();
        int index = 0;
        while (k != nullptr) {
            if (k->getData()->getData() == data) {
                return index;
            }
            k = k->getNext();
            index++;
        }
        return -1;
    }
    
    // Display the entire graph
    void displayGraph(){
        if(isDirected){
            cout << "\nDirected Graph" << endl;
        }
        else{
            cout << "\nUndirected Graph" << endl;
        }
        cout << "\nTotal Cities: " << vertexCount << endl;
        cout << "\nCity Connections:" << endl;
        
        Node<GraphNode<T>*>* t = vertices.getHead();
        while (t != nullptr) {
            GraphNode<T>* vertex = t->getData();
            cout << vertex->getData();
            vertex->displayEdges();
            cout << endl;
            t = t->getNext();
        }
    }
    
    // Display specific city connections
    void displayVertex(T data) {
        GraphNode<T>* vertex = findVertex(data);
        if (vertex == nullptr) {
            cout << "City '" << data << "' not found!" << endl;
            return;
        }
        
        cout << "\n City: " << vertex->getData() << endl;
        cout << "Number of connections: " << vertex->getDegree() << endl;
        cout << "Connected to Edges:";
        vertex->displayEdges();
        cout << endl;
    }
    
    // Getters
    int getVertexCount() const {
        return vertexCount;
    }
    
    bool isGraphDirected() const {
        return isDirected;
    }
    
    struct DijkstraResult {
        double distance;
        List<T> path;
        bool pathFound;
        
        DijkstraResult() {
            distance = -1;
            pathFound = false;
        }
    };
    
    int findMinDistanceVertex(double distances[], bool visited[], int size) {
        return -1;
    }
    
    // Helper to reconstruct path
    void reconstructPath(int parent[], int vertex, List<T>& path) {
        // Implementation will go here
    }
    
    // Dijkstra's Algorithm
    DijkstraResult dijkstra(T source, T destination) {
        DijkstraResult result;
        // Implementation will go here
        return result;
    }
};

template <typename T>
class Queue
{
private:
    Node<T> *front;
    Node<T> *rear;
    int count;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    void enqueue(T data)
    {
        Node<T> *newNode = new Node<T>();
        newNode->setData(data);
        newNode->setNext(nullptr);

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->setNext(newNode);
            rear = newNode;
        }
        count++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return T();
        }

        Node<T> *temp = front;
        T data = temp->getData();
        front = front->getNext();

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
        count--;
        return data;
    }

    T getFront()
    {
        if (isEmpty())
        {
            return T();
        }
        return front->getData();
    }

    bool isEmpty()
    {
        return (count == 0);
    }

    int size()
    {
        return count;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node<T> *temp = front;
        cout << "Queue: ";

        while (temp != nullptr)
        {
            cout << temp->getData() << " ";
            temp = temp->getNext();
        }
        cout << endl;
    }
};

#endif