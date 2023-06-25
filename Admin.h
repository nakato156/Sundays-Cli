#pragma once
#ifndef ADMIN_H
#define ADMIN_H
#include "Hash.h"
#include "Usuario.h"
#include "DataFrame.h"
#include "TreeAVLProduct.h"
#include "TreeBSTProduct.h"
#include "Estadisticas.h"
#include "Test.h"

class Admin : public Usuario {
	Usuario& usuario;
	HashTabla<std::string, Usuario> admins;
public:
	Admin() = default;
	Admin(Usuario& user) : usuario(user) {
		DataFrame file;
		file.read_csv("usuarios.csv");

		for (int i = 0; i < file.size(); i++) {
			if (file[i]["rol"] == "1") {
				Fila fila = file[i];
				Usuario admin(fila["uuid"], fila["nombre"], fila["email"]);
				admins.insertar(fila["uuid"], admin);
			}
		}
	}
	
	void verAdmins() {
		admins.imprimir([](Usuario admin) {
			cout << admin.getUUID() << "\t" << admin.getNombre() << endl;
		});
	}

	void agregarAdmin(string email, string nombre, string pass) {
		Usuario admin;
		admin.registro(email, nombre, pass, 1);
		admins.insertar(admin.getUUID(), admin);
	}

	void estadisticas() {
		Estadisticas stats();
	}

	void test() {
		TreeAVLProduct AvlTree;
		TreeBSTProduct bstTree;
		Test test(AvlTree, bstTree);
		test.init(); 
	}

};
#endif