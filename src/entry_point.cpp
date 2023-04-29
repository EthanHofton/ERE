#include <ere/core/entry_point.hpp>
#include <ere/core/logger.hpp>

int main(int argc, char** argv) {

    // log application start
    ERE_INFO("ERE startup");

    // create the application
    ere::ref<ere::application> app = ere::ere_create_application(argc, argv);

    ERE_INFO("ERE runtime");
    app->run();

    // log application end
    ERE_INFO("ERE cleanup");

    // free the app
    app = nullptr;


    return 0;
}
