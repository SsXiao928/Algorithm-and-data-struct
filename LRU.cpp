#include <iostream>
#include <unordered_map>

struct DLinkedNode{
    DLinkedNode* prev_;
    DLinkedNode* next_;
    int key_;
    int value_;
    DLinkedNode():prev_(nullptr), next_(nullptr), key_(0), value_(0){}
    DLinkedNode(int key, int value):prev_(nullptr), next_(nullptr), key_(key), value_(value){}
};

class LRUCache{
    std::unordered_map<int, DLinkedNode*> cache;
    int size_;
    int cap_;
    DLinkedNode* head_;
    DLinkedNode* tail_;
public:
    LRUCache(int capcaity)
    {
        size_ = 0;
        cap_ = capcaity;
        head_ = new DLinkedNode();
        tail_ = new DLinkedNode();
        head_->next_ = tail_;
        tail_->prev_ = head_;
    }

    int get(int key) {
        if(!cache.count(key)){
            return -1;
        }

        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value_;
    }
    
    void put(int key, int value) {
        if(!cache.count(key)){
            DLinkedNode* node = new DLinkedNode(key, value);
            
            addToHead(node);
            size_++;
            cache[key] = node;
            if(size_ > cap_){
                DLinkedNode* rnode = removeTail();
                cache.erase(rnode->key_);
                delete rnode;
                size_--;
            }

        }
        else{
            DLinkedNode* node = cache[key];
            node->value_ = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node){
        node->next_ = head_->next_;
        head_->next_->prev_ = node;
        node->prev_ = head_;
        head_->next_ = node;

    }

    void moveToHead(DLinkedNode* node){
        removeNode(node);
        addToHead(node);
    }

    void removeNode(DLinkedNode* node){
        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;
    }

    DLinkedNode* removeTail(){
        DLinkedNode* node = tail_->prev_;
        removeNode(node);
        return node;
    }
};