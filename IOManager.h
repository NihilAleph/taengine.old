#ifndef IOMANAGER_H
#define IOMANAGER_H

#include<string>
#include<vector>

namespace taengine {
    class IOManager
    {
        public:

			static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
			static bool readFileToBuffer(std::string filePath, std::string& buffer);
        protected:
        private:
    };
}
#endif // IOMANAGER_H
