#include <ere/core/entry_point.hpp>
#include <ere/core/logger.hpp>

int main(int argc, char** argv) {

    // log application start
    ERE_INFO("Creating application");

    // create the application
    ere_create_application();

    // log application end
    ERE_INFO("Destroying application");

    return 0;
}
