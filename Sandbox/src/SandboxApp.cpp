#include <Just.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Just::Layer
{
public:
	ExampleLayer()
		: Layer( "Example" ), m_Camera( -1.6f, 1.6f, -0.9f, 0.9f ), m_CameraPosition( 0.0f ), m_CameraRotation( 0.0f )
	{
		m_VertexArray.reset( Just::VertexArray::Create() );

		float vertices[ 3 * 7 ] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};


		std::shared_ptr<Just::VertexBuffer> vertexBuffer( Just::VertexBuffer::Create( vertices, sizeof( vertices ) ) );
		vertexBuffer->SetLayout( {
			{ Just::ShaderDataType::Float3, "a_Position" },
			{ Just::ShaderDataType::Float4, "a_Color" }
			} );
		m_VertexArray->AddVertexBuffer( vertexBuffer );

		uint32_t indices[ 3 ] = { 0, 1, 2 };
		std::shared_ptr<Just::IndexBuffer> indexBuffer( Just::IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint32_t ) ) );
		m_VertexArray->SetIndexBuffer( indexBuffer );


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4( a_Position, 1.0 );
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

		m_Shader = std::make_shared<Just::Shader>( vertexSrc, fragmentSrc );


		// test
		m_SquareVA.reset( Just::VertexArray::Create() );

		float squareVertices[ 3 * 4 ] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};


		std::shared_ptr<Just::VertexBuffer> squareVB( Just::VertexBuffer::Create( squareVertices, sizeof( squareVertices ) ) );
		squareVB->SetLayout( {
			{ Just::ShaderDataType::Float3, "a_Position" }
			} );
		m_SquareVA->AddVertexBuffer( squareVB );

		uint32_t squareIndices[ 6 ] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Just::IndexBuffer> squareIB( Just::IndexBuffer::Create( squareIndices, sizeof( squareIndices ) / sizeof( uint32_t ) ) );
		m_SquareVA->SetIndexBuffer( squareIB );


		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4( a_Position, 1.0 );
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

		m_BlueShader = std::make_shared<Just::Shader>( blueShaderVertexSrc, blueShaderFragmentSrc );

	}

	virtual void OnUpdate( const Just::Timestep& ts ) override
	{
		// Input
		if( Just::Input::IsKeyPressed( JST_KEY_LEFT ) )
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if( Just::Input::IsKeyPressed( JST_KEY_RIGHT ) )
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if( Just::Input::IsKeyPressed( JST_KEY_UP ) )
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if( Just::Input::IsKeyPressed( JST_KEY_DOWN ) )
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if( Just::Input::IsKeyPressed( JST_KEY_A ) )
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if( Just::Input::IsKeyPressed( JST_KEY_D ) )
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		
		// Render
		Just::RenderCommand::SetClearColor( { 0.1f, 0.1f, 0.1f, 1.0f } );
		Just::RenderCommand::Clear();

		m_Camera.SetPosition( m_CameraPosition );
		m_Camera.SetRotation( m_CameraRotation );

		Just::Renderer::BeginScene( m_Camera );

		static glm::mat4 scale = glm::scale( glm::mat4( 1.0f ), glm::vec3( 0.1f ) );
		for( size_t i = 0; i < 5; ++i )
		{
			for( size_t j = 0; j < 5; ++j )
			{
				glm::vec3 pos( j * 0.11f, i * 0.11f, 0.0f );
				glm::mat4 transform = glm::translate( glm::mat4( 1.0f ), pos ) * scale;

				Just::Renderer::Submit( m_BlueShader, m_SquareVA, transform );
			}
		}

		Just::Renderer::Submit( m_Shader, m_VertexArray );
		
		Just::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

private:
	std::shared_ptr<Just::Shader> m_Shader;
	std::shared_ptr<Just::VertexArray> m_VertexArray;

	std::shared_ptr<Just::Shader> m_BlueShader;
	std::shared_ptr<Just::VertexArray> m_SquareVA;

	Just::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 45.0f;
};

class Sandbox : public Just::Application
{
public:
	Sandbox()
	{
		PushLayer( new ExampleLayer );
	}

	~Sandbox()
	{

	}

	void Run()
	{
	}
};

Just::Application* Just::CreateApplication()
{
	return new Sandbox();
}