#include <PLAYFAIR.CPP>
#include <HILL.CPP>
#include <RSA.CPP>
#include <VIGENERE.CPP>
#include <SHXOR.CPP>
#include <SHRXOR.CPP>
#include <DES.CPP>
#include <BBS.CPP>

#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
    int main()
#else
    #include <iostream.h>
    void main()
#endif


{
    char ch;
    do
    {
        cout<<"Algoritms: "<<endl;
        cout<<"\t 0: Playfair"<<endl;
        cout<<"\t 1: Hillcipher"<<endl;
        cout<<"\t 2: RSA"<<endl;
        cout<<"\t 3: Vigenere"<<endl;
        cout<<"\t 4: Simple Hash XOR"<<endl;
        cout<<"\t 5: Simple Hash Rotate XOR"<<endl;
        cout<<"\t 6: DES"<<endl;
        cout<<"\t 7: Blum Blum Shup (BBS)"<<endl;
        cout<<endl;
        cout<<"\t e: Exit"<<endl;
        cout<<"Your choice: ";
        cin>>ch;
        cout<<endl;
        switch (ch) {
            case '0':
                Playfair_Run();
                break;
            case '1':
                Hillcipher_Run();
                break;               
            case '2':
                RSA_Run();
                break;
            case '3':
                Vigenere_Run();
                break;
            case '4':
                SimpleHashXOR_Run();
                break;
            case '5':
                SimpleHashXOR_Run();
                break;
            case '6':
                DES_Run();
                break;
            case '7':
                BBS_Run();
                break;
        }
        cout<<endl;
    }while(ch != 'e');




    #ifdef QT_CORE_LIB
	    return 0;
    #endif
}
