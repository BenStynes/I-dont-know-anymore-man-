#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

	

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[8];
Vertex initialvertex[8];
GLubyte triangles[36];
Matrix3 matrix;

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	glMatrixMode(GL_PROJECTION);
	/* vertex counter-clockwise winding */
	glEnable(GL_CULL_FACE);

	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -8);
	vertex[0].coordinate[0] = -1.0f;
	vertex[0].coordinate[1] = -1.0f;
	vertex[0].coordinate[2] =  1.0f;

	vertex[1].coordinate[0] =  1.0f;
	vertex[1].coordinate[1] = -1.0f;
	vertex[1].coordinate[2] =  1.0f;

	vertex[2].coordinate[0] =  1.0f;
	vertex[2].coordinate[1] =  1.0f;
	vertex[2].coordinate[2] =  1.0f;

	vertex[3].coordinate[0] = -1.0f; 
	vertex[3].coordinate[1] =  1.0f;  
	vertex[3].coordinate[2] =  1.0f;

	vertex[4].coordinate[0] = -1.0f; 
	vertex[4].coordinate[1] = -1.0f;  
	vertex[4].coordinate[2] = -1.0f;

	vertex[5].coordinate[0] =  1.0f; 
	vertex[5].coordinate[1] = -1.0f;  
	vertex[5].coordinate[2] = -1.0f;

	vertex[6].coordinate[0] =  1.0f;
	vertex[6].coordinate[1] =  1.0f;
	vertex[6].coordinate[2] = -1.0f;

	vertex[7].coordinate[0] = -1.0f;
	vertex[7].coordinate[1] =  1.0f;
	vertex[7].coordinate[2] = -1.0f;

	vertex[7].color[0] = 0.1f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	vertex[6].color[0] = 0.2f;
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[5].color[0] = 0.3f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[4].color[0] = 0.4f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[3].color[0] = 0.5f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[2].color[0] = 0.6f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[1].color[0] = 0.5f;
	vertex[1].color[1] = 0.5f;
	vertex[1].color[2] = 0.0f;

	vertex[0].color[0] = 0.3f;
	vertex[0].color[1] = 0.4f;
	vertex[0].color[2] = 0.0f;

	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 2;   triangles[4] = 3;   triangles[5] = 0;
	triangles[6] = 4;   triangles[7] = 7;   triangles[8] = 6;
	triangles[9] = 6;   triangles[10] = 5;   triangles[11] = 4;
	triangles[12] = 3;   triangles[13] = 2;   triangles[14] = 6;
	triangles[15] = 6;   triangles[16] = 7;   triangles[17] = 3;
	triangles[18] = 4;   triangles[19] = 5;   triangles[20] = 1;
	triangles[21] = 1;   triangles[22] = 0;   triangles[23] = 4;
	triangles[24] = 1;   triangles[25] = 5;   triangles[26] = 6;
	triangles[27] = 6;   triangles[28] = 2;   triangles[29] = 1;
	triangles[30] = 0;   triangles[31] = 3;   triangles[32] = 7;
	triangles[33] = 7;   triangles[34] = 4;   triangles[35] = 0;
	
	for (int i = 0; i < 8; i++)
	{
		initialvertex[i] = vertex[i] ;
	}
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 0.01f)
	{
		clock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			rotation.setX(rotation.getX() + rotationAngle);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			rotation.setY(rotation.getY() + rotationAngle);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			rotation.setZ(rotation.getZ() + rotationAngle);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			translation.setY(translation.getY() - 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			translation.setY(translation.getY() + 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			translation.setX(translation.getX() - 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			translation.setX(translation.getX() + 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			scale += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			scale -= 10;
		}

		Matrix3 identity{ 1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f };

		identity = identity * matrix.Scale(scale, scale);

		identity = identity * matrix.RotationX(rotation.getX());
		identity = identity * matrix.RotationY(rotation.getY());
		identity = identity * matrix.RotationZ(rotation.getZ());

		for (int i = 0; i < 8; i++)
		{


			vector3 localvect{ initialvertex[i].coordinate[0],initialvertex[i].coordinate[1] ,initialvertex[i].coordinate[2] };
			vector3 answerVector = identity * localvect;
            vertex[i].coordinate[2] = answerVector.getZ();

			answerVector.setZ(1);
			vector3 secondAnswer = identity.Translate(translation.getX(), translation.getY()) * answerVector;
			vertex[i].coordinate[0] = secondAnswer.getX();
			vertex[i].coordinate[1] = secondAnswer.getY();

		}
	}
	//Change vertex data
	/*vertex[0].coordinate[0] += -0.0001f;
	vertex[0].coordinate[1] += -0.0001f;
	vertex[0].coordinate[2] += -0.0001f;*/

	
}

void Game::render()
{
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	

	glDeleteBuffers(1, vbo);
}

