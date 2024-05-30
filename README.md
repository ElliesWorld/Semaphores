Design a thread-safe, single-instance circular buffer data structure for storing and retrieving integers.

    The buffer can hold a maximum of 8 integers.
    
    A Producer thread adds integers to the buffer.
    
    Four Consumer threads independently remove integers from the buffer.
    
    The Producer and Consumer threads operate at different speeds.
    
    When the buffer is empty, Consumer threads will wait. When the buffer is full, the Producer thread will wait.
