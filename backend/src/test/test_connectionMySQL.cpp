#include "dao/cConnectionMySQL.h"
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << ">> == Teste de conexão MySQL ==" << std::endl;

    try {
        cConnectionMySQL conn;

        if (conn.isConnected()) {
            std::cout << ">> [OK] Ping no banco realizado com sucesso" << std::endl;
        }
        else {
            std::cout << ">> [ERRO] Conexão não estabelecida" << std::endl;
            return 1;
        }
    }
    catch(const std::runtime_error& e) {
        std::cout << ">> [EXCEPTION] " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
