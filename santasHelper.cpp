#include "santasHelper.hpp"

// All none template functions need to be defined in the cpp file

SantasHelper::SantasHelper() {}
SantasHelper::~SantasHelper() {}
SantasHelper::SantasHelper(const SantasHelper &santasHelper) {}
SantasHelper::SantasHelper(SantasHelper &&santasHelper) {}
SantasHelper& SantasHelper::operator=(const SantasHelper &santasHelper) {return *this;}
SantasHelper& SantasHelper::operator=(SantasHelper &&santasHelper) {return *this;}
