
#include <iostream>
#include "AJ_Scanner.h"

using namespace AJimpa;

void Printer(STRING path, ListingChannel mtype)
{
    switch (mtype)
    {
    case ListingChannel::Begin:
        LOG("Begen = >" + path);
        break;
    case ListingChannel::File:
        LOG("File = >" + path);
        break;
    case ListingChannel::Folder:
        F_ListFilesInDirectory(path, true, Printer);
        break;
    case ListingChannel::SystemError:
        LOG("SystemError" + path);
        break;
    case ListingChannel::NotExist:
        LOG("NotFind" + path);
        break;
    case ListingChannel::End:
        LOG("End = >" + path);
        break;
    }
}

int main()
{
    STRING path;
    Request("Wrtie Address", path);
    F_ListFilesInDirectory(path, true, Printer);

    std::cin.get();
    return 0;
}
