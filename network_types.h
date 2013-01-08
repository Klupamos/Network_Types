#if !defined(NETWORK_TYPES_HEADER_FILE)
#define NETWORK_TYPES_HEADER_FILE

#pragma region fixed point precision
#include <cstddef> // for std::size_t
#include <limits>  // for std::numeric_limits<integral>::digits
#include <deque>   // for std::deque

class Fixed_Point{
	private:
		std::deque<char> data;
		/*
		Change this to:
			unsigned char data;
			Fixed_Point * next;
		*/

		static const unsigned char data_mask = 0x7F;
		static const unsigned char cont_mask = 0x80;
		static const unsigned char masks[];

		template<typename T>
		void convert_to_integral(T & datatype);
		template<typename T>
		void convert_from_integral(T datatype);

public:
		// Default and single paramater constructors
		Fixed_Point(){
			data.push_front(char(0));
		}

		// should expand this out to all allowable types
#if TEMPLATE_CONSTRUCTOR
#endif

		Fixed_Point(bool);
		Fixed_Point(signed char);
		Fixed_Point(unsigned char);
		Fixed_Point(signed short);
		Fixed_Point(unsigned short);
		Fixed_Point(signed int);
		Fixed_Point(unsigned int);
		Fixed_Point(signed long);
		Fixed_Point(unsigned long);
		Fixed_Point(signed long long);
		Fixed_Point(unsigned long long);

		operator bool();
		operator signed char();
		operator unsigned char();
		operator signed short();
		operator unsigned short();
		operator signed int();
		operator unsigned int();
		operator signed long();
		operator unsigned long();
		operator signed long long();
		operator unsigned long long();

		template<class PUPer>
		friend void pup(PUPer &, Fixed_Point &);

		template<class PUPer>
		friend PUPer operator<<(PUPer &, Fixed_Point &);

		template<class PUPer>
		friend PUPer operator>>(PUPer &, Fixed_Point &);


};
#pragma endregion

#pragma region floating point precision
#include <cstddef>  // for size_t

class Single_Precision{
	public:
		const static std::size_t bits;
		const static std::size_t sign_bits;
		const static std::size_t mantissa_bits;
		const static std::size_t exponent_bits;
		const static std::size_t exponent_bias;
		typedef float raw_type;
};

class Double_Precision{
	public:
		const static std::size_t bits;
		const static std::size_t sign_bits;
		const static std::size_t mantissa_bits;
		const static std::size_t exponent_bits;
		const static std::size_t exponent_bias;
		typedef double raw_type;
};

class Extended_Double_Precision{
	public:
		const static std::size_t bits;
		const static std::size_t sign_bits;
		const static std::size_t mantissa_bits;
		const static std::size_t exponent_bits;
		const static std::size_t exponent_bias;
		typedef long double raw_type;
};

class Floating_Point{
	private:
		typedef unsigned long long integral_value_type;

	public:
		Fixed_Point sign;
		Fixed_Point mantissa;
		Fixed_Point exponent;
	private:	
		void transfer_bits(void* source, void* destination, size_t source_first, size_t destination_first, size_t length);

	public:
		Floating_Point();
		Floating_Point(float);
		Floating_Point(double);
		Floating_Point(long double);
		operator float();
		operator double();
		operator long double();

		template<typename PUPer>
		friend void pup(PUPer &, Floating_Point &);
};

#pragma endregion
#endif /*NETWORK_TYPES_HEADER_FILE*/
