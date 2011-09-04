module kiwi.dynamic.nodegroup;

import kiwi.core.base;
import kiwi.core.commons;
import kiwi.core.data;
import kiwi.dynamic.node;
import kiwi.dynamic.port;
import kiwi.dynamic.compatibility;

import kiwi.graph.acyclic;

class InternalInputPort : InputPort
{
	this()
	{
		super(null);
	}
}

class InternalOutputPort : OutputPort
{
	this()
	{
		super(null);
	}

	override
	{
        @property
        {
            int maxConnections() { return -1; }
            string name() 
            {
            	throw NotImplemented("InternalOutputPort.name"); 
            }
            OutputPort[] subPorts() 
            {
            	throw NotImplemented("InternalOutputPort.subPorts");
            }
            DataTypeInfo dataType() pure 
            { 
	            throw NotImplemented("InternalOutputPort.dataType"); 
	        }
            Data data()
            {
            	throw NotImplemented("InternalOutputPort.data");
            }
        }

        bool isComposite()
        {
        	return dataType.isComposite;
        	throw NotImplemented("InternalOutputPort.isComposite"); 
        }
        bool isCompatible( InputPort port ){ return (port !is null); }         
                   
    }
    @property void data( kiwi.core.base.Data value )
    {
    	throw NotImplemented("NodeGroup.data:set"); 
    }
}



class NodeGroup : kiwi.core.base.NodeGroup
{		
	override
	{

		bool addNode( Node n )
		{
			_nodes ~= n;
			return true;
		}
		bool removeNode( Node n )
		{
			for(int i = 0; i < _nodes.length; ++i)
				if ( _nodes[i] is n )
				{
					_nodes[i] = _nodes[$-1];
					return true;
				}
			return false;
		}

		void optimize( int flags ){};
		
		void update()
		{
			if ( !isReady ) prepare();

			foreach ( node ; _sortedNodes )
			{
				node.update();
			}

			throw NotImplemented("kiwi.dynamic.nodegroup.NodeGroup.update");			
		}
		bool serialize( DataStream stream )
		{
			throw NotImplemented("kiwi.dynamic.nodegroup.NodeGroup.serialize");
		}
		bool deSerialize( DataStream stream )
		{
			throw NotImplemented("kiwi.dynamic.nodegroup.NodeGroup.deSerialize");
		}

	}// override



	void prepare()
	{
		_sortedNodes = OrderedNodes( _nodes );
	}

	bool isReady()
	{
		throw NotImplemented("NodeGroup.isReady");
	}

	/++
	 + add an input to this group and create an output port to which will connect the nested nodes' input.
	 +/
	void addInput( string name = "in" )
	{
		// TODO: better DataType support !
		_inputBridge ~= new DynamicOutputPort(null, null, null, name);
	}

	void removeInput()
	{
		_inputBridge.length -= 1;
	}

	void addOutput( string name = "out")
	{
		_outputBridge ~= new DynamicInputPort( null, new AlwaysCompatible, name );
	}

	void removeOutput()
	{
		_outputBridge.length -= 1;
	}

protected:
	Data dataSlot(int index)
	{
		throw NotImplemented("NodeGroup.dataSLot");
	}

private:

	int _state;
	OutputPort[] _inputBridge;
	InputPort[] _outputBridge;
	Node[] _nodes;
	Node[] _sortedNodes;
}




//              #######   #####    ####   #####    ####
//                 #      #       #         #     #   
//                 #      ###      ###      #      ### 
//                 #      #           #     #         #
//                 #      #####   ####      #     #### 



version(unittest){ import kiwi.utils.mock; }

unittest
{
	mixin( logTest!"kiwi.dynamic.nodegroup" );
	auto ng = new NodeGroup;

	auto n1 = NewMockNode(2,2);
	auto n2 = NewMockNode(2,2);

	ng.addNode(n1);
	ng.addNode(n2);
}