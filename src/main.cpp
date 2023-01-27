#include <ere/core/entryPoint.hpp>

int main(int argc, char** argv) {
    // * create the application
    std::shared_ptr<ere::application> app = ere::createApplication();

    // * run the application
    app->run();

    return 0;
}
