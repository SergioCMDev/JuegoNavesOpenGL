//#include "Render.h"
//
//
//
//vec3 posLuz;
//const float M_PI = 3.14f;
//const vec3 posSuelo = vec3(0.0f, -16.0f, 0.0f);
//const float screen_width = 1280, screen_height = 720;
//const float shadow_width = 1024, shadow_height = 1024;
//
//Player* GetPlayerReference(GameObject* objectPlayer) {
//	GameObject *g = objectPlayer;
//	Player* player = static_cast<Player*>(objectPlayer);
//	return player;
//}
//
//
//#pragma endregion
//struct Sphere {
//	float* vertices;
//	float* normals;
//	float* textCoords;
//	uint32_t* elementos;
//	uint32_t numeroVertices;
//	uint32_t numeroElementos;
//	uint32_t numeroNormales;
//	uint32_t numeroTexturas;
//	uint32_t* VAO;
//	Shader *shader;
//	uint32_t numeroIndices = 121 * 8;
//	vec3 scale = glm::vec3(0.4f);
//	vec3 color = vec3(1.0f);
//	vec3 position = posLuz;
//
//};
//
//
//
//#pragma region Generacion esfera
//
//void generateVerts(float * verts, float * norms, float * tex, unsigned int * el, const uint32_t slices, const uint32_t stacks, const uint32_t radius) {
//	float theta, phi;       // Generate positions and normals
//	float thetaFac = (float)((2.0 * M_PI) / slices);
//	float phiFac = (float)(M_PI / stacks);
//	float nx, ny, nz, s, t;
//	uint32_t idx = 0, tIdx = 0;
//	for (uint8_t i = 0; i <= slices; i++) {
//		theta = i * thetaFac;
//		s = (float)i / slices;
//		for (uint8_t j = 0; j <= stacks; j++) {
//			phi = j * phiFac;
//			t = (float)j / stacks;
//			nx = sinf(phi) * cosf(theta);
//			ny = sinf(phi) * sinf(theta);
//			nz = cosf(phi);
//			verts[idx] = radius * nx;
//			verts[idx + 1] = radius * ny;
//			verts[idx + 2] = radius * nz;
//			norms[idx] = nx;
//			norms[idx + 1] = ny;
//			norms[idx + 2] = nz;
//			idx += 3;
//
//			tex[tIdx] = s;
//			tex[tIdx + 1] = t;
//			tIdx += 2;
//		}
//	}
//
//	idx = 0;                      // Generate the element list
//	for (uint8_t i = 0; i < slices; i++) {
//		uint32_t stackStart = i * (stacks + 1);
//		uint32_t nextStackStart = (i + 1) * (stacks + 1);
//		for (uint8_t j = 0; j < stacks; j++) {
//			if (j == 0) {
//				el[idx] = stackStart;
//				el[idx + 1] = stackStart + 1;
//				el[idx + 2] = nextStackStart + 1;
//				idx += 3;
//			}
//			else if (j == stacks - 1) {
//				el[idx] = stackStart + j;
//				el[idx + 1] = stackStart + j + 1;
//				el[idx + 2] = nextStackStart + j;
//				idx += 3;
//			}
//			else {
//				el[idx] = stackStart + j;
//				el[idx + 1] = stackStart + j + 1;
//				el[idx + 2] = nextStackStart + j + 1;
//				el[idx + 3] = nextStackStart + j;
//				el[idx + 4] = stackStart + j;
//				el[idx + 5] = nextStackStart + j + 1;
//				idx += 6;
//			}
//		}
//	}
//}
//
//uint32_t createSphere(const float radius) {
//	constexpr int slices = 10;
//	constexpr int stacks = 10;
//
//	Sphere sphere;
//
//	constexpr uint32_t nVerts = (slices + 1) * (stacks + 1); //121
//	constexpr uint32_t elements = (slices * 2 * (stacks - 1)) * 3; //540
//
//	float v[3 * nVerts];        // Verts      363 elementos
//	float n[3 * nVerts];        // Normals    363 elementos
//	float tex[2 * nVerts];      // Tex coords    242 elementos
//	uint32_t el[elements];      // Elements
//
//	generateVerts(v, n, tex, el, slices, stacks, radius);
//	sphere.vertices = v;
//	sphere.textCoords = tex;
//	sphere.elementos = el;
//	sphere.normals = n;
//	sphere.numeroVertices = nVerts * 3;
//	sphere.numeroNormales = nVerts * 3;
//	sphere.numeroTexturas = 2 * nVerts;
//	sphere.numeroElementos = elements;
//
//	const int sizeTotal = (sphere.numeroVertices + sphere.numeroNormales + sphere.numeroTexturas);
//
//	//vector<float> newVertice2(sizeTotal);
//	float newVertice2[3 * nVerts + 3 * nVerts + 2 * nVerts];
//
//	for (size_t i = 0; i < sphere.numeroVertices / 3; i++)
//	{
//		newVertice2[0 + 8 * i] = sphere.vertices[3 * i];
//		newVertice2[1 + 8 * i] = sphere.vertices[3 * i + 1];
//		newVertice2[2 + 8 * i] = sphere.vertices[3 * i + 2];
//
//		newVertice2[3 + 8 * i] = sphere.normals[3 * i];
//		newVertice2[4 + 8 * i] = sphere.normals[3 * i + 1];
//		newVertice2[5 + 8 * i] = sphere.normals[3 * i + 2];
//
//		newVertice2[6 + 8 * i] = sphere.textCoords[2 * i];
//		newVertice2[7 + 8 * i] = sphere.textCoords[2 * i + 1];
//	}
//
//	uint32_t VAO, VBO, EBO;
//
//	glGenVertexArrays(1, &VAO);
//	//Generamos 2 buffer, elementos y objetos
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	//Bindeamos el VAO
//	glBindVertexArray(VAO);
//
//	//Bindeamos buffer vertices
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//Subida de vertices al buffer
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(newVertice2), &newVertice2, GL_STATIC_DRAW);
//
//
//	//Bindeo buffer indices
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(el), el, GL_STATIC_DRAW);
//
//	//Vertices de posicion
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	////Vertices de normales
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(3 * (sizeof(float))));
//	glEnableVertexAttribArray(1);
//
//	//Vertices de textura
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(6 * (sizeof(float))));
//	glEnableVertexAttribArray(2);
//
//
//	//desbindeamos buffer objetos
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//Desbindeo
//	glBindVertexArray(0);
//
//	//desbindeamos buffer elements
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	sphere.VAO = &VAO;
//	return VAO;
//
//	//return sphere;
//
//}
//#pragma endregion
//
//#pragma region Render Figures
//
//void RenderFigureMain(const Shader & shader, glm::mat4 &projection, glm::mat4 &view, glm::mat4 &model, const uint32_t &VAO, const uint32_t &numeroElementos)
//{
//	shader.Set("projection", projection);
//	shader.Set("view", view);
//	shader.Set("model", model);
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, numeroElementos, GL_UNSIGNED_INT, 0);
//}
//
//
//
//void RenderSphere(Sphere &sphere, glm::mat4 &projection, glm::mat4 &view)
//{
//	glm::mat4 model = glm::mat4(1.0f);
//	sphere.shader->Use();
//	sphere.shader->Set("color", sphere.color);
//
//	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//
//	//float l_pos[] = { sin((float)glfwGetTime() / 2.0f), 0.0f, abs(cos((float)glfwGetTime() / 2.0f)) };
//	//vec3 lightPos = vec3(l_pos[0], l_pos[1], l_pos[0]);
//
//	////model = glm::translate(model, sphere.position + lightPos);
//	model = glm::translate(model, sphere.position);
//	model = glm::scale(model, sphere.scale);
//
//	RenderFigureMain(*sphere.shader, projection, view, model, *sphere.VAO, sphere.numeroIndices);
//
//}
//#pragma endregion
//
//void Render::RenderScene(Quad quadSuelo, Sphere sphere, Cube cube) {
//
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//
//	glm::mat4 view = _camera->GetViewMatrix();
//	glm::mat4 projection = glm::perspective(glm::radians(_camera->GetFOV()), screen_width / screen_height, 0.1f, 60.0f);
//
//	quadSuelo.Render(projection, view, posSuelo);
//	//Dibujamos Suelo
//	if (_debug) {
//
//		//Dibujamos sphera luz
//		RenderSphere(sphere, projection, view);
//
//		//Dibujamos Cubos Meteoritos
//		cube._color = vec3(1.0f);
//		cube._scale = vec3(1.0f);
//		for (size_t i = 0; i < Meteor::GetNumberPositions(); i++)
//		{
//			cube.Render(projection, view, Meteor::GetMeteorPosition(i), 1.0f);
//		}
//
//		//dibujamos cubos naves
//		cube._color = vec3(1.0f, 0.0f, 0.0f);
//		for (size_t i = 0; i < Enemy::GetNumberPositions(); i++)
//		{
//			cube._shader->Set("color", cube._color);
//			cube.Render(projection, view, Enemy::GetEnemyPosition(i), 1.0f);
//
//		}
//
//		//dibujamos cubos limites
//		cube._color = vec3(1.0f, 1.0f, 0.0f);
//		cube._shader->Set("color", cube._color);
//		cube.Render(projection, view, vec3(Constants::MAX_POSITION_X, 0.0f, 0.0f), 1.0f);
//
//		cube.Render(projection, view, vec3(Constants::MIN_POSITION_X, 0.0f, 0.0f), 1.0f);
//
//		cube.Render(projection, view, vec3(0.0f, 0.0f, Constants::MIN_POSITION_Y), 1.0f);
//
//		cube.Render(projection, view, vec3(0.0f, 0.0f, Constants::MAX_POSITION_Y), 1.0f);
//
//	}
//
//	glBindVertexArray(0);
//}
//
//
//
//Render::Render(Node * node, bool debug) {
//
//	_node = node;
//	_debug = debug;
//	GameObject *g = node->GetGameObject();;
//	Camera* camera = static_cast<Camera*>(g);
//	_camera = camera;
//	//Shader shaderQuad = Utils::GetFullShader("Shaders/QuadVS.vs", "Shaders/QuadFS.fs");
//	//Shader shaderSphere = Utils::GetFullShader("Shaders/LightVS.vs", "Shaders/LightFS.fs");
//	//cout << "Creacion Geometrias " << endl;
//	//Quad quadSuelo = Quad(shaderQuad);
//	//_sphere = Sphere();
//	//uint32_t textureSuelo = Model::GetTexture("Textures/texture3.png", true);
//	//uint32_t SphereVAO = createSphere(1);
//
//	//_sphere.shader = &shaderSphere;
//
//	//quadSuelo.textures[0] = textureSuelo;
//
//	//_sphere.VAO = &SphereVAO;
//}
//
//void Render::RenderGame(Shader & shaderModels, Shader & depthShader)
//{
//}
//
//
//void ColliderPlayer(Player * player, Cube *cube)
//{
//	//vec3 position = player->GetPosition();
//	//glm::mat4 view = _camera->GetViewMatrix();
//	//glm::mat4 projection = glm::perspective(glm::radians(camera.GetFOV()), screen_width / screen_height, 0.1f, 60.0f);
//	//cube->_scale = vec3(3.0f, 4.0f, 5.5f);
//	//cube->_color = vec3(1.0f);
//	//cube->_position = position;
//
//	//player->_collider = cube;
//	//cube->Render(projection, view, position, 0.0f);
//}
//
//void RenderColliders(Node * node, Cube *cube) {
//	Player* player = GetPlayerReference(node->GetChildren(0)->GetGameObject());
//	ColliderPlayer(player, cube);
//
//}
