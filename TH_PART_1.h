//author Salim TOP 17050111014

#include <stdio.h>

typedef int SType;
#define STACKSIZE 10
#define EMPTY_STACK -9999

typedef struct {

	SType datas[STACKSIZE]; //a merged two array which have 50 sizes
	int top1;//first arrays top
	int top2;//seccond arrays top(which starts from end to initial)
	   
}double_Stack;

void initialize_s1(double_Stack *stck);
void initialize_s2(double_Stack *stck);
int is_empty_s1(double_Stack *stck);
int is_empty_s2(double_Stack *stck);
int is_full_s1(double_Stack *stck);
int is_full_s2(double_Stack *stck);
int push1(double_Stack *stck, SType inp);
int push2(double_Stack *stck, SType inp);
SType pop1(double_Stack *stck);
SType pop2(double_Stack *stck);

//----------------------------------------------------------------------------------------------------------------

void initialize_s1(double_Stack *stck) {

	stck->top1 = -1;//initializing first array
}
//----------------------------------------------------------------------------------------------------------------
void initialize_s2(double_Stack *stck) {

	stck->top2 = STACKSIZE; // initializing second array from another end point

}
//----------------------------------------------------------------------------------------------------------------
int is_empty_s1(double_Stack *stck) {

	if (stck->top1 == -1)
		return 1;
	return 0;
}
//----------------------------------------------------------------------------------------------------------------
int is_empty_s2(double_Stack *stck) {

	if (stck->top2 == STACKSIZE)	//second array starts from stack size
		return 1;					
	return 0;
}
//----------------------------------------------------------------------------------------------------------------
int is_full_s1(double_Stack *stck) {

	if ((stck->top2 - stck->top1) == 1)		//if two array meet in the middle, that means stacks is full
		return 1;							//this function is same for two array element
	return 0;

}
//----------------------------------------------------------------------------------------------------------------
int is_full_s2(double_Stack *stck) {

	if ((stck->top2 - stck->top1) == 1)
		return 1;
	return 0;

}
//----------------------------------------------------------------------------------------------------------------
int push1(double_Stack *stck, SType inp) {

	if (is_full_s1(stck))
		printf("ERROR!! Stacks are full!");
	else {
		stck->top1++;
		stck->datas[stck->top1] = inp;
	}

	return (stck->top2 - stck->top1) - 1; //I want to see how many data size do ý have
}
//----------------------------------------------------------------------------------------------------------------
int push2(double_Stack *stck, SType inp) {

	if (is_full_s2(stck))
		printf("ERROR!! Stacks are full!");
	else {
		stck->top2--;
		stck->datas[stck->top2] = inp;
	}

	return (stck->top2 - stck->top1) - 1; //I want to see how many data size do ý have
}
//----------------------------------------------------------------------------------------------------------------
SType pop1(double_Stack *stck) {

	if (is_empty_s1(stck)) {
		printf("Error: Stack is empty!\n");
		return EMPTY_STACK;
	}

	else {
		return stck->datas[stck->top1--];
	}

}
//----------------------------------------------------------------------------------------------------------------
SType pop2(double_Stack *stck) {

	if (is_empty_s2(stck)) {
		printf("Error: Stack is empty!\n");
		return EMPTY_STACK;
	}

	else {
		return stck->datas[stck->top2++];
	}

}
//----------------------------------------------------------------------------------------------------------------
