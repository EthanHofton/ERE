#include <ere/core/application.hpp>
#include <iostream>

namespace ere {

application::application() {}
application::~application() {}

void application::run() { std::cout << "application run" << std::endl; }
void application::onEvent() {}

}
