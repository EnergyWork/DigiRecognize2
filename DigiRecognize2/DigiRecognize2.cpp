#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

typedef vector<vector<bool>> DigitMatrix;
vector<DigitMatrix> patterns2 = {
    {
        {0, 0, 0},
        {0, 1, 1},
        {0, 0, 0}
    },
    {
        { 0, 0, 0 },
        { 1, 1, 0 },
        { 0, 0, 0 }
    },
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}
    },
    {
        {0, 0, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    {
        {0, 0, 0},
        {0, 1, 1},
        {0, 1, 0}
    },
    {
        {0, 0, 0},
        {1, 1, 0},
        {0, 1, 0}
    },
    {
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 0}
    },
    {
        {0, 1, 0},
        {0, 1, 1},
        {0, 0, 0}
    },
    {
        {0, 1, 0},
        {0, 1, 1},
        {0, 1, 0}
    },
    {
        {0, 1, 0},
        {1, 1, 0},
        {0, 1, 0}
    },
    {
        {0, 0, 0},
        {1, 1, 1},
        {0, 1, 0}
    },
    {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0}
    },
};
struct Digit {
    DigitMatrix digitmatr;
    size_t n, m;
};

Digit init_digit(string file)
{
    ifstream in(file);
    bool tmp;
    vector<bool> tmp_vec;
    Digit digit;
    in >> digit.n >> digit.m;
    for (size_t i = 0; i < digit.n; i++)
    {
        for (size_t j = 0; j < digit.m; j++)
        {
            in >> tmp;
            tmp_vec.emplace_back(tmp);
        }
        digit.digitmatr.emplace_back(tmp_vec);
        tmp_vec.clear();
    }
    return digit;
}

bool isPattern(size_t x, bool ij, bool i_top, bool i_bottom, bool j_right, bool j_left)
{
    if (patterns2[x][0][1] == i_top && patterns2[x][2][1] == i_bottom && patterns2[x][1][0] == j_right && patterns2[x][1][2] == j_left && patterns2[x][1][1] == ij)
        return true;
    return false;
}

int pixel_recognize(Digit digit, size_t i, size_t j)
{
    for (size_t x = 0; x < patterns2.size(); x++)
    {
        if (i < digit.n - 1 && j < digit.m - 1)
            if (isPattern(x, digit.digitmatr[i][j], digit.digitmatr[i - 1][j], digit.digitmatr[i + 1][j], digit.digitmatr[i][j - 1], digit.digitmatr[i][j + 1]))
                return x + 1;
    }
    return NULL;
}

int recognize_pattern_kit(vector<int> pattern_kit)
{
    if (pattern_kit.empty())
        return -1;

    stringstream ss;
    int pattern;
    for (size_t i = 0; i < pattern_kit.size(); i++)
        ss << pattern_kit[i];
    ss >> pattern;
    switch (pattern)
    {
        case 5687:    return 0;
        case 43:      return 1;
        case 165782:  return 2;
        case 1611017: return 3;
        case 448103:  return 4;
        case 528617:  return 5;
        case 529687:  return 6;
        case 163:     return 7;
        case 5691087: return 8;
        case 5681017: return 9;
        default:      return -1;
    }
}

int recognize(Digit digit)
{
    bool flag = false;
    size_t tmpi = 0, tmpj = 0;
    vector<int> pattern_kit;
    for (size_t i = 0; i < digit.n; i++)
    {
        for (size_t j = 0; j < digit.m; j++)
        {
            if (digit.digitmatr[i][j] == true) //it is if
            {
                flag = true;
                tmpi = i;
                tmpj = j;
                break;
            }
        }
        if (flag)
            break;
    }

    for (size_t i = tmpi; i < digit.n; i++)
    {
        for (size_t j = tmpj; j < digit.m; j++)
        {
            if (digit.digitmatr[i][j] == 1)
            {
                int tmp_pattern_index = pixel_recognize(digit, i, j);
                if (tmp_pattern_index != 0)
                    pattern_kit.emplace_back(tmp_pattern_index);
            }
        }
    }

    return recognize_pattern_kit(pattern_kit);
}

int main()
{
    int dig = recognize(init_digit("3.txt"));
    if (dig == -1)
        cout << "Not number" << endl << endl;
    else
        cout << "Number: " << dig << endl << endl;

    system("pause");
    return 0;
}