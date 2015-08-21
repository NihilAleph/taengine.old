#include "IOManager.h"

#include<fstream>


namespace taengine {
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
		std::ifstream file(filePath, std::ios::binary);

		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		// seek to the end of file
		file.seekg(0, std::ios::end);

		// get file size
		int fileSize = file.tellg();

		// seek to begining again
		file.seekg(0, std::ios::beg);

		// reduce the file size by any header bytes
		fileSize -= file.tellg();

		buffer.resize(fileSize);

		// buffer can be cast to char* since it doesn't change the format, just interpretation
		file.read((char *)&(buffer[0]), fileSize);

		file.close();

		return true;
	}

	bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer) {
		std::ifstream file(filePath, std::ios::binary);

		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		// seek to the end of file
		file.seekg(0, std::ios::end);

		// get file size
		int fileSize = file.tellg();

		// seek to begining again
		file.seekg(0, std::ios::beg);

		// reduce the file size by any header bytes
		fileSize -= file.tellg();

		buffer.resize(fileSize);

		// buffer can be cast to char* since it doesn't change the format, just interpretation
		file.read((char *)&(buffer[0]), fileSize);

		file.close();

		return true;
	}
}
