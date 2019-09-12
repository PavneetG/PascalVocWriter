#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "boost\foreach.hpp"
#include "boost\property_tree\json_parser.hpp"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>

using namespace std; 

//Name: Pavneet Gill 
//Date : 2019-05-23
//Description: This is a file type converter for certain types of labeled data formats. It converts given data to XML Pascal VOC
//Supports ImageNet,Dota and Supervisely 
//Methods:
//void ImageNet (string pathToSave, string location) // converts Imagenet labeled data (txt)
//pathToSave - is where you want to save the converted file  - C:/Users/pavne/Desktop/img_ImageNet.xml
//location - is where the file that you are trying to convert is placed 
//void DotaConversion (string pathToSave, string location) // converts Dota Labeled Data (txt)
//void superviselyConversion (string pathToSave, string location) //converts supervisely labeled format (json)

void ImageNet (string pathToSave, string location)
{
    //Creating Tree
	boost::property_tree::ptree pt1;
	boost::property_tree::read_xml(location, pt1);
	vector<int> vect;
	vector<string> name; 
	vector<string> cordinates; 
	string label;

		// Traverse property tree example
		BOOST_FOREACH(boost::property_tree::ptree::value_type const& p, pt1.get_child("annotation"))
		{
			if (p.first == "object")
			{
				boost::property_tree::ptree p1 = p.second;

				BOOST_FOREACH(boost::property_tree::ptree::value_type const& node, p1.get_child(""))
				{
					cout << node.first << endl;

					if (node.first == "name")
					{
						//cout << node.second.get_value<string>();
						name.push_back(node.second.get_value<string>());
					}

					boost::property_tree::ptree subtree = node.second;

					BOOST_FOREACH(boost::property_tree::ptree::value_type const& v, subtree.get_child(""))
					{
						std::string label = v.first;

						if (label != "<xmlattr>")
						{
							std::string value = subtree.get<std::string>(label);
							cordinates.push_back(value); 
						}
					}
				}
			}
		}

		

		int width = 0;
		int hieght = 0;

		cout << "working" << endl; 

		hieght = pt1.get_child("annotation").get_child("size").get<int>("height");
		width = pt1.get_child("annotation").get_child("size").get<int>("width");

		int current_frame_number = 0;

		boost::property_tree::ptree tree; //highest node
		boost::property_tree::ptree children_of_tree; //2nd order node

		boost::property_tree::ptree child_folder;
		boost::property_tree::ptree child_filename;

		boost::property_tree::ptree children_of_source;
		boost::property_tree::ptree child_source_database;

		boost::property_tree::ptree child_width;
		boost::property_tree::ptree child_height;
		boost::property_tree::ptree child_depth;
		boost::property_tree::ptree children_of_size;

		boost::property_tree::ptree child_segmented;

		boost::property_tree::ptree child_name;
		boost::property_tree::ptree child_temporal_attribute;
		boost::property_tree::ptree child_truncated;
		boost::property_tree::ptree child_occluded;
		boost::property_tree::ptree children_of_bndbox;
		boost::property_tree::ptree child_xmin;
		boost::property_tree::ptree child_ymin;
		boost::property_tree::ptree child_xmax;
		boost::property_tree::ptree child_ymax;
		boost::property_tree::ptree child_difficult;
		boost::property_tree::ptree children_of_object;

		boost::property_tree::ptree vect1;
		boost::property_tree::ptree vect2;
		boost::property_tree::ptree vect3;
		boost::property_tree::ptree vect4;

		boost::property_tree::ptree x1;
		boost::property_tree::ptree y1;
		boost::property_tree::ptree x2;
		boost::property_tree::ptree y2;
		boost::property_tree::ptree x3;
		boost::property_tree::ptree y3;
		boost::property_tree::ptree x4;
		boost::property_tree::ptree y4;

		
		child_folder.put("", "C:/Users/pavne/Desktop");
		child_filename.put("", "supervisely.jpg");

		child_source_database.put("", "http://127.0.0.1:8081");
		children_of_source.push_back(std::make_pair("database", child_source_database));

		child_width.put("", width);
		child_height.put("", hieght);
		child_depth.put("", "3");

		children_of_size.push_back(std::make_pair("width", child_width));
		children_of_size.push_back(std::make_pair("height", child_height));
		children_of_size.push_back(std::make_pair("depth", child_depth));

		child_segmented.put("", 0);


		children_of_tree.push_back(std::make_pair("folder", child_folder));
		children_of_tree.push_back(std::make_pair("filename", child_filename));
		children_of_tree.push_back(std::make_pair("source", children_of_source));
		children_of_tree.push_back(std::make_pair("size", children_of_size));
		children_of_tree.push_back(std::make_pair("segmented", child_segmented));

		int count = 0; 
		int xMinIndex = 0; 
		int yMinIndex = 1;
		int xMaxIndex = 2; 
		int yMaxIndex = 3; 

		for (string x : name)
		{
			count++; 


			child_name.put("", x);

			child_temporal_attribute.put("", "n/a");
			child_truncated.put("", 0);
			child_occluded.put("", 0); 

			x1.put("", cordinates[xMinIndex]);
			y1.put("", cordinates[yMaxIndex]);
			x2.put("", cordinates[xMaxIndex]);
			y2.put("", cordinates[yMaxIndex]);
			x3.put("", cordinates[xMaxIndex]);
			y3.put("", cordinates[yMinIndex]);
			x4.put("", cordinates[xMinIndex]);
			y4.put("", cordinates[yMinIndex]);
			xMinIndex += 4; 
			yMinIndex += 4; 
			xMaxIndex += 4;
			yMaxIndex += 3;


			child_difficult.put("", "0");

			vect1.push_back(std::make_pair("X", x1));
			vect1.push_back(std::make_pair("Y", y1));
			vect2.push_back(std::make_pair("X", x2));
			vect2.push_back(std::make_pair("Y", y2));
			vect3.push_back(std::make_pair("X", x3));
			vect3.push_back(std::make_pair("Y", y3));
			vect4.push_back(std::make_pair("X", x4));
			vect4.push_back(std::make_pair("Y", y4));

			children_of_bndbox.push_back(std::make_pair("vertice1", vect1));
			children_of_bndbox.push_back(std::make_pair("vertice2", vect2));
			children_of_bndbox.push_back(std::make_pair("vertice3", vect3));
			children_of_bndbox.push_back(std::make_pair("vertice4", vect4));

			children_of_object.push_back(std::make_pair("name", child_name));
			children_of_object.push_back(std::make_pair("temporal", child_temporal_attribute));
			children_of_object.push_back(std::make_pair("truncated", child_truncated));
			children_of_object.push_back(std::make_pair("occluded", child_occluded));
			children_of_object.push_back(std::make_pair("bndbox", children_of_bndbox));
			children_of_object.push_back(std::make_pair("difficult", child_difficult));

			children_of_tree.push_back(std::make_pair("object", children_of_object));

			children_of_bndbox.clear();
			children_of_object.clear();

			vect1.clear();
			vect2.clear();
			vect3.clear();
			vect4.clear();

		}

		tree.add_child("annotation", children_of_tree);
		boost::property_tree::write_xml(pathToSave.c_str(), tree, std::locale(), boost::property_tree::xml_writer_make_settings< std::string >('\t', 1));
}

void DotaConversion (string pathToSave, string location)
{
		int current_frame_number = 0;

		boost::property_tree::ptree tree; //highest node
		boost::property_tree::ptree children_of_tree; //2nd order node

		boost::property_tree::ptree child_folder;
		boost::property_tree::ptree child_filename;

		boost::property_tree::ptree children_of_source;
		boost::property_tree::ptree child_source_database;

		boost::property_tree::ptree child_width;
		boost::property_tree::ptree child_height;
		boost::property_tree::ptree child_depth;
		boost::property_tree::ptree children_of_size;

		boost::property_tree::ptree child_segmented;

		boost::property_tree::ptree child_name;
		boost::property_tree::ptree child_temporal_attribute;
		boost::property_tree::ptree child_truncated;
		boost::property_tree::ptree child_occluded;
		boost::property_tree::ptree children_of_bndbox;
		boost::property_tree::ptree child_xmin;
		boost::property_tree::ptree child_ymin;
		boost::property_tree::ptree child_xmax;
		boost::property_tree::ptree child_ymax;
		boost::property_tree::ptree child_difficult;
		boost::property_tree::ptree children_of_object;

		boost::property_tree::ptree vect1;
		boost::property_tree::ptree vect2;
		boost::property_tree::ptree vect3;
		boost::property_tree::ptree vect4;

		boost::property_tree::ptree x1;
		boost::property_tree::ptree y1;
		boost::property_tree::ptree x2;
		boost::property_tree::ptree y2;
		boost::property_tree::ptree x3;
		boost::property_tree::ptree y3;
		boost::property_tree::ptree x4;
		boost::property_tree::ptree y4;

		child_folder.put("", "C:/Users/pavne/Desktop");
		child_filename.put("", "supervisely.jpg");

		child_source_database.put("", "http://127.0.0.1:8081");
		children_of_source.push_back(std::make_pair("database", child_source_database));

		child_width.put("", "");
		child_height.put("", "");
		child_depth.put("", "3");

		children_of_size.push_back(std::make_pair("width", child_width));
		children_of_size.push_back(std::make_pair("height", child_height));
		children_of_size.push_back(std::make_pair("depth", child_depth));

		child_segmented.put("", 0);


		children_of_tree.push_back(std::make_pair("folder", child_folder));
		children_of_tree.push_back(std::make_pair("filename", child_filename));
		children_of_tree.push_back(std::make_pair("source", children_of_source));
		children_of_tree.push_back(std::make_pair("size", children_of_size));
		children_of_tree.push_back(std::make_pair("segmented", child_segmented));

		
		ifstream myfile(location);
		string line;
		vector<string> vect;

		int count = 0; 

		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				count++; 
				if (count > 2)
				{
					string space = line;
					vector<string> split;
					boost::split(split, line, boost::is_any_of(" "));
					child_name.put("", split[8]);
					cout << split [8]<< endl;

					child_temporal_attribute.put("", "n/a");
					child_truncated.put("", 0);
					child_occluded.put("", 0); 
					x1.put("", split[0]);
					y1.put("", split[1]);
					x2.put("", split[2]);
					y2.put("", split[3]);
					x3.put("", split[4]);
					y3.put("", split[5]);
					x4.put("", split[6]);
					y4.put("", split[7]);

					child_difficult.put("", "0");

					vect1.push_back(std::make_pair("X", x1));
					vect1.push_back(std::make_pair("Y", y1));
					vect2.push_back(std::make_pair("X", x2));
					vect2.push_back(std::make_pair("Y", y2));
					vect3.push_back(std::make_pair("X", x3));
					vect3.push_back(std::make_pair("Y", y3));
					vect4.push_back(std::make_pair("X", x4));
					vect4.push_back(std::make_pair("Y", y4));

					children_of_bndbox.push_back(std::make_pair("vertice1", vect1));
					children_of_bndbox.push_back(std::make_pair("vertice2", vect2));
					children_of_bndbox.push_back(std::make_pair("vertice3", vect3));
					children_of_bndbox.push_back(std::make_pair("vertice4", vect4));

					children_of_object.push_back(std::make_pair("name", child_name));
					children_of_object.push_back(std::make_pair("temporal", child_temporal_attribute));
					children_of_object.push_back(std::make_pair("truncated", child_truncated));
					children_of_object.push_back(std::make_pair("occluded", child_occluded));
					children_of_object.push_back(std::make_pair("bndbox", children_of_bndbox));
					children_of_object.push_back(std::make_pair("difficult", child_difficult));

					children_of_tree.push_back(std::make_pair("object", children_of_object));

					children_of_bndbox.clear();
					children_of_object.clear();

					vect1.clear();
					vect2.clear();
					vect3.clear(); 
					vect4.clear(); 

				}
			}
			myfile.close();
		}

		tree.add_child("annotation", children_of_tree);
		boost::property_tree::write_xml(pathToSave.c_str(), tree, std::locale(), boost::property_tree::xml_writer_make_settings< std::string >('\t', 1));
		
}

void superviselyConversion (string pathToSave, string location)
{
    //Creating Tree
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(location, pt);
	vector<int> vect;
	string label;

	//Iterating through file and getting points 
	for (auto& kv : pt.get_child("objects")) {
		for (auto& kk : kv.second) {
			if (kk.first == "points")
			{
				for (auto& aa : kk.second.get_child("exterior")) {
					for (auto& ab : aa.second) {
						vect.push_back(ab.second.get_value<double>());
					}
				}
				break; 
			}
			if (kk.first == "classTitle")
			{
				label = kk.second.get_value<string>(); 
			}
		}
	}

	int width = 0;
	int hieght = 0;

	hieght = pt.get_child("size").get<int>("height"); 
	width = pt.get_child("size").get<int>("width");

		std::stringstream SSjson;

		int current_frame_number = 0;

		boost::property_tree::ptree tree; //highest node
		boost::property_tree::ptree children_of_tree; //2nd order node

		boost::property_tree::ptree child_folder;
		boost::property_tree::ptree child_filename;

		boost::property_tree::ptree children_of_source;
		boost::property_tree::ptree child_source_database;

		boost::property_tree::ptree child_width;
		boost::property_tree::ptree child_height;
		boost::property_tree::ptree child_depth;
		boost::property_tree::ptree children_of_size;

		boost::property_tree::ptree child_segmented;

		boost::property_tree::ptree child_name;
		boost::property_tree::ptree child_temporal_attribute;
		boost::property_tree::ptree child_truncated;
		boost::property_tree::ptree child_occluded;
		boost::property_tree::ptree children_of_bndbox;
		boost::property_tree::ptree child_xmin;
		boost::property_tree::ptree child_ymin;
		boost::property_tree::ptree child_xmax;
		boost::property_tree::ptree child_ymax;
		boost::property_tree::ptree child_difficult;
		boost::property_tree::ptree children_of_object;

		boost::property_tree::ptree vect1;
		boost::property_tree::ptree vect2;
		boost::property_tree::ptree vect3;
		boost::property_tree::ptree vect4;

		boost::property_tree::ptree x1;
		boost::property_tree::ptree y1;
		boost::property_tree::ptree x2;
		boost::property_tree::ptree y2;
		boost::property_tree::ptree x3;
		boost::property_tree::ptree y3;
		boost::property_tree::ptree x4;
		boost::property_tree::ptree y4;

		child_folder.put("", "C:/Users/pavne/Desktop");
		child_filename.put("",  "supervisely.jpg");

		child_source_database.put("", "http://127.0.0.1:8081");
		children_of_source.push_back(std::make_pair("database", child_source_database));

		child_width.put("", width);
		child_height.put("", hieght);
		child_depth.put("", "3");

		children_of_size.push_back(std::make_pair("width", child_width));
		children_of_size.push_back(std::make_pair("height", child_height));
		children_of_size.push_back(std::make_pair("depth", child_depth));

		child_segmented.put("", 0);


		children_of_tree.push_back(std::make_pair("folder", child_folder));
		children_of_tree.push_back(std::make_pair("filename", child_filename));
		children_of_tree.push_back(std::make_pair("source", children_of_source));
		children_of_tree.push_back(std::make_pair("size", children_of_size));
		children_of_tree.push_back(std::make_pair("segmented", child_segmented));

			child_name.put("", label);
			child_temporal_attribute.put("", "n/a");
			child_truncated.put("", 0);
			child_occluded.put("", 0); //is the object zoomed-in or zoomed-out with respect to origianl position

			x1.put("", vect[1]);
			y1.put("", vect[2]);
			x2.put("", vect[0]);
			y2.put("", vect[2]);
			x3.put("", vect[0]);
			y3.put("", vect[3]);
			x4.put("", vect[1]);
			y4.put("", vect[3]);

			child_difficult.put("", "0");

			vect1.push_back(std::make_pair("X", x1));
			vect1.push_back(std::make_pair("Y", y1));
			vect2.push_back(std::make_pair("X", x2));
			vect2.push_back(std::make_pair("Y", y2));
			vect3.push_back(std::make_pair("X", x3));
			vect3.push_back(std::make_pair("Y", y3));
			vect4.push_back(std::make_pair("X", x4));
			vect4.push_back(std::make_pair("Y", y4));

			children_of_bndbox.push_back(std::make_pair("vertice1", vect1));
			children_of_bndbox.push_back(std::make_pair("vertice2", vect2));
			children_of_bndbox.push_back(std::make_pair("vertice3", vect3));
			children_of_bndbox.push_back(std::make_pair("vertice4", vect4));

			children_of_object.push_back(std::make_pair("name", child_name));
			children_of_object.push_back(std::make_pair("temporal", child_temporal_attribute));
			children_of_object.push_back(std::make_pair("truncated", child_truncated));
			children_of_object.push_back(std::make_pair("occluded", child_occluded));
			children_of_object.push_back(std::make_pair("bndbox", children_of_bndbox));
			children_of_object.push_back(std::make_pair("difficult", child_difficult));

			children_of_tree.push_back(std::make_pair("object", children_of_object));

			children_of_bndbox.clear();
			children_of_object.clear();

		tree.add_child("annotation", children_of_tree);
		boost::property_tree::write_xml(pathToSave.c_str(), tree, std::locale(), boost::property_tree::xml_writer_make_settings< std::string >('\t', 1));

}