#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

// Doubly Linked List
class Node {
public:
    unordered_set<string> keys;
    int count;
    Node* next;
    Node* prev;

    Node() {
        next = prev = NULL;
        count = 0;
    }
};

const string empty_key = "";

class AllOne {
public:

    Node* head = new Node();
    Node* tail = head;
    unordered_map<string, Node*> umap;

    AllOne() {

    }

    // Increments the count of the string key by 1. 
    // If key does not exist in the data structure, insert it with count 1.
    void inc(string key) {
        // Doesnt exist in the data structure.  
        if (!umap.count(key)) {
            if (head->next && (head->next->count == 1)) {
                head->next->keys.insert(key);
            }
            else {
                Node* currHead = head->next;
                Node* newHead = new Node();
                newHead->count = 1;
                newHead->keys.insert(key);
                newHead->prev = head;
                newHead->next = currHead;
                head->next = newHead;
                if (currHead) {
                    currHead->prev = newHead;
                }
                else {
                    tail = newHead;
                }
            }
            umap[key] = head->next;
        }
        // Exist in the data structure.
        else {
            Node* tempNode = umap[key];
            if (tempNode->next && (tempNode->next->count == tempNode->count + 1)) {
                umap[key] = tempNode->next;
                tempNode->next->keys.insert(key);
            }
            else {
                Node* newNode = new Node();
                newNode->count = tempNode->count + 1;
                newNode->keys.insert(key);
                umap[key] = newNode;
                newNode->next = tempNode->next;
                newNode->prev = tempNode;
                tempNode->next = newNode;

                if (newNode->next) {
                    newNode->next->prev = newNode;
                }
                else {
                    tail = newNode;
                }
            }
            RemoveTempNode(tempNode, key);
        }
    }

    // Decrements the count of the string key by 1. If the count of key is 0 after the decrement,
    // remove it from the data structure.
    // It is guaranteed that key exists in the data structure before the decrement.
    void dec(string key) {
        Node* tempNode = umap[key];

        // Count of key is NOT 0 after the decrement.
        if (tempNode->count - 1 != 0) {
            if (tempNode->prev->count == tempNode->count - 1) {
                tempNode->prev->keys.insert(key);
                umap[key] = tempNode->prev;
            }
            else {
                Node* newNode = new Node();
                newNode->count = tempNode->count - 1;
                newNode->keys.insert(key);
                umap[key] = newNode;
                newNode->next = tempNode;
                tempNode->prev->next = newNode;
                newNode->prev = tempNode->prev;
                tempNode->prev = newNode;
            }
        }
        // Count of key is 0 after the decrement.
        else {
            // Remove from the data structure.
            umap.erase(key);
        }
        RemoveTempNode(tempNode, key);
    }

    //  Returns one of the keys with the maximal count. If no element exists, return an empty string "".
    string getMaxKey() {
        return tail == head ? empty_key : *tail->keys.begin();
    }

    // Returns one of the keys with the minimum count. If no element exists, return an empty string "".
    string getMinKey() {
        return tail == head ? empty_key : *head->next->keys.begin();
    }

    // Helper Method
    void RemoveTempNode(Node* tempNode, string key)
    {
        tempNode->keys.erase(key);
        if (tempNode->keys.size() == 0) {
            tempNode->prev->next = tempNode->next;
            if (tempNode->next) {
                tempNode->next->prev = tempNode->prev;
            }
            else {
                tail = tail->prev;
            }
            tempNode->next = tempNode->prev = NULL;
        }
    }
};
