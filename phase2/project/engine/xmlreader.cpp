#include "xmlreader.h"

string pathxml = "../ficheiros/";


vector<Ponto> modelReader(string f) {
	ifstream file(f);
    Ponto p;
    vector<Ponto> pontos;

	if (file.is_open()) {
		while (file.good()) {
			file >> p.x >> p.y >> p.z;
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

		int x_pos, y_pos, z_pos;
		int  x_la, y_la, z_la;
		int  x_up, y_up, z_up;
		int   fov, near, far;

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


void parseModels(XMLElement* models, Group* group) {
    XMLElement* model = models->FirstChildElement("model");
    for (; model != NULL; model = model->NextSiblingElement("model")) {
		string file3d = model->Attribute("file");
		vector<Ponto> pontos = modelReader(pathxml + file3d);
		group->addModel(new Model(pontos));
	}
}


void parseTransform(XMLElement* transform, Group* group) {
    XMLElement* t = transform->FirstChildElement();
    for (; t != NULL; t = t->NextSiblingElement()) {
        string type = t->Value();

		Transform* transform = new Transform();

        if (type.compare("translate") == 0) { 
            float x = t->FloatAttribute("x");
            float y = t->FloatAttribute("y");
            float z = t->FloatAttribute("z");

			transform->setTranslate(new Translate(x, y, z));
        }
	    else if (type.compare("rotate") == 0) {
            float angulo = t->FloatAttribute("angle");
            float      x = t->FloatAttribute("x");
            float      y = t->FloatAttribute("y");
            float      z = t->FloatAttribute("z");

			transform->setRotate(new Rotate(angulo, x, y, z));
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


void xmlReader(string f, Camera* camera, vector<Group>* groups) {
    XMLDocument doc;
	XMLNode* root;
	vector<Ponto> model;
	Group* group;
	
    if (!(doc.LoadFile(f.c_str()))) {
		root = doc.RootElement();
		
        XMLElement* elem = root->FirstChildElement("camera");
		parseCamera(elem, camera);
		
		for (elem = elem->NextSiblingElement("group"); elem != NULL; elem = elem->NextSiblingElement("group")) {
			group = new Group();
			parseGroup(elem, group);
			groups->push_back(*group);
		}
	}
	else cout << "ERROR loading xml" << endl;
}