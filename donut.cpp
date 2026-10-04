#include <iostream>
#include <cmath>
#include <string>
#include <thread>
#include <chrono>

const float Rone = 1;
const float Rtwo = 2;
const float Kone = 50;
const float Ktwo = 5;


struct coordinate_output {double x, y, z; };

coordinate_output construct_donut(float theta, float phi, float A, float B) {

    float x = (Rtwo + Rone*std::cos(theta))*(std::cos(B)*std::cos(phi)+std::sin(A)*std::sin(B)*std::sin(phi)) - Rone*std::cos(A)*std::sin(B)*std::sin(theta);
    float y = (Rtwo + Rone*std::cos(theta))*(std::cos(phi)*std::sin(B) - std::cos(B)*std::sin(A)*std::sin(phi)) + Rone*std::cos(A)*std::cos(B)*std::sin(theta);
    float z = std::cos(A)*(Rtwo+Rone*std::cos(theta))*std::sin(phi) + Rone*std::sin(A)*std::sin(theta);

    return {x, y, z};
}


int main() {
    float A = 1;
    float B = 1;
    std::cout << "\x1b[2J";
    while (true){

    char grid[100][100];
    for (int x = 0; x<99; x++) {
        for (int y = 0; y<99; y++) {
            grid[x][y] = '.';
        }
    }

    A += 0.5;
    B += 0.02;


    for (float theta = 0; theta < 2*3.14; theta+=0.035) {
        for (float phi = 0; phi < 2*3.14; phi+=0.035) {

            coordinate_output coord_struct = construct_donut(theta, phi, A, B);

            float loop_x = coord_struct.x;
            float loop_y = coord_struct.y;
            float loop_z = coord_struct.z;


            int project_x = Kone*loop_x/(Ktwo+loop_z) + 50;
            int project_y = Kone*loop_y/(Ktwo+loop_z) + 50;


            grid[project_x][project_y] = '#';



        }

    }
    std::string frame = "\x1b[H";


    for (int x = 0; x <99; x++) {
        for (int y = 0; y <99; y++) {
            frame += grid[x][y];
        }
        frame += "\n";
    }
    std::cout << frame << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

}

    return 0;
}









