// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
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

#include "kiwi/core/Node.hpp"

#include "kiwi/core/Reader.hpp"
#include "kiwi/core/Writer.hpp"

#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/InputPort.hpp"


namespace kiwi{
namespace core{


template <typename SlotType>
OutputPort<SlotType>::OutputPort( Node* myNode )
	: _enabled(true)
	, _node(myNode)
	, _subPort(0)
{
	// nothing to do
}

template <typename SlotType>
const OutputPort<SlotType>* 
OutputPort<SlotType>::subPort() const
{
	// if there's port rebinding, _subPort 1!= 0 
	// call the _subPort's method
	if(_subPort) return _subPort->subPort();
	// if this is the "subport" return a pointer to self
	else return this;
} 

template <typename SlotType>
void 
OutputPort<SlotType>::disconnect( InputPort<SlotType>* input )
{
//	ScopedBlockMacro(__scop, "OutputPort::disconnect" );
	if( input == 0 ){
		std::list<InputPort<SlotType>*> connectionsTempCopy
			= _connections;
		_connections.clear();
		typename std::list<InputPort<SlotType>*>::iterator
			it = connectionsTempCopy.begin();

		for(int i = 0; i < connectionsTempCopy.size(); ++i)
		{
			InputPort<SlotType>* temp = (*it);
			connectionsTempCopy.erase(it);
			temp->disconnect();
			++it;
		}

	}else
		for(typename std::list<InputPort<SlotType>*>::iterator
			it = _connections.begin()
			; it!= _connections.end()
			; ++it)
		{
			if( (*it) == input ){
				_connections.erase(it);
				input->disconnect();
				return;
			}
		}
}


template <typename SlotType>
void 
OutputPort<SlotType>::bind(OutputPort<SlotType>& port)
{
//	Debug::print() << "port binding" << endl();
	_subPort = &port;

	// note that if the binded Node is deleted, trying to acces
	// this port might cause a segfault
}


template<>
kiwi::string 
OutputPort<Reader>::name() const
{
	return _node->readerOutputName( _node->indexOf(*this) );
}

template<>
kiwi::string 
OutputPort<Writer>::name() const
{
	return _node->readerOutputName(	_node->indexOf(*this) );
}

template <typename SlotType>
portIndex_t 
OutputPort<SlotType>::index() const 
{
	return _node->indexOf(*this);
}

template <typename SlotType>
Node* 
OutputPort<SlotType>::node() const 
{
	return _node;
}

template<>
Tags 
OutputPort<Reader>::tags() const
{ 
	return _node->readerOutputTags( index() ); 
}

template<>
Tags 
OutputPort<Writer>::tags() const
{ 
	return _node->writerOutputTags( index() ); 
}

template <typename SlotType>
bool 
OutputPort<SlotType>::isCompatible(InputPort<SlotType>& input)	
{
	return input.isCompatible(*this); 
}

template <typename SlotType>
bool 
OutputPort<SlotType>::isConnected() const 
{ 
	return (_connections.size() != 0); 
}

template <typename SlotType>
bool 
OutputPort<SlotType>::isEnabled() const 
{ 
	return _enabled; 
}

template <typename SlotType>
typename OutputPort<SlotType>::connectionList 
OutputPort<SlotType>::connections() const 
{ 
	return _connections; 
}


template <typename SlotType>
void 
OutputPort<SlotType>::setEnabled(bool status) 
{
	_enabled = status;
}

}// namespace
}// namespace