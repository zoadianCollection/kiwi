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


#include "PlainTextContainer.hpp"


namespace kiwi{
namespace text{	

PlainTextContainer::PlainTextContainer()
{
	// noting to do
}

Line* PlainTextContainer::line(kiwi::uint32_t linePos)
{
//	ScopedBlockMacro(__scop, "PlainTextContainer::line" )
	// out of bounds...
	if(linePos >= nbLines() ) return 0;
	
	//general case
	std::list<kiwi::text::PlainTextLine>::iterator it = _lines.begin();
	while( linePos-- > 0 ){ ++it; }
	return &(*it);
}

void PlainTextContainer::insertLine(kiwi::uint32_t linePos, const PlainTextLine& toInsert)
{
//	ScopedBlockMacro(__scop, "PlainTextContainer::insertLine" )
	if(linePos > nbLines() ) return;
	
	//general case, kiwi::uint32_t position
	std::list<kiwi::text::PlainTextLine>::iterator it = _lines.begin();
	while( linePos > 0 ){
		++it;
		--linePos;
	}
	_lines.insert(it, toInsert);
}

void PlainTextContainer::insertLine(kiwi::uint32_t linePos, const Line& toInsert)
{
	insertLine(linePos, PlainTextLine(toInsert.str()) );
}

void PlainTextContainer::clear()
{
	_lines.clear();
}

void PlainTextContainer::append(std::istream& inputStream)
{
	while( !inputStream.eof() )
	{
		kiwi::string line;
		std::getline(inputStream, line);
		insertLine(nbLines(), PlainTextLine(line) );
	}
}

void PlainTextContainer::init(std::istream& inputStream)
{
	clear();
	append(inputStream);
}

void PlainTextContainer::removeLine(kiwi::uint32_t linePos)
{
	ScopedBlockMacro(__scop, "PlainTextContainer::removeLine" )
	// out of bounds...
	if(linePos >= nbLines() ) return;
	
	//general case
	std::list<kiwi::text::PlainTextLine>::iterator it = _lines.begin();
	while( linePos > 1 ){
		++it;
		--linePos;
	}
	_lines.erase(it);
}

void PlainTextContainer::removeLines(kiwi::uint32_t firstLine, kiwi::uint32_t lastLine)
{
	ScopedBlockMacro(__scop, "PlainTextContainer::removeLines" )
	// out of bounds...
	if(firstLine >= nbLines() ) return;
	if(lastLine >= nbLines() ) lastLine = nbLines() - 1;

	int i = 0;
	std::list<kiwi::text::PlainTextLine>::iterator itf = _lines.begin();
	while( i++ < firstLine ){ ++itf; }
	std::list<kiwi::text::PlainTextLine>::iterator itl = itf;
	while( i++ < lastLine ){ ++itl; }
	_lines.erase(itf,itl);
}


PlainTextContainer::lock_t PlainTextContainer::lock(kiwi::uint32_t firstLinePos
		, kiwi::uint32_t lastLinePos )
{

}			

void PlainTextContainer::unlock( PlainTextContainer::lock_t id )
{
	
}

bool PlainTextContainer::isLocked(kiwi::uint32_t firstLinePos, kiwi::uint32_t lastLinePos) const
{

}


}// namespace
}// namespace