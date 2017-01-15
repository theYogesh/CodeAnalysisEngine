GCC Report:-
DefaultCode.cpp: In function 'int main()':
DefaultCode.cpp:18:10: error: 'b' was not declared in this scope
    cout<<b; //Not declared
          ^


CppCheck Report:-
[DefaultCode.cpp:15]: (error) Array 'str[5]' accessed at index 5, which is out of bounds.
[DefaultCode.cpp:7]: (error) Uninitialized variable: p
[DefaultCode.cpp:15]: (error) Uninitialized variable: str
