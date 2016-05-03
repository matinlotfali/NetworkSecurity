#include <COMMON.CPP>

#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
#else
    #include <iostream.h>
#endif


void SimpleHashXOR_Run()
{
    cout<<"Simple hash algorithm: "<<endl;
    char again;
    do
    {
        int hlen;
        cout<<"Hash length in bits: ";
        cin>>hlen;
        do
        {
            cout<<"Hash or SetHashLen or Exit SimpleHashXOR (h/l/x)? ";
            cin>>again;
            switch (again) {
                case 'h':
                    {
                        long long hash = 0;
                        char message[100];
                        cout<<"Message: ";
                        cin>>message;
                        cout<<"Hash: ";
                        int len = strlen(message)*sizeof(char)*8;
                        for(int j = 0; j<hlen; j++)
                            for(int i=j; i<len; i+= hlen)
                            {
                                int bit1 = GetBitInString(message,i);
                                hash = xorbit(hash,j,bit1);
                            }
                        cout<<hex<<hash<<endl<<endl;
                    }
                    break;                
                case 'x':
                    return;
            }
        }while(again != 'l');
    }while(again == 'l');
}
