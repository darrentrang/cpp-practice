#include <iostream>
#include "pointerAssignment.h"
#include "referenceAssignment.h"
using namespace std;

void uniform_initialization()
{
	//======================================================================================
	// (C++11) uniform initialization - initialize all types (scalars and arrays) with {}
	//======================================================================================
	int a1; //junk value
	int a2 = 0; //copy initialization
	int a3(0); //direct initialization
	string s1; //string default ""
	string s2("C++");

	//all of these below are also copy initializations
	char d1[8]; //uninitialized
	char d2[8] = { '\0' }; //initialize with null terminated character
	char d3[8] = { 'a', 'b', 'c' }; //aggregate initialization
	char d4[8] = { "abcd" };

	//now uniform initialization. use these to avoid copy initializations
	int b1{}; //value initialization. initialize to default value. for all primitive types that is 0
	int b3{ 5 }; //direct initialization.
	char e1[8]{}; //direct initialization. initialize array to default values
	char e2[8]{ "Hello" }; //direct initialization
	//uniform initialization also works with heap based objects
	int* p0 = new int; //uninitialized
	int* p1 = new int{}; //initialized by uniform init.
	char* p2 = new char[8]{};
	char* p3 = new char[8]{ "Hello" }; //dynamic array initialized. this did not work before

	//should u use uniform init everywhere? 
	//for primitive types its ok to use assignment for init. 
	//for user definied types u should always use uniform init.
	//recap:
	//		1. value init.:   T obj{}
	//		2. direct init.:  T obj{v}
	//		3. copy init.:    T obj = v   should be avoided with user defined objects
	//
	//	advantages:
	//		1. forces initialization
	//		2. u can use direct init. for array types
	//		3. prevents narrowing conversions (when u assign a float to an int)
	//                  float f{};
	//					int i{f}; --> this will give error. conversion from float to int requires a narrowing conversion
	//		4. uniform syntax
	//======================================================================================
	// End uniform initialization
	//======================================================================================
}
void pointers()
{
	//(C++11) introducing nullptr

	int x = 10;
	cout << "address of x = " << &x << endl;
	int* ptr = &x;
	cout << ptr << endl;

	void* vptr = &x; //void pointer can point to any type's address

	//pointers that are uninit. are random addresses. some may not even compile

	//dereference and assign new value
	*ptr = 5;
	cout << x << endl;

	int y = *ptr; //assign y to ptr's value
	cout << y << endl;

	/*
	NULL is a macro in C & pre C++11
	defined as 0 in most compilers
	used to init. pointer types
	C++11 introduces a new type of null called nullptr
	this is type safe and better than NULL macro
	*/
	void* ptr2 = nullptr;
	cout << ptr2 << endl;

	int* ptr3 = nullptr;
	//cout << *ptr3 << endl; //access violation at runtime. dereferencing a null pointer
}

void pointer_assignment()
{
	int aval = 5;
	int bval = 6;
	int* a = &aval;
	int* b = &bval;
	int* result = new int{};

	cout << Add(a, b) << endl;

	AddVal(a, b, result);
	cout << *result << endl;

	cout << *a << " " << *b << endl;
	Swap(a, b);
	cout << *a << " " << *b << endl;

	Factorial(a, result);
	cout << *result << endl;
}

void references()
{
	//no memory is allocated for a reference. its just a new name for an existing variable
	int x = 10;   //referent
	int& ref = x; //reference
	cout << x << " " << ref << endl;
	cout << &x << " " << &ref << endl; //they share same address

	int y = 22;
	ref = y; //assign y's value to ref. does NOT bind ref to y
	cout << x << " " << ref << endl;

	//references must be initialized. cannot be null. 

	//references are always bound to its referent; ie it will always have that 1 same address for its life
	//pointers can change the address it points to

	//references have no storage required so has same address as referent
	//pointers has its own storage so will have a different address 

	//references don't need dereference to access value
	//pointers require dereference operator to access value
}

void reference_assignment()
{
	int a = 6;
	int b = 10;
	int answer;

	Add(a, b, answer);
	cout << answer << endl;

	Factorial(a, answer);
	cout << answer << endl;

	cout << a << " " << b << endl;
	Swap(a, b);
	cout << a << " " << b << endl;
}

void const_pointer_print_example(const int* ptr)
{
	cout << *ptr << endl;
	//*ptr = 700; //const in the parameters prevents function from moidfying ptr value
}

void const_reference_print_example(const int& ref)
{
	cout << ref << endl;
	//ref = 10; //the const prevents function from changing the value of ref
}

void const_qualifier()
{
	//const qualifier
	//const <type> <variable> {initializer}
	float radius = 0;
	float area = 3.141f * radius * radius; //3.141f is magic number and causes confusion. replace with below
	const float PI{ 3.141f };
	area = PI * radius * radius; //good practice to have consts all uppercase

	const int CHUNK_SIZE = 512;
	//int* ptr = &CHUNK_SIZE;  //compiler will not allow because then you can modify a const variable through its address
	const int* ptr = &CHUNK_SIZE;  //this is allowed. you cannot modify the value through pointer. *ptr is constant and ptr is not.
	int x = 10;
	ptr = &x;
	//*ptr = 1; // not allowed because the pointer is const

	//to make pointer also const (not just the *ptr)
	const int* const cptr = &CHUNK_SIZE; //cannot change address of ptr once assigned
	//this is good if you pass a pointer to a function, but want to ensure that the function does not modify the address value
	const_pointer_print_example(&x);
	cout << "main->x : " << x << endl;

	//const references
	const int& ref = 5; //const allows initialization to a literal. w/o must need a referent 
	int x1 = 5;
	const_reference_print_example(x1);

	//const reference vs const pointer
	//reference easier to use and easier to read syntax
	//reference easier to use with objects
	//print functions for example, u dont need a new variable. and since it is const, you can pass literals rather than only variables
}

void const_pointer_assignement()
{
	int x = 5;
	const int MAX = 12;
	int& ref_x1 = x;
	const int& ref_x2 = x;

	//Try to modify the pointer (e.g. ptr1) and the pointee value (*ptr1)
	const int* ptr1 = &x; //*ptr is const (value at address is const). ptr is not (address can point elsewhere). 
	int* const ptr2 = &x; //*ptr is NOT const (value at address can change). ptr is const (address can NOT point elsewhere).
	const int* const ptr3 = &x; //*ptr is const (value at address is const). ptr is const (address can NOT point elsewhere)


	//Find which declarations are valid. If invalid, correct the declaration
	const int* ptr3a = &MAX;
	//int* ptr4 = &MAX; //cant do because then u can change MAX through the pointer, but MAX is const int

	const int& r1 = ref_x1;
	//int& r2 = ref_x2; //cant do because setting a const ref to a ref

	//int*& p_ref1 = ptr1;
	//const int*& p_ref2 = ptr2;
}

void auto_keyword()
{
	//(C++11) auto keyword
	//allows the compiler to automatically infer the type from the initializer
	//this means initializer is important
	//auto <identifier> = <initializer>
	//<initializer> could be an expression that returns some value (literal, math expression, function call that returns a value)
	auto i = 10;
	//auto j; //this will not compile. need initializer
	auto j = 5;
	auto sum = i + j;
	auto sum2 = i + 4.3f; //adding int and float. auto will choose the largest type that is in the expression

	//auto doesnt carry the const (unless u use reference)
	const int x = 10;
	auto var = x; //var is not const int, it is just int
	const auto var2 = x; //var2 is now const int

	auto& var3 = x; //var3 is const int. this time the const did carry because we are using reference
	auto ptr = &x; //qualifier not discarded. ie ptr is a pointer to a const int

	auto list = { 1,2,3,4 }; //list of ints initialized to 1,2,3,4
	auto list2{ 1 }; //int that is initialzied to 1
}

void static_keyword_sidenote()
{
	//static variables = space for variable gets allocated for the lifetime of the program. even if function is called multiple times, space for the static variable is allocated only once and the value of the variable in the prvious call gets carried through the next function call. this is useful for implementing coroutines in c++ or any other application where previous state of function needs to be stored
	static auto y = 2;
}

void range_based_for_loops()
{
	//(C++11) range based for loop
	int arr[] = { 1,2,3,4,5 };
	for (auto& x : arr) //declare x as a reference to each element in the array. or else it returns a copy of the element in the array
	{
		x = 3; //set all values of array to 3 (requires reference variable in for loop)
		cout << x << " ";
	}
	cout << endl;

	for (const auto& x : arr) //x is a reference to each element in array (not a copy) but won't be able to be modified because of const keyword
	{
		cout << x << " ";
	}
	cout << endl;

	//can also iterate through initialzer list
	for (auto x : { 1,2,3,4 })
	{
		cout << x << " ";
	}
	cout << endl;
}

//============================================================
// function overloading
// 2 functions below have same names, but compiler knows which
// one to call based on arguments passed
// name mangling = unique names generated by compiler for functions
//                 allows linker to link the call with the correct overloaded
//				   function.
// because the name mangling is unknown, C++ functions are not callable from C code
// need to use extern "C" in order to allow C or other languages to call C++ functions
//
// extern C suppresses name mangling, can be applied to only one function in a set of overloaded functions
// (if 2 functions called Print(), only one can be extern C). 
//============================================================
int Add(int a, int b)
{
	return a + b;
}

double Add(double a, double b)
{
	return a + b;
}

//extern "C" means that this function can be invoked from C or other languages
extern "C" void Print(int* x)
{
	cout << "inside void Print(int* x): " << *x << endl;
}

void Print(const int* x)
{
	cout << "inside void Print(const int* x): " << *x << endl;
}
//============================================================
// end function overloading
//============================================================

int main()
{
	//function overloading
	int x = 1;
	Print(&x);
	
	
	return 0;
}