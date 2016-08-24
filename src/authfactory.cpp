#include "authptc.h"
#include "authgoogle.h"
#include "authfactory.h"

IAuth *AuthFactory::createAuthProvider(IAuth::AuthProviders provider)
{
    switch (provider) {
    case IAuth::Google:
        return new AuthGoogle();
    case IAuth::PTC:
        return new AuthPTC();
    default:
        return nullptr;
    }
}
