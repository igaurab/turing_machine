// Written by: Gaurab Panthee
// 25th Aug, 2020

#ifndef TAPE_H
#define TAPE_H

/// <Note>
/// This class in a sense represents the entire Turing Machine
///     * char tape :    represents the infinite tape 
///     * head      :    represnets the head/writer of turing machine
///     * scanner   :    function scan() represents the scanner
///
/// We could make seperate classes to represent the Head 
/// and the Scanner but, that would only result in having many classes
/// and will only complicate things.
/// 
/// I want the code to be as readable as possible for begineers as well as far as possible
/// </End Note>

class Tape {
private:
    char *tape;
    int head;
    int size;

public:
    Tape();
    
    //Scanner
    char scan();
    
    // Head
    void write(char c);
    void moveLeft();
    void moveRight();
    void moveToPosition(int x);

    // Display Machine
    void display();
    void printTapeStats();

    // Utility Functions
    int getSize();
    int getHeadPosition();
    void clear();

};

#endif // !TAPE_H
