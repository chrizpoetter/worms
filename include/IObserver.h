/* Interface for Observer
   See Observer Design Pattern */

#ifndef IOBSERVER_H
#define IOBSERVER_H

class IObserver {
    public:
        virtual ~IObserver(){}; 
        virtual void update() = 0;
};

#endif // IOBSERVER_H