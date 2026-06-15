#include "Memory.h"

#include <iostream>
#include <osg/Image>
#include <osg/ref_ptr>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

bool linuxSaveToShm(const osg::ref_ptr<osg::Image> image, const std::string& sharedName) {
    size_t imageSize = image -> getTotalSizeInBytes();

    int sharedFileDescriptor = shm_open(sharedName.c_str(), O_CREAT | O_RDWR, 0666);
    if (sharedFileDescriptor == -1) {
        std::cerr << "Failed to create shared memory\n";
        return false;
    }

    if (ftruncate(sharedFileDescriptor, imageSize) == -1) {
        std::cerr << "Failed to resize shared memory\n";
        close(sharedFileDescriptor);
        return false;
    }

    void* ptr = mmap(0, imageSize, PROT_READ | PROT_WRITE, MAP_SHARED, sharedFileDescriptor, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory\n";
        close(sharedFileDescriptor);
        return false;
    }

    std::memcpy(ptr, image -> data(), imageSize);

    std::cout << "Wrote image " << sharedName << " to RAM sector\n";

    munmap(ptr, imageSize);
    close(sharedFileDescriptor);

    return true;
}
