#include "Login.h"

void Login::login() {
    string email;
    cout << "Email: "; cin >> email;
    cout << "Password: ";

    string password = inputPassword();
    user.login(email, password);
}