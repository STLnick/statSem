#include <iostream>

void showHelp()
{
  std::cout << "~ ~ ~ ~ ~ [ Compilers ] ~ ~ ~ ~ ~" << std::endl
            << "~ ~ ~ ~ ~  [ Parser ] ~ ~ ~ ~ ~" << std::endl
            << std::endl
            << "The only flag used for this program is the one you already used!" << std::endl
            << "    -h  -> Help" << std::endl
            << std::endl
            << "**Run command structure**:" << std::endl
            << "  ./frontEnd [ _file_ ]    -> read from _file_.fs" << std::endl
            << std::endl
            << "**NOTE** The file must be of extension '.fs'." << std::endl
            << "         More specifically, if you specify an extension it MUST BE '.fs'" << std::endl
            << "         and if no file extension is specified then scanner will look for [ _file_ ].fs" << std::endl
            << "         Also, the files being provided must be in the same directory as the executable."
            << std::endl
            << "Examples of valid invocations:" << std::endl
            << "\t./frontEnd test3.fs" << std::endl
            << "\t./frontEnd test3  (Valid IF there is in fact a file 'test3.fs')" << std::endl
            << "Examples of _invalid_ invocations:" << std::endl
            << "\t./frontEnd test2.txt" << std::endl
            << "\t./frontEnd test2  (_Invalid_ IF there is NO file 'test2.fs')" << std::endl
            << std::endl;
}