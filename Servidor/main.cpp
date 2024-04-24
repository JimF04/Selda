#include "crow.h"
#include <json/json.h>
#include <iostream>

int main() {
    crow::SimpleApp app;

    // Define una ruta para recibir las coordenadas del jugador y del enemigo
    CROW_ROUTE(app, "/send_coordinates")
            .methods("POST"_method)
                    ([](const crow::request& req){
                        // Parsea el JSON recibido
                        auto json_data = crow::json::load(req.body);
                        if (!json_data)
                            return crow::response(400, "Invalid JSON");

                        // Extrae las coordenadas del jugador y del enemigo del JSON
                        auto player_coords = json_data["player_coords"];
                        auto enemy_coords = json_data["enemy_coords"];
                        auto map = json_data["map"];

                        // Imprime las coordenadas en la consola
                        std::cout << "Player Coords: " << player_coords << std::endl;
                        std::cout << "Enemy Coords: " << enemy_coords << std::endl;
                        std::cout << "Map: " << map<< std::endl;

                        // Crea un objeto JSON para la respuesta
                        crow::json::wvalue response_json;
                        response_json["message"] = "Received player and enemy coordinates";
                        response_json["status"] = "success";

                        // Envia una respuesta al cliente con el JSON
                        return crow::response(response_json);
                    });

    // Iniciar el servidor en el puerto 18080
    app.port(18080).multithreaded().run();
}