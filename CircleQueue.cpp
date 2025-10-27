#include <iostream>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <thread>

template<typename T, size_t size>
class CircleQueue{
public:
    CircleQueue():tail_(0), head_(0), num_(0), buffer(size), stop(false){
        //buffer = new std::vector<T>(size);
    };
    bool push(const T& value){
        std::unique_lock<std::mutex> lock(m_);
        notfull.wait(lock, [this](){return !full()||stop;});
        std::cout << "push " <<*value << std::endl;
        buffer[tail_] = value;
        tail_ = (tail_ + 1) % size;
        num_++;
        lock.unlock();
        notEmpty.notify_one();

        return true;
    }
    bool pop(){
        std::unique_lock<std::mutex> lock(m_);
        notEmpty.wait(lock, [this](){return !empty()||stop;});
        std::cout << "pop " << *buffer[head_] << std::endl;
        head_ = (head_ + 1) % size;
        num_ --;
        lock.unlock();
        notfull.notify_one();

        return true;
    }

    bool full(){
        //push和pop函数本身已经获取互斥锁，这里再加锁会导致死锁。
        //std::lock_guard<std::mutex> lock(m_);
        return is_full();
    }
    bool empty(){
        //std::lock_guard<std::mutex> lock(m_);
        return is_empty();
    }
private:
    bool is_full() const {
        return num_ == size;
    }

    // 内部辅助函数：判空（依赖外部已加锁）
    bool is_empty() const {
        return num_ == 0;
    }
    size_t tail_;
    size_t head_;
    //size_t size_;
    size_t num_;
    std::mutex m_;
    std::condition_variable notEmpty;
    std::condition_variable notfull;
    std::vector<T> buffer;
    bool stop;
};

int main(){
    CircleQueue<std::shared_ptr<int>, 5> queue;
    std::thread t1([&](){
        for(int i = 0; i < 10; i++){
            std::shared_ptr<int> p = std::make_shared<int>(i);
            queue.push(p);
        }
    }
    );

    std::thread t2([&](){
        while(true){
            queue.pop();
        }
    });

    t1.join();
    t2.join();
}