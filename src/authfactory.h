#ifndef AUTHFACTORY_H
#define AUTHFACTORY_H

#include "iauth.h"

class AuthFactory
{

private:
    AuthFactory();
    AuthFactory(const AuthFactory &);

public:
    static IAuth * createAuthProvider(IAuth::AuthProviders provider);

};

#endif // AUTHFACTORY_H
