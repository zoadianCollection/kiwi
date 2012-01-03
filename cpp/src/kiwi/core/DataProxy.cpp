
#include "kiwi/core/DataProxy.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Context.hpp"
#include "kiwi/core/DataHeader.hpp"

#include <assert.h>

namespace kiwi{
namespace core{



void DataProxy::setTarget( Data* dataptr )
{
    _flag = DATA;
    _ptr.data = dataptr;
}

void DataProxy::setTarget( DataProxy* proxy )
{
    SCOPEDBLOCK("DataProxy::setTarget( DataProxy* )");
    DataProxy * temp = _ptr.proxy;
    if ( proxy ) proxy->increaseRefCount( _refCount );
    if ( temp ) temp->decreaseRefCount( _refCount );
    _flag = PROXY;
    _ptr.proxy = proxy;
}

void DataProxy::setTarget( InputPort* input )
{
    KIWI_NOT_IMPLEMENTED("DataProxy::setTarget");
    _flag = INPUT;
    _ptr.input = input;
}

void DataProxy::setTarget( OutputPort* output )
{
    _flag = DATATYPE;
    _ptr.output = output;
}

/*
DataHeader * DataProxy::dataHeader( Context * c ) const
{
    switch( _flag )
    {
        case DATA : return _ptr.data;
        case DATATYPE : return c->requestData( _ptr.output->dataType() );
        case PROXY : return _ptr.proxy->dataHeader();
        //case INPUT : return _ptr.input->dataHeader(); // TODO add method to input port
        default : return 0;
    }
}
*/

Data* DataProxy::data() const
{
        switch( _flag )
    {
        case DATA : return _ptr.data;
        case PROXY : return _ptr.proxy->data();
        //case DATATYPE : return c->requestData( _ptr.output->dataType() );
        //case INPUT : return _ptr.input->dataHeader(); // TODO add method to input port
        default : return 0;
    }
}

/*
enum{ Error__need_context = 0 };
DataHeader * DataProxy::dataHeader() const
{
    switch( _flag )
    {
        case DATA  : return _ptr.data;
        case PROXY : return _ptr.proxy->data();
        case INPUT : {
            if( _ptr.input->isConnected() )
                return _ptr.input->connection()->dataProxy().dataHeader();
            else return 0;
        }
        case INDEX : assert( Error__need_context );
        default : return 0;
    }
}
*/

void DataProxy::increaseRefCount( uint16 nb )
{
    _refCount += nb;
    if ( _flag == PROXY ) _ptr.proxy->increaseRefCount( nb );
    //else if ( _flag == INPUT ) _ptr.input-> // TODO
}

void DataProxy::decreaseRefCount( uint16 nb )
{
    _refCount -= nb;
    if ( _flag == PROXY ) _ptr.proxy->decreaseRefCount( nb );
    //else if ( _flag == INPUT ) _ptr.input-> // TODO
}

void DataProxy::beginUsingData( Context * c ) const
{
    // the direct reference to the data SHOULD be the first to access it
    if( isDirectRef() )
        dataHeader( c )->increaseRefCount( _refCount );
    assert( dataHeader( c )->refCount() > 0 );
}

void DataProxy::endUsingData( Context * c ) const
{
    dataHeader( c )->increaseRefCount( 1 );
}

bool DataProxy::isAllocated() const
{
    switch( _flag )
    {
        case DATA : return _ptr.data != 0;
        case PROXY : return _ptr.proxy->isAllocated();
        case INPUT : return (_ptr.input->isConnected() && _ptr.input->connection()->dataProxy().isAllocated());
        default : { assert(false); return false; }
    }
}



}//namespace
}//namespace
