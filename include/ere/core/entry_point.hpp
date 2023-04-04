#ifndef __ERE_ENTRY_POINT_HPP__
#define __ERE_ENTRY_POINT_HPP__

/**
* @brief extern function to create application. To be implemented by client.
*/
extern void ere_create_application();

/**
* @brief main function. This is the entry point of the application.
*
* @param argc the number of arguments
* @param argv the arguments
*
* @return the exit code
*/
int main(int argc, char** argv);

#endif
