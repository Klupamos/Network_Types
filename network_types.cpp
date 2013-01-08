

#include "network_types.h"

#include <cstddef>  // for size_t
#include <limits>   // for number sizes
#include <cmath>    // for log
#include <assert.h>

#define BUILD_ERROR_IF(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#pragma region fixed point precision
#include <stdexcept>
	const unsigned char Fixed_Point::masks[] = {0xF0, 0xCC, 0xAA};

	template<typename T>
	void Fixed_Point::convert_to_integral(T & datatype){
		size_t bits_used = 0;

		for (std::deque<char>::iterator dit = data.begin(); dit != data.end(); ++dit){
				
			// grab front of deque and push onto back of ret_val
			datatype <<= 7;
			unsigned char data_byte = (*dit & data_mask);
			datatype |= data_byte;

			// find most significant bit or increment bits used in ret_val
			if (bits_used == 0){
				if(data_byte){

					for(size_t m=0; m<3; ++m){
						if(data_byte & masks[m]){
							data_byte &= masks[m];
							bits_used += (1 << (2-m));
						}else{
							data_byte &= ~masks[m];
						}
					}
					bits_used += 1;
				}
			}else{
				bits_used += 7;
			}
		}

		// throw error if more bits are inspected than representable
		if (bits_used > sizeof(T) * std::numeric_limits<unsigned char>::digits){
			throw std::length_error("Fixed_Point::convert_to_integral Return type too small");
		}
	};

	template<typename T>
	void Fixed_Point::convert_from_integral(T datatype){
		unsigned char tmp;
			
		// grab bottom 7 bits and push to front of deque
		while (data.size() == 0 || datatype != 0){
			tmp ^= tmp;
			tmp = datatype & data_mask;
			datatype >>= 7;
			if (datatype > 0)
				tmp |= 0x80;

			data.push_front(tmp);
		}		
	}

	Fixed_Point::Fixed_Point(bool data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(signed char data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(unsigned char data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(signed short data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(unsigned short data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(signed int data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(unsigned int data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(signed long data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(unsigned long data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(signed long long data_val){
		convert_from_integral(data_val);
	}
	Fixed_Point::Fixed_Point(unsigned long long data_val){
		convert_from_integral(data_val);
	}

	Fixed_Point::operator bool(){
		bool data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator signed char(){
		signed char data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator unsigned char(){
		unsigned char data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator signed short(){
		signed short data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator unsigned short(){
		unsigned short data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator signed int(){
		signed int data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator unsigned int(){
		unsigned int data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator signed long(){
		signed long data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator unsigned long(){
		unsigned long data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator signed long long(){
		signed long long data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};
	Fixed_Point::operator unsigned long long(){
		unsigned long long data_type = 0;
		convert_to_integral(data_type);
		return data_type;
	};




	template<class PUPer>
	void pup(PUPer &, Fixed_Point &){
		assert(false && "Needs to be written");
	}

	template<class PUPer>
	PUPer & operator<<(PUPer & p, Fixed_Point & fp){
		pup(p, fp);
		return p;
	};

	template<class PUPer>
	PUPer & operator>>(PUPer & p, Fixed_Point & fp){
		pup(p, fp);
		return p;
	}


#pragma endregion

#pragma region floating point precision

#pragma region Single_Precision
	const std::size_t Single_Precision::sign_bits = 1;
	const std::size_t Single_Precision::exponent_bias = std::numeric_limits<Single_Precision::raw_type>::max_exponent -1;
	const std::size_t Single_Precision::exponent_bits = std::size_t(std::log((double) std::numeric_limits<Single_Precision::raw_type>::max_exponent) / std::log((double) std::numeric_limits<Single_Precision::raw_type>::radix))+1;
	const std::size_t Single_Precision::mantissa_bits = std::numeric_limits<Single_Precision::raw_type>::digits - 1;
	const std::size_t Single_Precision::bits = (Single_Precision::sign_bits + Single_Precision::mantissa_bits + Single_Precision::exponent_bits); 
#pragma endregion

#pragma region Double_Precision
	const std::size_t Double_Precision::sign_bits = 1;
	const std::size_t Double_Precision::exponent_bias = std::numeric_limits<Double_Precision::raw_type>::max_exponent -1;
	const std::size_t Double_Precision::exponent_bits = std::size_t(std::log((double) std::numeric_limits<Double_Precision::raw_type>::max_exponent) / std::log((double) std::numeric_limits<Double_Precision::raw_type>::radix))+1;
	const std::size_t Double_Precision::mantissa_bits = std::numeric_limits<Double_Precision::raw_type>::digits -1;
	const std::size_t Double_Precision::bits = (Double_Precision::sign_bits + Double_Precision::mantissa_bits + Double_Precision::exponent_bits);
#pragma endregion

#pragma region Extended_Double_Precision
	const std::size_t Extended_Double_Precision::sign_bits = 1;
	const std::size_t Extended_Double_Precision::exponent_bias = std::numeric_limits<Extended_Double_Precision::raw_type>::max_exponent -1;
	const std::size_t Extended_Double_Precision::exponent_bits = std::size_t(std::log((double) std::numeric_limits<Extended_Double_Precision::raw_type>::max_exponent) / std::log((double) std::numeric_limits<Extended_Double_Precision::raw_type>::radix))+1;
	const std::size_t Extended_Double_Precision::mantissa_bits = std::numeric_limits<Extended_Double_Precision::raw_type>::digits -1;
	const std::size_t Extended_Double_Precision::bits = (Extended_Double_Precision::sign_bits + Extended_Double_Precision::mantissa_bits + Extended_Double_Precision::exponent_bits);
#pragma endregion

#pragma region Floating_Point

	/*  Inclusivly transfer length number of bits from source to destination starting with the first bit
	    all numbers are zero based.*/
	void Floating_Point::transfer_bits(void* source, void* destination, size_t source_first, size_t destination_first, size_t length){
		assert(source);
		assert(destination);

		typedef unsigned char unit_type;
		unit_type* src_ptr = ((unit_type*)source);
		unit_type* dest_ptr = ((unit_type*)destination);

		const size_t unit_size = std::numeric_limits<unit_type>::digits;

		size_t src_cur_pos = source_first;
		size_t dest_cur_pos = destination_first;

		unit_type src_mask = 0;
		unit_type dest_mask = 0;
		size_t movement = 0;

		do{
			src_cur_pos += movement;	
			dest_cur_pos += movement;	
			length -= movement;			

			src_mask = ~((1 << (src_cur_pos%unit_size)) - 1);
			dest_mask = ~((1 << (dest_cur_pos%unit_size)) - 1);

			if (length < unit_size){
				dest_mask &= ((1 << (length%unit_size)) -1) << (dest_cur_pos%unit_size);
			}

			dest_ptr[dest_cur_pos/unit_size] &= ~dest_mask;
			dest_ptr[dest_cur_pos/unit_size] |= dest_mask & ((src_ptr[src_cur_pos/unit_size] & src_mask) >> (src_cur_pos%unit_size)) << (dest_cur_pos%unit_size);

			movement = (unit_size - (std::max(src_cur_pos%unit_size, dest_cur_pos%unit_size)));
		}while(length > movement);
	}

	Floating_Point::Floating_Point(){}
	Floating_Point::Floating_Point(float val){
		size_t src_offset = 0;
		integral_value_type mask = 0;

		// grab the mantissa bits
		mask = 0;
		src_offset = 0;
		this->transfer_bits((void*)&val, (void*)&mask, src_offset, 0, Single_Precision::mantissa_bits);
		this->mantissa = Fixed_Point(mask);

		// grab the exponent bits
		mask = 0;
		src_offset = Single_Precision::mantissa_bits;
		this->transfer_bits((void*)&val, (void*)&mask, src_offset, 0, Single_Precision::exponent_bits);// in biased form
		mask -= Single_Precision::exponent_bias;	// remove bias
		this->exponent = Fixed_Point(mask);

		// grab the sign bit
		mask = 0;
		src_offset = Single_Precision::exponent_bits + Single_Precision::mantissa_bits;
		this->transfer_bits((void*)&val, (void*)&mask, src_offset, 0, Single_Precision::sign_bits);
		this->sign = Fixed_Point(mask);
	}
	Floating_Point::operator float(){
		Single_Precision::raw_type ret_val;

		size_t dest_offset = 0;
		integral_value_type mask = 0;

		mask = this->sign;
		dest_offset = Single_Precision::exponent_bits + Single_Precision::mantissa_bits;
		this->transfer_bits((void*)&mask, (void*)&ret_val, 0, dest_offset, Single_Precision::sign_bits);

		mask = this->exponent;
		mask += Single_Precision::exponent_bias;
		dest_offset = Single_Precision::mantissa_bits;
		this->transfer_bits((void*)&mask, (void*)&ret_val, 0, dest_offset, Single_Precision::exponent_bits);

		mask = this->mantissa;
		dest_offset = 0;
		this->transfer_bits((void*)&mask, (void*)&ret_val, 0, dest_offset, Single_Precision::mantissa_bits);

		return ret_val;
	}


	Floating_Point::Floating_Point(double val){

	}
	Floating_Point::operator double(){
		double ret_val;

		return ret_val;
	}

	Floating_Point::Floating_Point(long double val){
		size_t src_offset = 0;
		integral_value_type mask = 0;

		// grab the mantissa bits
		mask = 0;
		src_offset = 0;
		this->transfer_bits((void*)&val, (void*)&mask, src_offset, 0, Extended_Double_Precision::mantissa_bits);
		this->mantissa = Fixed_Point(mask);

		// grab the exponent bits
		mask = 0;
		src_offset = Extended_Double_Precision::mantissa_bits;
		this->transfer_bits((void*)&val, (void*)&mask, src_offset, 0, Extended_Double_Precision::exponent_bits);// in biased form
		mask -= Extended_Double_Precision::exponent_bias;	// remove bias
		this->exponent = Fixed_Point(mask);

		// grab the sign bit
		mask = 0;
		src_offset = Extended_Double_Precision::exponent_bits + Extended_Double_Precision::mantissa_bits;
		this->transfer_bits((void*)&val, (void*)&mask, src_offset, 0, Extended_Double_Precision::sign_bits);
		this->sign = Fixed_Point(mask);
	}
	Floating_Point::operator long double(){
		Extended_Double_Precision::raw_type ret_val;

		size_t dest_offset = 0;
		integral_value_type sign_mask, exp_mask, mant_mask;

		sign_mask = this->sign;
		dest_offset = Extended_Double_Precision::exponent_bits + Extended_Double_Precision::mantissa_bits;
		this->transfer_bits((void*)&sign_mask, (void*)&ret_val, 0, dest_offset, Extended_Double_Precision::sign_bits);

		exp_mask = this->exponent;
		exp_mask += Extended_Double_Precision::exponent_bias;
		integral_value_type filled_exponent = (1 << Extended_Double_Precision::exponent_bits) -1;
		if ((exp_mask & filled_exponent) == exp_mask){
			// exponent will fit

		}else{
			// exponent won't fit
			throw 0;
		}
		dest_offset = Extended_Double_Precision::mantissa_bits;
		this->transfer_bits((void*)&exp_mask, (void*)&ret_val, 0, dest_offset, Extended_Double_Precision::exponent_bits);



		mant_mask = this->mantissa;
		integral_value_type filled_mantissa = (1 << Extended_Double_Precision::mantissa_bits) -1;
		if ((mant_mask & filled_mantissa) == mant_mask){
			// mantissa will fit
		}else{
			// mantissa won't fit so round
		}
		dest_offset = 0;
		this->transfer_bits((void*)&mant_mask, (void*)&ret_val, 0, dest_offset, Extended_Double_Precision::mantissa_bits);

		return ret_val;
	}


	template< typename PUPer>
	void pup(PUPer &p, Floating_Point &fp){
		pup(p, fp.sign);
		pup(p, fp.mantissa);
		pup(p, fp.exponent);
	}
#pragma endregion

#pragma endregion
