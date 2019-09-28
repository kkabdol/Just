#include "jstpch.h"
#include "Application.h"

#include "Just/Renderer/Renderer.h"

namespace Just
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Camera( -1.6f, 1.6f, -0.9f, 0.9f )
	{
		JST_CORE_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_Window = std::unique_ptr< Window >( Window::Create() );
		m_Window->SetEventCallback( JST_BIND_EVENT_FN( Application::OnEvent ) );

		PushOverlay( new ImGuiLayer );

		m_VertexArray.reset( VertexArray::Create() );

		float vertices[ 3 * 7 ] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		

		std::shared_ptr<VertexBuffer> vertexBuffer( VertexBuffer::Create( vertices, sizeof( vertices ) ) );
		vertexBuffer->SetLayout( {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		} );
		m_VertexArray->AddVertexBuffer( vertexBuffer );

		uint32_t indices[ 3 ] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer( IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint32_t ) ) );
		m_VertexArray->SetIndexBuffer( indexBuffer );


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader = std::make_shared<Shader>( vertexSrc, fragmentSrc );


		// test
		m_SquareVA.reset( VertexArray::Create() );

		float squareVertices[ 3 * 4 ] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};


		std::shared_ptr<VertexBuffer> squareVB( VertexBuffer::Create( squareVertices, sizeof( squareVertices ) ) );
		squareVB->SetLayout( {
			{ ShaderDataType::Float3, "a_Position" }
		} );
		m_SquareVA->AddVertexBuffer( squareVB );

		uint32_t squareIndices[ 6 ] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB( IndexBuffer::Create( squareIndices, sizeof( squareIndices ) / sizeof( uint32_t ) ) );
		m_SquareVA->SetIndexBuffer( squareIB );


		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main()
			{
				color = vec4( 0.2, 0.3, 0.8, 1.0 );
			}
		)";

		m_BlueShader = std::make_shared<Shader>( blueShaderVertexSrc, blueShaderFragmentSrc );
	}

	void Application::Run()
	{
		while( m_Running )
		{
			RenderCommand::SetClearColor( { 0.1f, 0.1f, 0.1f, 1.0f } );
			RenderCommand::Clear();

			m_Camera.SetPosition( { 0.5f, 0.5f, 0.0f } );
			m_Camera.SetRotation( 45.0f );

			Renderer::BeginScene( m_Camera );

			Renderer::Submit( m_BlueShader, m_SquareVA );
			Renderer::Submit( m_Shader, m_VertexArray );
			
			Renderer::EndScene();

			for( Layer* layer : m_LayerStack )
			{
				layer->OnUpdate();
			}

			ImGuiLayer::Begin();
			for( Layer* layer : m_LayerStack )
			{
				layer->OnImGuiRender();
			}
			ImGuiLayer::End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent( Event & e )
	{
		EventDispatcher dispatcher( e );
		dispatcher.Dispatch< WindowCloseEvent >( JST_BIND_EVENT_FN( Application::OnWindowClose ) );

		for( auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			( *--it )->OnEvent( e );
			if( e.handled )
			{
				break;
			}
		}
	}

	void Application::PushLayer( Layer * layer )
	{
		m_LayerStack.PushLayer( layer );
		layer->OnAttach();
	}

	void Application::PushOverlay( Layer * layer )
	{
		m_LayerStack.PushOverlay( layer );
		layer->OnAttach();
	}

	bool Application::OnWindowClose( WindowCloseEvent & e )
	{
		m_Running = false;
		return true;
	}
}