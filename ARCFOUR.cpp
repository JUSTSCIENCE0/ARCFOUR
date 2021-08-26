#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

class PRNSGenerator
{
private:
    BYTE* S = new BYTE[256];
    UINT8 i = 0;
    UINT8 j = 0;

public:
    PRNSGenerator(BYTE* Key, UINT16 length)
    {
        for (int it = 0; it < 256; it++)
        {
            S[it] = it;
        }
        j = 0;
        for (int it = 0; it < 256; it++)
        {
            j = (j + S[it] + Key[it % length]) % 256;
            swap(S[it], S[j]);
        }
        i = 0;
        j = 0;
    }

    BYTE NextBYTE()
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        UINT8 t = (S[i] + S[j]) % 256;
        return S[t];
    }
};

bool IsEqual(BYTE* A, BYTE* B, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (A[i] != B[i]) return false;
    }
    return true;
}

int main()
{
    srand(time(0));
    cout << hex;
    
    for (int num = 0; num < 1000; num++)
    {
        int sz = rand() % 256 + 1;
        BYTE* Key = new BYTE[sz];
        //cout << "Key: " << endl;
        for (int i = 0; i < sz; i++)
        {
            Key[i] = rand() % 256;
            //cout << (int)Key[i] << " ";
        }
       // cout << endl;

        PRNSGenerator EncrGnr = PRNSGenerator(Key, sz);
        //cout << "Open text:" << endl;
        int size = rand() % 256 + 1;
        BYTE* OpenText = new BYTE[size];
        for (int i = 0; i < size; i++)
        {
            OpenText[i] = rand() % 256;
            //cout << (int)OpenText[i] << " ";
        }
        //cout << endl;

        //cout << "Encrypted text:" << endl;
        BYTE* ClosedText = new BYTE[size];
        for (int i = 0; i < size; i++)
        {
            BYTE RndKey = EncrGnr.NextBYTE();
            ClosedText[i] = OpenText[i] ^ RndKey;
            //cout << (int)ClosedText[i] << " ";
        }
        //cout << endl;

        PRNSGenerator DecrGnr = PRNSGenerator(Key, sz);
        //cout << "Decrypted text:" << endl;
        BYTE* DecrText = new BYTE[size];
        for (int i = 0; i < size; i++)
        {
            BYTE RndKey = DecrGnr.NextBYTE();
            DecrText[i] = ClosedText[i] ^ RndKey;
            //cout << (int)DecrText[i] << " ";
        }
        //cout << endl;

        if (IsEqual(OpenText, DecrText, size)) cout << "Success!\n";
        else cout << "Failed!\n";

        //cout << endl;
    }
    std::cout << "Finished!\n";
}
