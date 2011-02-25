
#include "kiwi/image/ChannelOffsetFilter.hpp"
#include "kiwi/image/cairo/ImageContainer.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/generic/RectangleContainer.hpp"
#include <assert.h>



using namespace kiwi;
using namespace kiwi::image;

void ChannelOffsetTest()
{
	typedef cairo::RGBAImageContainer::CoordinateVector CoordinateVector; 

	cairo::RGBAImageContainer inputData("inputImageTransp.png");
	kiwi::core::Node inputDataNode(&inputData);

	kiwi::generic::PointVectorContainer<kiwi::uint32_t, 2> displacement1(CoordinateVector(10,10));
	kiwi::core::Node displacement1Node(&displacement1);

	kiwi::generic::RectangleContainer<kiwi::int32_t,2> region(
		CoordinateVector(0,100),CoordinateVector(600,400) );
	kiwi::core::Node regionNode(&region);
		
	cairo::RGBAImageContainer result("inputImageTransp.png" );	
	kiwi::core::Node resultNode(&result);

	kiwi::image::ChannelOffsetFilter f1;


	assert( inputDataNode.writerOutputPort(0).isComposite() );
	assert( inputDataNode.writerOutputPort(0).nbSubPorts() == 4 );
	
	inputDataNode.readerOutputPort(0).subPort(0) 	>> f1.readerInputPort(0);
	displacement1Node.readerOutputPort(0) 			>> f1.readerInputPort(1);
	regionNode.readerOutputPort(0) 			>> f1.readerInputPort(2);
	resultNode.writerOutputPort(0).subPort(0)		>> f1.writerInputPort(0);

	//typedef kiwi::core::Container TestType;
	typedef kiwi::generic::PointAccessContainerInterface<kiwi::uint8_t,2> TestType;
	TestType* ptr =	resultNode.writerOutputPort(0).subPort(0).getContainer<TestType>() ;
	assert( ptr );

	assert( f1.readerInputPort(0).isConnected() );
	assert( f1.readerInputPort(1).isConnected() );
	assert( f1.writerInputPort(0).isConnected() );

	f1.process();

	result.saveToPng("OffsetFilterOutputImage.png");
}


int main()
{
	ScopedBlockMacro(scop, "ChannelOffsetFilter::Test")
	ChannelOffsetTest();
}