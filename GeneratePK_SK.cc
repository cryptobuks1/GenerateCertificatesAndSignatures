#include <iostream>
#include <sstream>
#include "/usr/include/crypto++/eccrypto.h"
#include "/usr/include/crypto++/osrng.h"
#include "/usr/include/crypto++/oids.h"
#include "/usr/include/crypto++/files.h"

using namespace CryptoPP;

int main(int argc, const char* argv[]) 
{
    AutoSeededRandomPool prng;
    FileSink fs1( "private.ec.der", true /*binary*/ );
    FileSink fs3( "public.ec.der", true /*binary*/ );
    int i = 0;
    while (i<55){
        ECDSA<ECP, SHA256>::PrivateKey k;
        k.Initialize( prng, ASN1::secp256r1() );
        //ECDSA<ECP, SHA256>::Signer signer(k);
        //FileSink fs2( "signer.ec.der", true /*binary*/ );
        //signer.AccessKey().Save( fs2 );

        ECDSA<ECP, SHA256>::PublicKey publicKey;
        k.MakePublicKey(publicKey);
        const ECP::Point& q = publicKey.GetPublicElement();
        const Integer& qx = q.x;
        const Integer& qy = q.y;
        std::stringstream ssx, ssy ;
        ssx << std::hex << q.x ;
        ssy << std::hex << q.y ;
        std::string pt1 = ssx.str();
        std::string pt2 = ssy.str();
        if(pt1.length()==65 && pt2.length()==65){
            std::cout<<"Done"<<std::endl;
            publicKey.Save( fs3 );
            k.Save( fs1 );
            i++;
        }
        //ECDSA<ECP, SHA256>::Verifier verifier(publicKey);
        //FileSink fs4( "verifier.ec.der", true /*binary*/ );
        //verifier.AccessKey().Save( fs4 );
    }

    return 0;
}