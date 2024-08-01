#ifndef TRANSPORTEDTO_HPP
#define TRANSPORTEDTO_HPP

#include <string>

class TransporteDTO {
    private:
        std::string nome;
        std::string local;
    public:
        TransporteDTO(std::string nome, std::string local);
        std::string toString();
};

#endif