#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
#else
    #include <iostream.h>
#endif

#include <COMMON.CPP>

int CalculateInv(int p , int q, int e)
{
    int ferma = (p-1)*(q-1);
    int n = p*q;
    for(int x = 0; x<=n; x++)
    {
        double d = ((double)(x*ferma + 1))/e;
        if(d == (int)d)
            return d;
    }
    return -1;
}

void RSA_Run()
{        
    cout<<"RSA algorithm: "<<endl;
    char again;
    do
    {
        int p, q, e;
        cout<<"P (prime): ";
        cin>>p;

        cout<<"Q (prime): ";
        cin>>q;

        cout<<"N = ";
        int n = p*q;
        cout<< n <<endl;

        cout<<"E (prime): ";
        cin>>e;

        cout<<"D = ";
        int d = CalculateInv(p,q,e);
        cout<< d <<endl<<endl;

        do
        {
            cout<<"Encrypt or Decript or SetKey or Exit RSA (e/d/k/x)? ";
            cin>>again;
            switch (again) {
                case 'e':
                    int m;
                    cout<<"Message: ";
                    cin>>m;
                    cout<<"Cipher: "<< PowMod(m,e,n) << endl << endl;
                    break;
                case 'd':
                    int c;
                    cout<<"Cipher: ";
                    cin>>c;
                    cout<<"Message: "<< PowMod(c,d,n) << endl << endl;
                    break;
                case 'x':
                    return;
            }
        }while(again != 'k');
    }while(again == 'k');
}
