#pragma once
#ifndef STATS_H
#define STATS_H
#include "DataFrame.h"
#include "Categoria.h"
#include <unordered_map>
#include <unordered_set>
#include "helpers.cpp"

class Estadisticas {
public:
    Estadisticas() = default;
    std::string obtenerCodigo(const std::string& producto) {
        // Obtener solo el código del producto sin la cantidad
        size_t pos = producto.find('/');
        if (pos != std::string::npos) {
            return producto.substr(0, pos);
        }
        return producto;
    }
    std::unordered_map<std::string, int> contarPlatosPorCategoria(const MapadeCate& categoriasPlatos) {
        std::unordered_map<std::string, int> categorias;

        // Leer el archivo CSV y contar los platos por categoría
        std::ifstream file("historial.csv");
        std::string line;

        std::getline(file, line); // Ignorar la primera línea del encabezado

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uuid, cliente_uuid, productos, monto, fecha;
            std::getline(ss, uuid, ',');
            std::getline(ss, cliente_uuid, ',');
            std::getline(ss, productos, ',');
            std::getline(ss, monto, ',');
            std::getline(ss, fecha, ',');

            std::stringstream productStream(productos);
            std::string producto;

            while (std::getline(productStream, producto, ';')) {
                std::string codigo = producto.substr(0, producto.find('/'));
                Categoria categoria = buscarCategoriaPorCodigo(categoriasPlatos, codigo);
                categorias[categoria.getNombre()]++;
            }
        }

        return categorias;
    }
    int contarClientes() {
        std::unordered_set<std::string> clientes;

        // Leer el archivo CSV y contar los clientes únicos
        std::ifstream file("historial.csv");
        std::string line;

        std::getline(file, line); // Ignorar la primera línea del encabezado

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uuid, cliente_uuid, productos, monto, fecha;
            std::getline(ss, uuid, ',');
            std::getline(ss, cliente_uuid, ',');
            std::getline(ss, productos, ',');
            std::getline(ss, monto, ',');
            std::getline(ss, fecha, ',');

            clientes.insert(cliente_uuid);
        }

        return clientes.size();
    }
    std::string platoMasVendido() {
        std::unordered_map<std::string, int> ventasPlatos;

        // Leer el archivo CSV y contar las ventas de cada plato
        std::ifstream file("historial.csv");
        std::string line;

        std::getline(file, line); // Ignorar la primera línea del encabezado

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uuid, cliente_uuid, productos, monto, fecha;
            std::getline(ss, uuid, ',');
            std::getline(ss, cliente_uuid, ',');
            std::getline(ss, productos, ',');
            std::getline(ss, monto, ',');
            std::getline(ss, fecha, ',');

            std::stringstream productStream(productos);
            std::string producto;

            while (std::getline(productStream, producto, ';')) {
                std::string plato = obtenerCodigo(producto);
                ventasPlatos[plato]++;
            }
        }

        // Encontrar el plato más vendido
        std::string platoMasVendido;
        int maxVentas = 0;

        for (const auto& entry : ventasPlatos) {
            if (entry.second > maxVentas) {
                maxVentas = entry.second;
                platoMasVendido = entry.first;
            }
        }

        return platoMasVendido;
    }
    std::string encontrarCategoriaMasVendida(const MapadeCate& categoriasPlatos) {//nol ahe probao
        std::unordered_map<std::string, int> conteoCategorias = contarPlatosPorCategoria(categoriasPlatos);

        std::string categoriaMasVendida;
        int maxCantidad = 0;

        for (const auto& item : conteoCategorias) {
            const std::string& categoria = item.first;
            int cantidad = item.second;

            if (cantidad > maxCantidad) {
                maxCantidad = cantidad;
                categoriaMasVendida = categoria;
            }
        }

        return categoriaMasVendida;
    }
};

#endif