#include "jstpch.h"
#include "LayerStack.h"

namespace Just
{
	LayerStack::~LayerStack()
	{
		for( Layer* layer : m_Layers )
		{
			delete layer;
		}
	}

	void Just::LayerStack::PushLayer( Layer * layer )
	{
		m_Layers.insert(  m_Layers.begin() + m_LayerInsertIndex, layer );
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void Just::LayerStack::PushOverlay( Layer * overlay )
	{
		m_Layers.push_back( overlay );
	}

	void Just::LayerStack::PopLayer( Layer * layer )
	{
		auto begin = m_Layers.begin();
		auto end = m_Layers.begin() + m_LayerInsertIndex;
		auto it = std::find( begin, end, layer );
		if( it != end )
		{
			layer->OnDetach();
			m_Layers.erase( it );
			m_LayerInsertIndex--;
		}
	}

	void Just::LayerStack::PopOverlay( Layer * overlay )
	{
		auto begin = m_Layers.begin() + m_LayerInsertIndex;
		auto end = m_Layers.end();
		auto it = std::find( begin, end, overlay );
		if( it != end )
		{
			overlay->OnDetach();
			m_Layers.erase( it );
		}
	}
}