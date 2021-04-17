#include "task.h"
using namespace testspace;


std::vector<std::complex< double >> testspace::myfft(std::vector<std::complex< double >> vect) {
    int n = 0;
    size_t vectSize = vect.size();
    while (vectSize % 2 == 0) {
        n++;
        vectSize /= 2;
    }
    int elementsInBlock = vectSize;//N/(2^n)
    int numOfBlock = 1 << n;


    std::vector<std::complex< double >> vect_block(vect.size());
    std::vector<size_t> blockAddr(vect.size());
    if (n == 0) {
        for (int i = 0; i < vect.size(); i++) {
            blockAddr[i] = i;
        }
    }
    if (n == 1) {
        for (int i = 0; i < vect.size() / 2; i++) {
            blockAddr[i] = i * 2;
            blockAddr[i + vect.size() / 2] = i * 2 + 1;
        }
    }
    if (n > 1) {
        for (int i = 0; i < elementsInBlock; i++) {
            blockAddr[i] = i * numOfBlock;
        }

        int k = 1;
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < elementsInBlock; i++) {
                blockAddr[i + elementsInBlock * k] = blockAddr[i] + numOfBlock / (k * 2);
                blockAddr[i + elementsInBlock * 3] += blockAddr[i] + numOfBlock / (k * 2);
            }
            k++;
        }
        k = 1;
        while (numOfBlock / (1 << (k - 1)) > 4) {

            for (int i = 0; i < elementsInBlock * 4 * k; i++) {
                blockAddr[i + elementsInBlock * 4 * k] = blockAddr[i] + numOfBlock / (k * 8);
            }
            k++;
        }
    }


    std::complex< double > comp_one(0, 1.0);
    std::complex< double > main_exp = exp(comp_one * (-1.0 * 2 * PI / elementsInBlock));

    {
        std::vector<std::complex< double >> vect_exp(elementsInBlock);

        vect_exp[0] = 1;
        for (int i = 1; i < elementsInBlock; i++)
        {
            vect_exp[i] = vect_exp[i - 1] * main_exp;
        }


        for (int i = 0; i < numOfBlock; i++)
        {
            for (int j = 0; j < elementsInBlock; j++)
            {
                for (int m = 0; m < elementsInBlock; m++) {
                    vect_block[i * elementsInBlock + j] += vect[blockAddr[i * elementsInBlock + m]] * vect_exp[(j * m) % elementsInBlock];
                }
            }
        }
    }

    int k = 1;
    std::complex<double> buff;
    std::complex<double> e;
    int znam;
    std::vector<std::complex< double >> vect_exp(vect.size());
    for (int i = 0; i < n; i++) {
        znam = (vect.size() / (1 << (n - i - 1)));
        e = exp(comp_one * ((-1.0 * 2 * PI) / znam));
        vect_exp[0] = 1;
        for (int j = 1; j < znam; j++) {
            vect_exp[j] = vect_exp[j - 1] * e;

        }

        for (int j = 0; j < numOfBlock / (2 << i); j++) {
            int act = elementsInBlock * (2 << i);

            for (int m = act * j; m < act * j + act / 2; m++) {
                buff = vect_block[m];
                std::complex<double> exp_val = vect_exp[m % znam];// exp(comp_one * ((-1.0 * 2 * PI * m) / (vect.size() / (1 << (n - i - 1)))));
                vect_block[m] = buff + exp_val * vect_block[m + act / 2];
                vect_block[m + act / 2] = buff - exp_val * vect_block[m + act / 2];
            }
        }
    }


    return vect_block;
}