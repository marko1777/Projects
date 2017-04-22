#ifndef Queue_H
#define Queue_H

#include <iosfwd>

namespace MyQueue
{
    class Queue{
    public:
        struct List
        {
            int value;
            List *next;
            List(int v = 0,List *p = NULL): value(v),next(p) {}
        };

        enum Exceptions{EMPTY_LIST};

        Queue()
        {
            size = 0; 
            elements = new List();
            begin = elements;
        }

        Queue(int value)
        {
            elements = new List(); //head
            begin = elements;
            elements = elements -> next = new List(value);
            size = 1;
        }

        Queue(const Queue &o)
        {
            size = o.size;
            List *lhsP = begin;
            List *rhsP = o.begin -> next;
            while(rhsP != NULL)
            {
                lhsP -> next = new List(rhsP -> value);
                lhsP = lhsP -> next;
                rhsP = rhsP -> next;
            }
            elements = rhsP;
        }

        ~Queue()
        {
            if(!isEmpty())
            {
                List *tempPointer = begin;
                while(tempPointer != NULL)
                {
                    tempPointer = begin;
                    begin = begin -> next;
                    delete tempPointer;
                }
            }
        }

        int pop()
        {
            if(isEmpty()) throw EMPTY_LIST;
            List *tempPointer = begin -> next;
            int returnValue = tempPointer -> value; 
            begin ->next = tempPointer -> next;
            delete tempPointer;
            size--;

            return returnValue;
        }

        void push(int pushValue)
        {
            if(isEmpty())
            {
                ++size;
                elements = new List(pushValue);
                begin ->next = elements;
            }else{
                ++size;
                elements -> next = new List(pushValue);
                elements = elements-> next;
            }
        }

        bool isEmpty(){ return size == 0; }

        int getSize(){ return size; }    
        
    private:
        List *elements;
        List *begin;
        int size;
    };
}
#endif // Queue_H
