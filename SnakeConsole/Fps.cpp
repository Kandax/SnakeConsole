#include <chrono>
#include <thread>
#include <Windows.h>
#include <iostream>



class Fps {
private:
	float fps = 15;
	float delay = 0;
	std::chrono::high_resolution_clock::time_point startF;
	std::chrono::high_resolution_clock::time_point endF;

public:
	void setFps(float f) {
		fps = f;
	}

	void start() {
		startF = std::chrono::high_resolution_clock::now();
	}
	void end() {

		endF = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = endF - startF;
		delay = (1000.0F / fps) - duration.count();
		std::this_thread::sleep_for(std::chrono::milliseconds((long)delay));
	}
};


	

	
