#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main() {
	std::ofstream fout("../cat_quest/room_def.cpp");
	std::ofstream hout("../cat_quest/room_def.h");
	std::ofstream rout("../cat_quest/room_list.h");
	fout << "#include \"room.h\"\n";
	int n = 0;
	rout << "Room::Rooms Room::rm[] = {";
	std::string str = "../cat_quest/level/" + std::to_string((long long) n) + ".bmp";
	FILE *f;
	while(f = fopen(str.c_str(), "r")) {
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f);

		int width = *(int*)&info[18];
		int height = *(int*)&info[22];

		int size = 3 * width;
		unsigned char** data = new unsigned char*[height];
		for(int i = height - 1; i >= 0; i--) {
			data[i] = new unsigned char[size];
			fread(data[i], sizeof(unsigned char), size, f);
		}
		fclose(f);
		
		hout << "static void r" << n << "();\n";
		rout << (n != 0 ? "," : "") << "Room::r" << n;

		fout << "void Room::r" << n << "() {";
		fout << "w = " << width << ";";
		fout << "h = " << height << ";";

		for(int i = 0; i < height; i++) {
			for(int j = 0; j < 3 * width; j += 3) {
				int r = data[i][j + 2];
				int g = data[i][j + 1];
				int b = data[i][j];
				int color = (r<<16) | (g<<8) | b;
				
				if(color != 0xFFFFFF) {
					fout << "C(";
				}
				switch(color) {
				case 0x000000:
					fout << "Wall";
					break;
				case 0x4CFF00:
					fout << "Goal";
					break;
				case 0xFFD800:
					fout << "Player";
					break;
				case 0x00FFFF:
					fout << "Spike";
					break;
				case 0xFF0000:
					fout << "EnemyBasic";
					break;
				case 0x7F0000:
					fout << "EnemyFlyingBasic";
					break;
				case 0xB200FF:
					fout << "Fish";
					break;
				case 0x808080:
					fout << "WallPass";
					break;
				case 0x0026FF:
					fout << "Life";
					break;
				}

				if(color != 0xFFFFFF) {
					fout << "," << j/3 << "," << i << ");";
				}
			}
		}
		fout << "}\n";
		str = "../cat_quest/level/" + std::to_string((long long)++n) + ".bmp";
		delete data;
	}
	rout << "};";

	rout.close();
	hout.close();
	fout.close();
	delete f;
	system("PAUSE");
}