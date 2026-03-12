/*
Template:
    Step 1: Clarity on Scope of the problem
        - displayContent
        - insertText
        - deleteText
        - Cut / Copy / Paste
        - Undo / Redo
    Step 2: Finalise key Use Cases and APIs
        string displayContent(){}
        void insertText(int position, const string& text){}
        void deleteText(int position, int length){}
        void cut(int position, int length){}
        void copy(int position, int length){}
        void paste(int position){}
        void undo(){}
        void redo(){}
    Step 3: Data Model
    Step 4: Core Class Design
    Step 5: Choose Design Patterns
    Step 6: Implement the code, match all APIs and Use Cases
    Step 7: Check if concurrency is needed, if yes, add locks and mutexes
    Step 8: Scaling and Edge Cases
*/

#include <bits/stdc++.h>
using namespace std;
/*
Data Model
1. 
*/

class TextEditorSystemService{

public:
    string displayContent(){}
    void insertText(int position, const string& text){}
    void deleteText(int position, int length){}

    void cut(int position, int length){}
    void copy(int position, int length){}
    void paste(int position){}
    
    void undo(){}
    void redo(){}
};
int main(){
    
    return 0;
}