#include "jstpch.h"
#include "LayerStack.h"

namespace Just
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for( Layer* layer : m_Layers )
		{
			delete layer;
		}
	}

	void Just::LayerStack::PushLayer( Layer * layer )
	{
		m_LayerInsert = m_Layers.insert( m_LayerInsert, layer );
	}

	void Just::LayerStack::PushOverlay( Layer * overlay )
	{
		m_Layers.push_back( overlay );
	}

	void Just::LayerStack::PopLayer( Layer * layer )
	{
		auto it = std::find( m_Layers.begin(), m_LayerInsert, layer );
		if( it != m_LayerInsert )
		{
			m_Layers.erase( it );
			m_LayerInsert--;
		}
	}

	void Just::LayerStack::PopOverlay( Layer * overlay )
	{
		auto it = std::find( m_LayerInsert, m_Layers.end(), overlay );
		if( it != m_Layers.end() )
		{
			m_Layers.erase( it );
		}
	}
}