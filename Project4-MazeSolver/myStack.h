template<class T>  //must put this before every class

struct Node {
    T data;
    Node(T newData) { // node constructor
        data = newData;
        next = nullptr;
    }
    struct Node* next;
};

template<class T>

class MyStack {

private:

    Node<T>* head; // create the head node
    int length; // int to store the length of the stack

public:
    MyStack() : head(nullptr), length(0) {}

    // add function
    void push(T val) {
        Node<T>* n_node = new Node<T>(val); // create a new node with the value provided
        n_node->next = head; // make the node after the new one the head
        head = n_node;
        length++; // increment the length
    }

    // delete function
    void pop() {
        if (empty()) return; // if there's nothing in the stack to delete, return
        Node<T>* temp = head; // set temp = head
        head = temp->next == nullptr ? nullptr : temp->next;
        length--; // decrement the length
    }

    bool empty() { return length == 0; } // if empty function
    int size() { return length; } // function to return size of the stack
    T top() { return head->data; } // return the top of the stack by using the data in the head node

};

