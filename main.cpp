#include <iostream>
#include <cmath>
#include <memory>
#include "Scene.hpp"
#include "Vec.hpp"
#include "Intersection.hpp"

int main()
{
	// Vec3 t9[3] = {Vec3(-0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -0.5f), Vec3(0.5f, -0.5f, -1.5f)};
	// int cut = 1000;
	// for (int i = 0; i < cut; i++)
	// {
	// 	// std::cout << Vec3(0,std::sinf(PI + (PI / 2 / cut ) * i),std::cosf(PI + (PI / 2 / cut ) * i)) << std::endl;
	// 	std::cout << intersection(Vec3(0), Vec3(0, std::sinf(PI + (PI / 2 / cut) * i), std::cosf(PI + (PI / 2 / cut) * i)), t9) << std::endl;
	// }
	int ny = 100;
	int nx = 100;
	int ns = 10;
	std::unique_ptr<Scene> s(std::make_unique<Scene>(ny,nx,ns,"render.bmp"));
	s->render();
	return 0;
}