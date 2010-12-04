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

/**
 * @file Node.hpp
 * @brief Commandline kiwi program.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @version 0.3
 */
 
#include "kiwi/core.hpp"
#include "kiwi/generic.hpp"
#include "kiwi/text.hpp"
#include "Help.hpp"


#include <iostream>


using namespace kiwi;



using namespace std;

int main(int argc, char *argv[])
{
	Debug::init(true, true, 0);
	//ScopedBlockMacro(__scop,"command line Kiwi")
	for(unsigned i = 0; i < argc; ++i)
		std::cout << "| " << argv[i] << std::endl;
		
	if(argc > 1)
	{
		//if(kiwi::string(argv[1]).find("--version")!= kiwi::string::npos )
		if(kiwi::string(argv[1]) == kiwi::string("--version") )
		{
			cout << "kiwi version " << KIWI_VERSION_MAJOR 
				<< "." << KIWI_VERSION_MINOR 
				<< "." << KIWI_VERSION_PATCH
				<< endl;
			return 0;
		}
		else if(kiwi::string(argv[1]) == kiwi::string("--help") )
		{
			kiwi::Help::print(cout);
		}
		else
		{
			
			kiwi::core::NodeFactory factory;
			
			kiwi::text::UpperCaseFilter::registerToFactory(factory, "UpperCase");
			kiwi::generic::ArrayContainer<int,2>::registerToFactory(factory, "Array2int32");
			kiwi::generic::ValueContainer<kiwi::int32_t>::registerToFactory(factory, "int32");
			kiwi::generic::ValueContainer<float>::registerToFactory(factory, "float");
			
			kiwi::text::TextContainer input;
			kiwi::text::TextWriter inWriter(input, 0);
			
			kiwi::string filterName(argv[1]);
			if(kiwi::string(argv[2]) == "-i")
			{
				inWriter.getLine() = kiwi::string(argv[3]);
			}else return 1;
			
			kiwi::core::Filter* F = factory.newFilter(filterName);
			if(F)
			{
				input.readerOutputPort(0) >> F->readerInputPort(0);
				F->process();
				
				kiwi::text::TextReader reader( F->readerOutputPort(0) );
				
				cout << reader.getLine() << endl();
			}else { cout << "unknown filter name" << endl; }
		}
	}
	else
	{
		cout << "Please specify comandline arguments" << endl;
		return 1;
	}
	
}



