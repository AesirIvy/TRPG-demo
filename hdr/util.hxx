#ifndef UTIL_H
#define UTIL_H

#include "pch.hxx"

#include "being.hxx"

std::istringstream dataFromCSV(const std::string &filePath, const std::string &id);
void printCSV(std::string filePath);
void printParty(const std::vector<Being *> &party);

#endif
