#include <iostream>
#include <memory>
#include "Scene.hpp"
#include "Vec.hpp"

int main()
{
	int nx = 600;
	int ny = 300;
	int ns = 300;
	std::unique_ptr<Scene> s(std::make_unique<Scene>(ny,nx,ns,"render3.bmp"));
	s->render();
	return 0;
}