/*
To-Do
- Fixed_Point
  - Handle negitive numbers
  - Test conversions
  - PUPer
- Floating Point
  - Handle mantissa rounding
  - Handle exponent over/underflow
  - Test convertions
*/

#include <iostream>
using std::cout;
using std::endl;
#include <string>

#include <stdexcept>
#include <cfloat>
#include <climits>
#include <limits>
#include <typeinfo>

#include "network_types.h"



void info(){
	std::cout << "Unsigned integral Types (bits)" << std::endl;
	std::cout << "bool:  " << std::numeric_limits<bool>::digits << std::endl;
	std::cout << "char:  " << std::numeric_limits<unsigned char>::digits << std::endl;
	std::cout << "short: " << std::numeric_limits<unsigned short>::digits << std::endl;
	std::cout << "int:   " << std::numeric_limits<unsigned int>::digits << std::endl;
	std::cout << "long:  " << std::numeric_limits<unsigned long>::digits << std::endl;
	std::cout << "long long: " << std::numeric_limits<unsigned long long>::digits << std::endl;
	std::cout << std::endl;

	std::cout << "Floating Types (bits)" << std::endl;
	std::cout << "Single_Precision" << std::endl;
	std::cout << "sizeof("<< typeid(Single_Precision::raw_type).name() <<"): " << sizeof(Single_Precision::raw_type)*CHAR_BIT << std::endl;
	std::cout << "Radix:    " << std::numeric_limits<float>::radix << std::endl;
	std::cout << "Sign:     " << Single_Precision::sign_bits << std::endl;
	std::cout << "Exponent: " << Single_Precision::exponent_bits << std::endl;
	std::cout << "Mantissa: " << Single_Precision::mantissa_bits << std::endl;
	std::cout << "Bits:     " << Single_Precision::bits << std::endl;
	std::cout << "Exp Bias: " << Single_Precision::exponent_bias << std::endl;
	std::cout << std::endl;
	std::cout << "Double_Precision" << std::endl;
	std::cout << "sizeof("<< typeid(Double_Precision::raw_type).name() <<"): " << sizeof(Double_Precision::raw_type)*CHAR_BIT << std::endl;
	std::cout << "Radix:    " << std::numeric_limits<float>::radix << std::endl;
	std::cout << "Sign:     " << Double_Precision::sign_bits << std::endl;
	std::cout << "Exponent: " << Double_Precision::exponent_bits << std::endl;
	std::cout << "Mantissa: " << Double_Precision::mantissa_bits << std::endl;
	std::cout << "Bits:     " << Double_Precision::bits << std::endl;
	std::cout << "Exp Bias: " << Double_Precision::exponent_bias << std::endl;
	std::cout << std::endl;
	std::cout << "Extended_Double_Precision" << std::endl;
	std::cout << "sizeof("<< typeid(Extended_Double_Precision::raw_type).name() <<"): " << sizeof(Extended_Double_Precision::raw_type)*CHAR_BIT << std::endl;
	std::cout << "Radix:    " << std::numeric_limits<float>::radix << std::endl;
	std::cout << "Sign:     " << Extended_Double_Precision::sign_bits << std::endl;
	std::cout << "Exponent: " << Extended_Double_Precision::exponent_bits << std::endl;
	std::cout << "Mantissa: " << Extended_Double_Precision::mantissa_bits << std::endl;
	std::cout << "Bits:     " << Extended_Double_Precision::bits << std::endl;
	std::cout << "Exp Bias: " << Extended_Double_Precision::exponent_bias << std::endl;
	std::cout << std::endl;
}


template <typename From, typename To>
void Test_Fixed_Point(From & test, To & result, const char* test_name = ""){
	Fixed_Point Fixed_Point_Tester(test);	
	try{
		result = Fixed_Point_Tester;
	}catch(std::length_error e){
		if(test <= std::numeric_limits<To>::max() && test >= std::numeric_limits<To>::min()){
			std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << "\t\t *** FAILED ***" << std::endl;
			std::cout << "\t Invalid error: " << e.what() << std::endl;
			std::cout << std::endl;
		}else{
			std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << " Passed" << std::endl;
			std::cout << std::endl;
		}
		return;
	}catch(...){
		std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << "\t\t *** FAILED ***" << std::endl;
		std::cout << "\t Invalid unknown error" << std::endl;
		std::cout << std::endl;
		return;
	}

	if (test == result){
		std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << " Passed" << std::endl;
		std::cout << std::endl;
	}else{
		std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << "\t\t *** FAILED ***" << std::endl;
		std::cout << std::endl;
	}
	return;
}
void Fixed_Point_Test_Suit(){

	bool bool_type[2];
	signed char signed_char_type[2];
	signed short signed_short_type[2];
	signed int signed_int_type[2];
	signed long signed_long_type[2];
	signed long long signed_long_long_type[2];
	unsigned char unsigned_char_type[2];
	unsigned short unsigned_short_type[2];
	unsigned int unsigned_int_type[2];
	unsigned long unsigned_long_type[2];
	unsigned long long unsigned_long_long_type[2];

#pragma region unsigned long long -> unsigned long long tests
	unsigned_long_long_type[0] = std::numeric_limits<unsigned long long>::max();
	unsigned_long_long_type[1] = 0;
	Test_Fixed_Point(unsigned_long_long_type[0], unsigned_long_long_type[1], "(ULL max)");

	unsigned_long_long_type[0] = std::numeric_limits<unsigned long long>::max()/2;
	unsigned_long_long_type[1] = 0;
	Test_Fixed_Point(unsigned_long_long_type[0], unsigned_long_long_type[1], "(ULL half)");

	unsigned_long_long_type[0] = std::numeric_limits<unsigned long long>::min();
	unsigned_long_long_type[1] = 1;
	Test_Fixed_Point(unsigned_long_long_type[0], unsigned_long_long_type[1], "(ULL min)");
#pragma endregion
#pragma region signed long long -> signed long long tests
	signed_long_long_type[0] = std::numeric_limits<signed long long>::max();
	signed_long_long_type[1] = 0;
	Test_Fixed_Point(signed_long_long_type[0], signed_long_long_type[1], "(LL max)");

	signed_long_long_type[0] = std::numeric_limits<signed long long>::max()/2;
	signed_long_long_type[1] = 0;
	Test_Fixed_Point(signed_long_long_type[0], signed_long_long_type[1], "(LL +half)");

	signed_long_long_type[0] = 0;
	signed_long_long_type[1] = 1;
	Test_Fixed_Point(signed_long_long_type[0], signed_long_long_type[1], "(LL 0)");

	signed_long_long_type[0] = std::numeric_limits<signed long long>::min()/2;
	signed_long_long_type[1] = 0;
	Test_Fixed_Point(signed_long_long_type[0], signed_long_long_type[1], "(LL -half)");

	signed_long_long_type[0] = std::numeric_limits<signed long long>::min();
	signed_long_long_type[1] = 0;
	Test_Fixed_Point(signed_long_long_type[0], signed_long_long_type[1], "(LL min)");
#pragma endregion
#pragma region unsigned long long  -> unsigned char
	unsigned_long_long_type[0] = std::numeric_limits<unsigned long long>::max();
	unsigned_char_type[1] = 0;
	Test_Fixed_Point(unsigned_long_long_type[0], unsigned_char_type[1], "(LL min)");
#pragma endregion
#pragma region signed long long  -> signed char
	signed_long_long_type[0] = std::numeric_limits<signed long long>::min();
	signed_char_type[1] = 0;
	Test_Fixed_Point(signed_long_long_type[0], signed_char_type[1], "(LL min)");
#pragma endregion
}

template <typename From, typename To>
void Test_Floating_Point(From & test, To & result, const char* test_name = ""){
	Floating_Point Floating_Point_Tester(test);
	try{
		result = Floating_Point_Tester;
	}catch(std::length_error e){
		if(test <= std::numeric_limits<To>::max() && test >= std::numeric_limits<To>::min()){
			std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << "\t\t *** FAILED ***" << std::endl;
			std::cout << "\t Invalid error: " << e.what() << std::endl;
		}else{
			std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << " Passed" << std::endl;
			std::cout << "\tError thrown." << std::endl;
		}
		std::cout << std::endl;
		return;
	}catch(...){
		std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << "\t\t *** FAILED ***" << std::endl;
		std::cout << "\t Invalid unknown error" << std::endl;
		std::cout << std::endl;
		return;
	}


	if(std::numeric_limits<From>::digits < std::numeric_limits<To>::digits){            // From is smaller than To
		std::cout << "Not Implemented Yet / Read standard" << std::endl;
	}else if(std::numeric_limits<From>::digits == std::numeric_limits<To>::digits){     // From is equal to To
		if (test != result){
			std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << "\t\t *** FAILED ***" << std::endl;
			std::cout << "  test:   " << test << std::endl;
			std::cout << "  result: " << result << std::endl;
			std::cout << std::hex;
			std::cout << "    Sign:     " << ((unsigned long long)Floating_Point_Tester.sign) << std::endl;
			std::cout << "    Exponent: " << ((unsigned long long)Floating_Point_Tester.exponent) << std::endl;
			std::cout << "    Mantissa: " << ((unsigned long long)Floating_Point_Tester.mantissa) << std::endl;
			std::cout << std::dec;
		}else{
			std::cout << typeid(From).name() << " -> " << typeid(To).name() << " " << std::string(test_name) << " Passed" << std::endl;
		}	
	}else{																				// From is smaller than To
		std::cout << "Not Implemented Yet / Read standard" << std::endl;
	}
	std::cout << std::endl;
}
void Floating_Point_Test_Suit(){
	
	float float_type[2];
//	double double_type[2];
	long double long_double_type[2];

#pragma region float -> float tests
/*
	float_type[0] = std::numeric_limits<float>::max();
	float_type[1] = 0.0;
	Test_Floating_Point(float_type[0], float_type[1]);

	float_type[0] = -0.15625;
	float_type[1] = 0.0;
	Test_Floating_Point(float_type[0], float_type[1]);
	
	float_type[0] = std::numeric_limits<float>::min();
	float_type[1] = 0.0;
	Test_Floating_Point(float_type[0], float_type[1]);
*/
#pragma endregion

#pragma region float -> long double test
	float_type[0] = -3.14159265358979323846;
	long_double_type[1] = 0;
	Test_Floating_Point(float_type[0], long_double_type[1]);
#pragma endregion
}

int main(){

	info();
//	Fixed_Point_Test_Suit();
//	Floating_Point_Test_Suit();
	
	return 0;
}
