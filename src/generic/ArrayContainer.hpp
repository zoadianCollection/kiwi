//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#ifndef KIWI_ARRAYDATA_HPP
#define KIWI_ARRAYDATA_HPP

#include "core/Resource.hpp"
#include "generic/Point.hpp"
#include "utils/types.hpp"
#include <boost/lexical_cast.hpp>
#include "generic/ArrayIterator.hpp"

namespace kiwi
{
namespace generic
{



template<typename TValueType, unsigned int TDimension>
class ArrayContainer : public core::Resource
{
public:
	typedef TValueType ValueType;
	typedef Point<unsigned int, TDimension> Coordinates;
	typedef Point<unsigned int, TDimension+1> IncsType;
	
	enum{ NUMBERS = 0, RVBA = 1, CMJN = 2, XYZ = 3, ABCD = 4, MONO = 5 };
	enum{ READER_OUT = 0, WRITER_OUT = 1 };
	
	/**
	 * @brief constructor
	 */ 
	ArrayContainer(Coordinates size
		, unsigned char nbComponents = 1
		, bool interleaved = false
		, unsigned char nameHint = 0 );
	/**
	 * @brief constructor
	 */
	ArrayContainer(ValueType* dataPtr
		, Coordinates size
		, unsigned char nbComponents = 1
		, bool interleaved = false
		, unsigned char nameHint = 0 );
	/**
	 * @brief destructor
	 */
	~ArrayContainer();


// -----------------------------------------------------------------
	
	ValueType * const getDataPointer() const 
		{ return _data; }
	
	ValueType * const getDataPointer(portIndex_t index) const;
	
	inline unsigned int size() const {return _totalSize;}
	
	inline unsigned int spanSize(unsigned int dimension) 
		{ return _spanSize(dimension); }
		
	inline Coordinates spanSize() { return _spanSize; }
	
	Point<unsigned,TDimension+1> increments(portIndex_t index) const;
	
	inline bool isInterleaved() { return _interleaved; }
	
	ArrayIterator<ValueType> getBasicIterator() const
	{ return ArrayIterator<ValueType>( _data, _data + _totalSize-1, 1 ); }
	
	void printState();
	
protected:
	
	virtual kiwi::string portName(portIndex_t index
		, unsigned char nameHint
		, unsigned char portType = READER_OUT ) const;


private: 
	void init(unsigned char nameHint);

	ValueType* _data;
	bool _deleteDataDestructor;
	unsigned int _totalSize;
	unsigned char _nbComponents;
	Coordinates _spanSize;
	bool _interleaved;
};	




	
}//namespace	
}//namespace	

#include "ArrayContainer.ih"

#endif