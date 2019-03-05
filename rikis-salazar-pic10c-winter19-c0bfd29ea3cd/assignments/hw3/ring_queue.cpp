// Description:
//     An incomplete implementation of iterators for a RingQueue class.
//
// Notes:
//     The project DOES compile but there is no meaningful output
//
// Your job:
//     To complete this set of classes so that the output produced by 'main'
//     (below), matches the sample file provided at the end of this file.


#include <iostream>

// Forward declaration
template <typename ItemType, int MAX_SIZE>
class RingQueue;



template <typename ItemType, int MAX_SIZE>
class RingQueue{
  public:
    // Nested Forward declaration of RingQueue<ItemType,MAX_SIZE>::iterator.
    // This is needed if one plans to turn this home-made iterator into one of
    // the special categories of iterators (e.g., input, output, forward, etc.).
    class iterator;



    // Aliases.
    typedef ItemType* pointer;
    typedef ItemType& reference;



  public:
    // Definition of RingQueue<ItemType,MAX_SIZE>::iterator
    class iterator{
      private:
        // A link to the parent container
        RingQueue* parent;

        // The position within the RingQueue is determined by how far ahead we
        // are from the begining of the queue.
        int offset;

      private:  // Private constructor???
        iterator(RingQueue* _parent, int _offset = 0 )
          : parent(_parent), offset(_offset) { }


        // It is quite common for Containers and their iterators to be friends.
        // After all, they should work closely together.
        friend class RingQueue<ItemType,MAX_SIZE>;


      public:
        reference operator*() {
            // Replace the line(s) below with your code.
            return parent->buffer[(parent->begin_index + offset) % MAX_SIZE] ;
        }

        iterator& operator++(){
            // Replace the line(s) below with your code.
			++offset; //increment the offset to increment the iterator
            return *this; //as this is the prefix increment operator, we should return the modified iterator
        }

        iterator operator++( int unused ){
            // Replace the line(s) below with your code.
			iterator copy(parent, offset); //make a copy of the iterator in its unmodified state
			++(*this); //increment the iterator
            return copy; //return the unmodified copy
        }

        bool operator==( const iterator& rhs ) const {
            // Replace the line(s) below with your code.
            return (parent == rhs->parent) && (offset == rhs->offset); //the iterators are equal if they have the same parent and offset
        }

        bool operator!=( const iterator& rhs ) const {
            // Replace the line(s) below with your code.
            return !(*this == rhs); //check if the iterators are not equal
        }

    }; // end of iterator class



    /**
    class const_iterator{
      private:
        RingQueue* parent;
        int offset;

      private:
        // Only RingQueue objects can create const_iterators...
        const_iterator();

      public:
        // ... however, const_iterators can be 'copied'.
        const_iterator( const const_iterator& );

        friend class RingQueue<ItemType,MAX_SIZE>;
    };
    */



    // Friendship goes both ways here.
    friend class iterator;
    // friend class const_iterator;  // not implemented... try it if you want.



  private:
    // A fixed-size static array with constant capacity that represents the
    // RingQueue
    ItemType buffer[MAX_SIZE];

    // The starting index. It changes according to a very specific set of rules
    // (below).
    int begin_index;

    // The actual size of the RingQueue. Not to be confused with its capacity.
    int ring_size;



    // A helper function that computes the index of 'the end' of the RingQueue
    int end_index() const {
        // Replace the line(s) below with your code.
        return (begin_index + ring_size) % MAX_SIZE; //get the end index by adding the size to the beginning and taking the remainder with the capacity
    }



  public:
    // Constructor
    RingQueue() : begin_index(0), ring_size(0) { }

    // Accessors. Note: 'back()' is not considered part of the array.
    ItemType front() const {
        if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // Feel free to throw instead...


        // Replace the line(s) below with your code.
        return buffer[begin_index]; //return the oldest item
    }

    ItemType back() const {
        if ( ring_size == 0 ) std::cerr<< "Warning: Empty ring!\n" ;
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // Feel free to throw instead...


        // Replace the line(s) below with your code.
        return buffer[end_index()]; //return the newest item
    }



    // Mutators
    void push_back( const ItemType& value ){
		back() = value; //put the new item at the end of the queue
		if (ring_size < MAX_SIZE) { //if the ring is not at full capacity
			++ring_size; //update the size to reflect the ring's new size
		}
		else { //if the ring is at full capacity
			++begin_index; //we have just overwritten the beginning of the ring, so increment the begin_index
		}
        return;
    }

    void pop_front(){
		++begin_index; //incrementing the beginning index will serve the same purpose as removing the element
		--ring_size; //update the size
        return;
    }


    // Functions that return iterators
    iterator begin() {
        // Replace the line(s) below with your code.
        return iterator(this,0); //this will suffice as it will create an iterator for the ring at the beginning index
    }

    iterator end() {
        // Replace the line(s) below with your code.
        return iterator(this,ring_size); //the offset of the end index from the beginning index is the size of the ring
    }


    // Miscellaneous functions
    size_t size() const {
        // Replace the line(s) below with your code.
        return ring_size; //return the size of the ring
    }

    // Debugging functions
    void dump_queue() const {
        std::cout << "Raw queue...\n";
        for ( size_t i = 0 ; i < MAX_SIZE ; ++i )
            std::cout << "Val: " << buffer[i] << ", at: " << buffer + i << '\n';
        std::cout << '\n';
        return;
    }

};




int main(){
    RingQueue<int,7> rq;
    rq.dump_queue();

    for ( int i = 0 ; i < 8 ; ++i )
        rq.push_back(i+1);

    rq.dump_queue();
    rq.pop_front();

    std::cout << "Queue via size:\n";

    // RingQueue<int,7>::iterator it = rq.begin() ;
    auto it = rq.begin() ;
    for ( size_t i = 0 ; i < rq.size() ; ++i ) {
        std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
        ++it;
    }
    std::cout << '\n';



    // Uncomment the block below only when you have a working implementation of
    // RingQueue<ItemType,int>::end().  If the implementation is not correct, it
    // might result in an infinite loop.
    /**
    std::cout << "Queue via iterators:\n";
    for ( auto it = rq.begin() ; it != rq.end() ; ++it ) {
        std::cout << "Value: " << *it << ", address: " << &(*it) << '\n';
    }
    std::cout << '\n';
    */



    rq.dump_queue();

    return 0;
}



/**
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    The output of your program [once the missing code is added] should look more
    or less like the output below.

    Note: It is dependent on the device where this driver is executed. However,
    it should be clear that the difference between consecutive memory addresses
    is equal to the number reported by 'size_of( int )'.
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        Raw queue...
        Val: 2, at: 0x7ffcdeeaab40
        Val: 0, at: 0x7ffcdeeaab44
        Val: 4198285, at: 0x7ffcdeeaab48
        Val: 0, at: 0x7ffcdeeaab4c
        Val: 0, at: 0x7ffcdeeaab50
        Val: 0, at: 0x7ffcdeeaab54
        Val: 0, at: 0x7ffcdeeaab58

        Raw queue...
        Val: 8, at: 0x7ffcdeeaab40
        Val: 2, at: 0x7ffcdeeaab44
        Val: 3, at: 0x7ffcdeeaab48
        Val: 4, at: 0x7ffcdeeaab4c
        Val: 5, at: 0x7ffcdeeaab50
        Val: 6, at: 0x7ffcdeeaab54
        Val: 7, at: 0x7ffcdeeaab58

        Queue via size:
        Value: 3, address: 0x7ffcdeeaab48
        Value: 4, address: 0x7ffcdeeaab4c
        Value: 5, address: 0x7ffcdeeaab50
        Value: 6, address: 0x7ffcdeeaab54
        Value: 7, address: 0x7ffcdeeaab58
        Value: 8, address: 0x7ffcdeeaab40

        Queue via iterators:
        Value: 3, address: 0x7ffcdeeaab48
        Value: 4, address: 0x7ffcdeeaab4c
        Value: 5, address: 0x7ffcdeeaab50
        Value: 6, address: 0x7ffcdeeaab54
        Value: 7, address: 0x7ffcdeeaab58
        Value: 8, address: 0x7ffcdeeaab40

        Raw queue...
        Val: 8, at: 0x7ffcdeeaab40
        Val: 2, at: 0x7ffcdeeaab44
        Val: 3, at: 0x7ffcdeeaab48
        Val: 4, at: 0x7ffcdeeaab4c
        Val: 5, at: 0x7ffcdeeaab50
        Val: 6, at: 0x7ffcdeeaab54
        Val: 7, at: 0x7ffcdeeaab58
 */
