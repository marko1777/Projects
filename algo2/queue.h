#ifndef Queue_H
#define Queue_H

namespace MyQueue
{	
	typedef unsigned size_t;
    class Queue{
    public:
        struct List
        {
            int value;
            List *next;
            List(int v = 0,List *p = nullptr): value(v),next(p) {}
        };

        enum Exceptions{EMPTY_LIST};

        Queue() : end(new List()), begin(end), size(0){}

        Queue(int value) : end(new List(value)), begin(new List(0, end)), size(1){}

        Queue(const Queue &o)
        {
            size = o.size;
            List *lhsP = begin;
            List *rhsP = o.begin -> next;
            while(rhsP != nullptr)
            {
                lhsP -> next = new List(rhsP -> value);
                lhsP = lhsP -> next;
                rhsP = rhsP -> next;
            }
            end = rhsP;
        }

        ~Queue()
        {
            if(isEmpty()) return;
            List *tempPointer = begin;
            while(tempPointer != nullptr)
            {
                tempPointer = begin;
                begin = begin -> next;
                delete tempPointer;
            }
        }

        int pop()
        {
            if(isEmpty()) throw EMPTY_LIST;
            List *tempPointer = begin -> next;
            begin -> next = tempPointer -> next;
            int returnValue = tempPointer -> value; 
            delete tempPointer;
            size--;

            return returnValue;
        }

        void push(int pushValue)
        {
            if(isEmpty())
            {
                ++size;
                begin ->next = end = new List(pushValue);
            }else{
                ++size;
                end = end-> next = new List(pushValue);
            }
        }

        bool isEmpty() const { return size == 0; }

        size_t getsize() const { return size; }
        
    private:
        List *end;
        List *begin;
        size_t size;
    };
}
#endif // Queue_H
