#pragma once
#ifndef S2D_SERIALIZER_HEADER
#define S2D_SERIALIZER_HEADER
#include <S2Dinternal.h>

class LevelSerializer
{
#define cstr const char*
public:
	cstr FILE_BEGIN = "FILE:\n";
	cstr FILE_END = "\nEND";

	cstr SCOPE_BEGIN = "\n{";
	cstr SCOPE_END = "\n}";

	cstr ARR_BEGIN = "[";
	cstr ARR_END = "]";

	cstr ATTR_BEGIN = "(";
	cstr ATTR_END = ")";

	cstr OBJECT_SCOPE = "\nOBJ";

	cstr ind = "\t";

	std::string name = "level";
	std::ofstream file;
	std::string path;
	std::string filename;
	std::string ext = ".s2";


	std::string int2str(int s)
	{
		std::stringstream ss;
		ss << s;
		return ss.str();
	}

	std::string bool2str(bool s, int mode = 0)
	{
		if (mode == 0)
		{
			if (s)
			{
				std::stringstream ss;
				ss << "true";
				return ss.str();
			}
			else
			{
				std::stringstream ss;
				ss << "false";
				return ss.str();
			}
		}
		else
		{
			if (s)
			{
				std::stringstream ss;
				ss << 1;
				return ss.str();
			}
			else
			{
				std::stringstream ss;
				ss << 0;
				return ss.str();
			}
		}

		return std::string("");
	}

	std::string float2str(float s)
	{
		std::stringstream ss;
		ss << s;
		return ss.str();
	}

	std::string vec2str(Vector2 s)
	{
		std::stringstream ss;
		ss << "(";
		ss << s.x;
		ss << ", ";
		ss << s.y;
		ss << ")";
		return ss.str();
	}



	void SerializeLevel()
	{
#define indent result.append(ind)
		using namespace std;

		fstream str;
		string result = "";

		path = GetWorkingDirectory();
		filename = path + name + ext;
		this->file = ofstream(filename.c_str());

		result.append(FILE_BEGIN);

		GameObject::GameObjectInstance* obj = nullptr;
		for (size_t i = 0; i < GameObject::ActiveObjects.size(); i++)
		{
			obj = GameObject::ActiveObjects[i];
			result.append(OBJECT_SCOPE);
			result.append(SCOPE_BEGIN);
			
			//result.append("\nname: " + obj->obj->name);
			if (obj != nullptr)
			{
				indent; result.append("\n\tid: ");
				result.append(int2str(obj->id));
				if (obj->obj->sprite.path.length() < 1)
				{
					indent; result.append("\n\tspritepath: none");
				}
				if (obj->obj->sprite.path.length() > 1)
				{
					indent; result.append("\n\tspritepath: " + obj->obj->sprite.path);
				}

				indent; result.append("\n\tname: ");
				result.append(obj->obj->name);

				indent; result.append("\n\tposition: ");
				result.append(vec2str(obj->obj->position));

				indent; result.append("\n\tdelta_position: ");
				result.append(vec2str(obj->obj->position));

				indent; result.append("\n\tscale: ");
				result.append(vec2str(obj->obj->scale));

				indent; result.append("\n\trotation: ");
				result.append(float2str(obj->obj->rotation));

				indent; result.append("\n\tactive: ");
				result.append(bool2str(obj->obj->active, 0));


			}

			result.append(SCOPE_END);
			result.append("\n");
		}

		result.append(FILE_END);
		file << result.c_str();
		file.close();

		s2dlog(string("Wrote ") + int2str(sizeof(result)) + string(" bytes to ") + filename);
#undef ind
	}

#undef cstr
};


#endif