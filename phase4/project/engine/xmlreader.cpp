#include "xmlreader.h"

string pathxml = "../ficheiros/";


vector<Ponto> modelReader(string f) {
	ifstream file(f);
    Ponto p;
    vector<Ponto> pontos;

	if (file.is_open()) {
		while (file.good()) {
			file >> p.x >> p.y >> p.z >> p.nx >> p.ny >> p.nz >> p.ti >> p.tj;
			if (file.eof())
                break;
			pontos.push_back(p);
		}
	}
	else cout << "ERROR opening file " << f << endl;

	file.close();
	return pontos;
}


void parseCamera(XMLElement* camera, Camera* c) {
	if (camera != NULL) {

		float x_pos, y_pos, z_pos;
		float  x_la, y_la, z_la;
		float  x_up, y_up, z_up;
		float   fov, near, far;

		XMLElement* settings = camera->FirstChildElement("position");
		if (settings != NULL) {
            x_pos = settings->FloatAttribute("x");
            y_pos = settings->FloatAttribute("y");
            z_pos = settings->FloatAttribute("z");
		}

		settings = settings->NextSiblingElement("lookAt");
		if (settings != NULL) {
			x_la = settings->FloatAttribute("x");
            y_la = settings->FloatAttribute("y");
            z_la = settings->FloatAttribute("z");
		}

		settings = settings->NextSiblingElement("up");
		if (settings != NULL) {
			x_up = settings->FloatAttribute("x");
            y_up = settings->FloatAttribute("y");
            z_up = settings->FloatAttribute("z");
		}

		settings = settings->NextSiblingElement("projection");
		if (settings != NULL) {
			fov  = settings->FloatAttribute("fov");
            near = settings->FloatAttribute("near");
            far  = settings->FloatAttribute("far");
		}

		c->setValues(x_pos, y_pos, z_pos, x_la, y_la, z_la, x_up, y_up, z_up, fov, near, far);
	}
	else cout << "ERROR parsing camera" << endl;
}


void parseLights(XMLElement* lights, vector<Light*>* l) {
	Light* aux;
	string type;
	
	GLenum i = 0;
	for (XMLElement* light = lights->FirstChildElement("light"); light != NULL; light = light->NextSiblingElement("light"), i++) {
		
		type = light->Attribute("type");
		
		if (type == "point") {
			float* pos = (float*)malloc(sizeof(float) * 4);
			pos[0] = light->FloatAttribute("posx");
			pos[1] = light->FloatAttribute("posy");
			pos[2] = light->FloatAttribute("posz");
			pos[3] = 1.0f; // 1.0 indica que se trata de um ponto de luz
			aux = new PointLight(i,pos,0.0f);
			l->push_back(aux);
		}
		else if (type == "directional") {
			float* dir = (float*)malloc(sizeof(float) * 4);
			dir[0] = light->FloatAttribute("dirx");
			dir[1] = light->FloatAttribute("diry");
			dir[2] = light->FloatAttribute("dirz");
			dir[3] = 0.0f; // 0.0 indica que a luz é direcional
			aux = new DirectionalLight(i,dir);
			l->push_back(aux);
		}
		else if (type == "spot") {
			float* pos = (float*)malloc(sizeof(float) * 4);
			pos[0] = light->FloatAttribute("posx");
			pos[1] = light->FloatAttribute("posy");
			pos[2] = light->FloatAttribute("posz");
			pos[3] = 1.0f; // ponto = 1
			float* dir = (float*)malloc(sizeof(float) * 3);
			dir[0] = light->FloatAttribute("dirx");
			dir[1] = light->FloatAttribute("diry");
			dir[2] = light->FloatAttribute("dirz");
			float cutoff = light->FloatAttribute("cutoff");
			float exponent = 0.0f;
			aux = new SpotLight(i,pos,dir,cutoff,exponent);
			l->push_back(aux);
		}
		else cout << "ERROR parsing lights " << type << endl;
	}
}


void parseModels(XMLElement* models, Group* group) {
    XMLElement* model = models->FirstChildElement("model");
    for (; model != NULL; model = model->NextSiblingElement("model")) {
		string file3d = model->Attribute("file");
		vector<Ponto> pontos = modelReader(pathxml + file3d);

		XMLElement* text = model->FirstChildElement("texture");
		string textura;
		if (text) textura = text->Attribute("file");
		
		// colors

		float* diffuse = (float*)malloc(sizeof(float) * 4);
		float* ambient = (float*)malloc(sizeof(float) * 4);
		float* specular = (float*)malloc(sizeof(float) * 4);
		float* emissive = (float*)malloc(sizeof(float) * 4);
		float shininess;

		XMLElement* color = model->FirstChildElement("color");
		
		if (!color) {
			diffuse[0]  = 0.8f; diffuse[1]  = 0.8f; diffuse[2]  = 0.8f;
			ambient[0]  = 0.2f; ambient[1]  = 0.2f; ambient[2]  = 0.2f;
			specular[0] = 0.0f; specular[1] = 0.0f; specular[2] = 0.0f;
			emissive[0] = 0.0f; emissive[1] = 0.0f; emissive[2] = 0.0f;
			shininess = 0.0f;
		}
		else {
			color = color->FirstChildElement("diffuse");
			diffuse[0] = color->FloatAttribute("R") / 255.0f;
			diffuse[1] = color->FloatAttribute("G") / 255.0f;
			diffuse[2] = color->FloatAttribute("B") / 255.0f;
			color = color->NextSiblingElement("ambient");
			ambient[0] = color->FloatAttribute("R") / 255.0f;
			ambient[1] = color->FloatAttribute("G") / 255.0f;
			ambient[2] = color->FloatAttribute("B") / 255.0f;
			color = color->NextSiblingElement("specular");
			specular[0] = color->FloatAttribute("R") / 255.0f;
			specular[1] = color->FloatAttribute("G") / 255.0f;
			specular[2] = color->FloatAttribute("B") / 255.0f;
			color = color->NextSiblingElement("emissive");
			emissive[0] = color->FloatAttribute("R") / 255.0f;
			emissive[1] = color->FloatAttribute("G") / 255.0f;
			emissive[2] = color->FloatAttribute("B") / 255.0f;
			color = color->NextSiblingElement("shininess");
			shininess = color->FloatAttribute("value");
		}

		diffuse[3]  = 1.0f;
		ambient[3]  = 1.0f;
		specular[3] = 1.0f;
		emissive[3] = 1.0f;
		

		if (textura != "")
			group->addModel(new Model(pontos, diffuse, ambient, specular, emissive, shininess, textura));
		else
			group->addModel(new Model(pontos, diffuse, ambient, specular, emissive, shininess));
	}
}


void parseTranslate(XMLElement* t, Transform* transform) {
	string value = t->FirstAttribute()->Name();

	if (value.compare("time") == 0) {
		float time = t->FloatAttribute("time");
		bool align = t->BoolAttribute("align");

		vector<Ponto> cp;

		t = t->FirstChildElement("point");
		for (; t != NULL; t = t->NextSiblingElement("point")) {
			Ponto p;
			p.x = t->FloatAttribute("x");
			p.y = t->FloatAttribute("y");
			p.z = t->FloatAttribute("z");
			cp.push_back(p);
		}
		transform->setTranslate(new Translate(cp, time, align));
	}
	else {
		float x = t->FloatAttribute("x");
		float y = t->FloatAttribute("y");
		float z = t->FloatAttribute("z");

		transform->setTranslate(new Translate(x, y, z));
	}
}


void parseRotate(XMLElement* t, Transform* transform) {
	string value = t->FirstAttribute()->Name();
	float angulo;
	bool rotate;

	if (value.compare("angle") == 0) {
		angulo = t->FloatAttribute("angle");
		rotate = false;
	}
	else {
		angulo = t->FloatAttribute("time");
		rotate = true;
	}
	
	float x = t->FloatAttribute("x");
	float y = t->FloatAttribute("y");
	float z = t->FloatAttribute("z");

	transform->setRotate(new Rotate(rotate, angulo, x, y, z));
}


void parseTransform(XMLElement* transform, Group* group) {
    XMLElement* t = transform->FirstChildElement();
    for (; t != NULL; t = t->NextSiblingElement()) {
        string type = t->Value();

		Transform* transform = new Transform();

        if (type.compare("translate") == 0) {
			parseTranslate(t,transform);
        }
	    else if (type.compare("rotate") == 0) {
			parseRotate(t, transform);
	    }
	    else if (type.compare("scale") == 0) {
            float x = t->FloatAttribute("x");
            float y = t->FloatAttribute("y");
            float z = t->FloatAttribute("z");

			transform->setScale(new Scale(x, y, z));
	    }
		else cout << "ERROR parsing transform " << type << endl;

		group->addTransform(transform);
	}
}


void parseGroup(XMLElement* group, Group* grupo) {
	XMLElement* elem = group->FirstChildElement();
    for (; elem; elem = elem->NextSiblingElement()) {
		
        string type = elem->Value();
		
        if (type.compare("transform") == 0) {
			parseTransform(elem, grupo);
        }
		else if (type.compare("models") == 0) {
			parseModels(elem, grupo);
		}
		else if (type.compare("group") == 0) {
			Group* subgroup = new Group();
			grupo->addSubGroup(subgroup);
			parseGroup(elem, subgroup);
		}
		else cout << "ERROR parsing group " << type << endl;
	}
}


void xmlReader(string f, Camera* camera, vector<Light*>* lights, vector<Group>* groups) {
    XMLDocument doc;
	XMLNode* root;
	vector<Ponto> model;
	Group* group;

    if (!(doc.LoadFile(f.c_str()))) {
		root = doc.RootElement();
		
        XMLElement* elem = root->FirstChildElement("camera");
		parseCamera(elem, camera);

		if (elem->NextSiblingElement("lights")) {
			elem = elem->NextSiblingElement("lights");
			parseLights(elem, lights);
		}
		
		for (elem = elem->NextSiblingElement("group"); elem != NULL; elem = elem->NextSiblingElement("group")) {
			group = new Group();
			parseGroup(elem, group);
			groups->push_back(*group);
		}
	}
	else cout << "ERROR loading xml" << endl;
}