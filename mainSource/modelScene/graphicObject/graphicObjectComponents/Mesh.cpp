#include "Mesh.h"
#include "fstream"
#include <sstream>
#include <map>
#include <cstddef>
// Структура, описывающая одну вершину полигональной сетки
// каждая вершина имеет геометрические координаты,
// вектор нормали и текстурные координаты


Mesh::Mesh()
{

}

Mesh::Mesh(string filename)
{
	load(filename);

}

void Mesh::load(string filename)
{	
	// вектор для хранения геометрических координат
	vector<vec3> vect;
	// вектор для хранения нормалей
	vector<vec3> normal;
	// вектор для хранения текстурных координат
	vector<vec2> texture;
	// вектор для хранения индексов атрибутов, для построения вершин
	vector<ivec3> fPoints;
	// словарь для проверки 
	map<string, int> vertexToIndexTable;
	// массив вершин полигональной сетки
	vector<Vertex> vertices;
	// массив индексов
	vector<GLuint> indices;
	int index = 0;
	

	fstream f(filename);
	if (!f.is_open()) {
		cout << "Ошибка открытия .obj файла\n";
	}
	string lineStr;
	while (getline(f, lineStr)) {
		//проверка на пустую строку
		if (lineStr.empty() || lineStr[0] == '#') continue;
		//разбиваем на отдельные слова
		//используем специальный класс для работы со строками
		istringstream str(lineStr);
		//тип данных (v, vn, vt)
		string type;
		str >> type;
		if (type == "v") {
			vec3 temp;
			str >> temp.x >> temp.y >> temp.z;
			vect.push_back(temp);
		}
		if (type == "vn") {
			vec3 temp;
			str >> temp.x >> temp.y >> temp.z;
			normal.push_back(temp);
		}
		if (type == "vt") {
			vec3 temp;
			str >> temp.x >> temp.y >> temp.z;
			texture.push_back(temp);
		}
		if (type == "f") {
			ivec3 temp;
			string strin;
			for (int i = 0; i < 3; i++) {
				str >> strin;
				//проверяем на нахождение в словаре
				auto it = vertexToIndexTable.find(strin);
				if (it == vertexToIndexTable.end()) {
					vertexToIndexTable[strin] = index;
					indices.push_back(index);
					//записываем в fPoints
					replace(strin.begin(), strin.end(), '/', ' ');
					istringstream tempStr(strin);
					tempStr >> temp.x >> temp.y >> temp.z;
					fPoints.push_back(temp);

					index++;
				}
				else { 
					int pastIndex = (*it).second;
					indices.push_back(pastIndex);
				}
			}
		}
	}
	//testOutPut(fPoints);
	//создаем вершины 
	int vectorLen = fPoints.size();
	for (int i = 0; i < vectorLen; i++) {
		Vertex tempVertex;
		int indexVert = fPoints[i][0] - 1;
		int indexNormal = fPoints[i][2] - 1;
		int indexTexture = fPoints[i][1] - 1;
		//cout << "Выводим позицию индекса " << indexVert<< " " << indexNormal  << " " << indexTexture << endl;
		// записываем в вершины данные по позициям
		for (int j = 0; j < 3; j++) {
			tempVertex.coord[j] = vect[indexVert][j];
			tempVertex.normal[j] = normal[indexNormal][j];
		}
		for (int j = 0; j < 2; j++) {
			tempVertex.texCoord[j] = texture[indexTexture][j];
		}
		vertices.push_back(tempVertex);
	}

	glGenBuffers(1, &bufferIds[0]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &bufferIds[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()* sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	indexCount = indices.size();
}

void Mesh::draw()
{	
	//Загружаем занчение всех вершин 
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, coord));

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}