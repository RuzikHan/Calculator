#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class printer {
private:
    long long power(long long st) {
        long long ans = 1;
        for (long i = 0; i < st; i++)
            ans *= 10;
        return ans;
    }

    vector<long long> tmp;
    vector<vector<char> > ans;
    string elements[7][18] = {{"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "      ", "     ", "     ", "     ", "     "},
                              {"#### ", " ##  ", "#### ", "#### ", "#  # ", "#### ", "#### ", "#### ", "#### ", "#### ", "     ", "     ", "   # ", " #    ", "     ", "     ", "  #  ", "#### "},
                              {"#  # ", "###  ", "   # ", "   # ", "#  # ", "#    ", "#    ", "   # ", "#  # ", "#  # ", " ##  ", "     ", "  #  ", "  #   ", "#### ", "     ", "     ", "#    "},
                              {"#  # ", " ##  ", "#### ", "#### ", "#### ", "#### ", "#### ", "   # ", "#### ", "#### ", "#### ", "#### ", " #   ", "   #  ", "     ", "  #  ", " ### ", "#    "},
                              {"#  # ", " ##  ", "#    ", "   # ", "   # ", "   # ", "#  # ", "   # ", "#  # ", "   # ", " ##  ", "     ", "  #  ", "  #   ", "#### ", "     ", "     ", "#    "},
                              {"#### ", "#### ", "#### ", "#### ", "   # ", "#### ", "#### ", "   # ", "#### ", "   # ", "     ", "     ", "   # ", " #    ", "     ", "     ", "  #  ", "#### "},
                              {"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "      ", "     ", "     ", "     ", "     "},};
public:

    void ensureCapacity(long long size, long long length) {
        tmp.resize(size);
        ans.resize(7 * size);
        for (long i = 0; i < 7 * size; i++) {
            ans[i].resize(5 * length);
        }
    }

    void putChar(char element, long long size, long long tmp_level) {
        long long num = 0, maxtmp = -power(9) - 7, tmp_level_end = tmp_level + 7 * (1 << (size - 1));
        tmp_level /= 7;
        tmp_level_end /= 7;
        size = 1 << (size - 1);
        for (long i = tmp_level; i < tmp_level_end; i++)
            if (tmp[i] > maxtmp) maxtmp = tmp[i];
        switch (element) {
            case '+':
                num = 10;
                break;
            case '-':
                num = 11;
                break;
            case '(':
                num = 12;
                break;
            case ')':
                num = 13;
                break;
            case '=':
                num = 14;
                break;
            case '*':
                num = 15;
                break;
            case '/':
                num = 16;
                break;
            case 'c':
            case 'C':
                num = 17;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                num = element - '0';
                break;
            default:
                cout << "Error: Invalid input" << endl;
                exit(0);
        }
        for (long i = 0; i < 7; i++)
            for (long j = 0; j < 5; j++)
                for (long q = i * size; q < i * size + size; q++)
                    for (long h = j * size; h < j * size + size; h++)
                        ans[q + tmp_level * 7][h + maxtmp] = elements[i][num][j];
        maxtmp += 5 * size;
        for (long i = tmp_level; i < tmp_level_end; i++)
            tmp[i] = maxtmp;
    }

    void print() {
        for (long i = 0; i < ans.size(); i++) {
            for (long j = 0; j < ans[i].size(); j++) {
                cout << ans[i][j];
            }
            cout << endl;
        }
    }

    void printImage() {
        ofstream os("temp.bmp", std::ios::binary);
        unsigned char signature[2] = {'B', 'M'};
        unsigned int dimensions[2] = {ans[0].size(), ans.size()};
        unsigned int fileSize = 14 + 40 + dimensions[0] * dimensions[1] * 4;
        unsigned int reserved = 0;
        unsigned int offset = 14 + 40;
        unsigned int headerSize = 40;
        unsigned short colorPlanes = 1;
        unsigned short bpp = 32;
        unsigned int compression = 0;
        unsigned int imgSize = dimensions[0] * dimensions[1] * 4;
        unsigned int resolution[2] = {2795, 2795};
        unsigned int pltColors = 0;
        unsigned int impColors = 0;
        os.write(reinterpret_cast<char *>(signature), sizeof(signature));
        os.write(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
        os.write(reinterpret_cast<char *>(&reserved), sizeof(reserved));
        os.write(reinterpret_cast<char *>(&offset), sizeof(offset));
        os.write(reinterpret_cast<char *>(&headerSize), sizeof(headerSize));
        os.write(reinterpret_cast<char *>(dimensions), sizeof(dimensions));
        os.write(reinterpret_cast<char *>(&colorPlanes), sizeof(colorPlanes));
        os.write(reinterpret_cast<char *>(&bpp), sizeof(bpp));
        os.write(reinterpret_cast<char *>(&compression), sizeof(compression));
        os.write(reinterpret_cast<char *>(&imgSize), sizeof(imgSize));
        os.write(reinterpret_cast<char *>(resolution), sizeof(resolution));
        os.write(reinterpret_cast<char *>(&pltColors), sizeof(pltColors));
        os.write(reinterpret_cast<char *>(&impColors), sizeof(impColors));
        unsigned char x, r, g, b;
        for (int i = dimensions[1] - 1; i >= 0; i--) {
            for (int j = 0; j < dimensions[0]; j++) {
                x = 0;
                if (ans[i][j] == '#') {
                    r = 0;
                    g = 0;
                    b = 0;
                } else {
                    r = 255;
                    g = 255;
                    b = 255;
                }
                os.write(reinterpret_cast<char *>(&b), sizeof(b));
                os.write(reinterpret_cast<char *>(&g), sizeof(g));
                os.write(reinterpret_cast<char *>(&r), sizeof(r));
                os.write(reinterpret_cast<char *>(&x), sizeof(x));
            }
        }
        os.close();
    }
};