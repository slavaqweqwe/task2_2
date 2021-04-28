#include "task.h"
using namespace testspace;


using complex = std::complex< double >;


std::vector<size_t> FindAddrs(size_t VectSize, int n, size_t numOfBlock, size_t elementsInBlock) {
    std::vector<size_t> AddrsFFtElements(VectSize); //2
    if (n == 0) {
        for (int i = 0; i < VectSize; i++) {
            AddrsFFtElements[i] = i;
        }
    }
    if (n == 1) {
        for (int i = 0; i < VectSize / 2; i++) {
            AddrsFFtElements[i] = i * 2;
            AddrsFFtElements[i + VectSize / 2] = i * 2 + 1;
        }
    }
    if (n > 1) {
        for (size_t i = 0; i < elementsInBlock; i++) {
            AddrsFFtElements[i] = i * numOfBlock;
        }

        int k = 1;
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < elementsInBlock; i++) {
                AddrsFFtElements[i + elementsInBlock * k] = AddrsFFtElements[i] + numOfBlock / (k * 2);
                AddrsFFtElements[i + elementsInBlock * 3] += AddrsFFtElements[i] + numOfBlock / (k * 2);
            }
            k++;
        }
        k = 1;
        while (numOfBlock / (1 << (k - 1)) > 4) {

            for (int i = 0; i < elementsInBlock * 4 * k; i++) {
                AddrsFFtElements[i + elementsInBlock * 4 * k] = AddrsFFtElements[i] + numOfBlock / (k * 8);
            }
            k++;
        }
    }
    return AddrsFFtElements;
}
std::vector<complex> GetElementaryBlocks(std::vector<complex> vect,int n, size_t numOfBlock, size_t elementsInBlock){


    complex CompOne(0, 1.0);
    complex MainExp = exp(CompOne * (-1.0 * 2 * PI / elementsInBlock));
    std::vector<size_t> AddrsFFtElements = FindAddrs(vect.size(), n, numOfBlock, elementsInBlock);//2
    std::vector<complex> VectExp(elementsInBlock);
    std::vector<complex> VectorPreparedBlocks(vect.size());

    VectExp[0] = 1;
    for (int i = 1; i < elementsInBlock; i++)
    {
        VectExp[i] = VectExp[i - 1] * MainExp;
    }


    for (int i = 0; i < numOfBlock; i++)
    {
        for (int j = 0; j < elementsInBlock; j++)
        {
            for (int m = 0; m < elementsInBlock; m++) {
                VectorPreparedBlocks[i * elementsInBlock + j] += vect[AddrsFFtElements[i * elementsInBlock + m]] * VectExp[(j * m) % elementsInBlock];
            }
        }
    }
    return VectorPreparedBlocks;
}


std::vector<complex> testspace::myfft(std::vector<complex> vect) {
    int n = 0;//the power of two in the length of the vector
    size_t elementsInBlock = vect.size();
    while (elementsInBlock % 2 == 0) {
        n++;
        elementsInBlock /= 2;
    }
    size_t numOfBlock = 1 << n;
    std::vector<complex> FFTvector = GetElementaryBlocks(vect, n, numOfBlock, elementsInBlock);


    complex CompOne(0, 1.0);
    complex buff;
    complex e;
    int znam;
    std::vector<complex> VectExp(vect.size());
    VectExp[0] = 1;

    for (int i = 0; i < n; i++) {
        znam = (vect.size() / (1 << (n - i - 1)));
        e = exp(CompOne * ((-1.0 * 2 * PI) / znam));
        for (int j = 1; j < znam; j++) {
            VectExp[j] = VectExp[j - 1] * e;
        }

        for (int j = 0; j < numOfBlock / (2 << i); j++) {
            int act = elementsInBlock * (2 << i);

            for (int m = act * j; m < act * j + act / 2; m++) {
                buff = FFTvector[m];
                std::complex<double> AddVal = VectExp[m % znam] * FFTvector[m + act / 2];
                FFTvector[m] =           buff + AddVal;
                FFTvector[m + act / 2] = buff - AddVal;
            }
        }
    }


    return FFTvector;
}