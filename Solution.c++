#include <iostream>
#include <string>
using namespace std;

class Engine {
public:
    virtual void Status(int speed) = 0; 
    virtual ~Engine() {} 
};

class GasEngine : public Engine { 
public:
    void Status(int speed) override {
        cout << "Gas Engine is running on speed = " << speed << endl;
    }
};

class ElecEngine : public Engine {
public:
    void Status(int speed) override {
        cout << "Electric Engine is running on speed = " << speed << endl;
    }
};

class HybirdEngine : public Engine {
public:
    void Status(int speed) override {
        if(speed < 50) { cout << "Electric mode speed  "<<speed << endl; }
        else { cout << "Gas mode speed "<<speed << endl; }
    }
};

class Car {
private:
    Engine* activeEngine; 
    int speed;
    bool activated;

public:
    Car(Engine* en) : activeEngine(en), speed(0), activated(false) {}

    void start() {
        activated = true;
        cout << "Car is running." << endl;
    }

    void stop() {
        if(speed > 0) {
            cout << "Car is moving" << endl;
        } else {
            activated = false;
            cout << "The Car is stopped ." << endl;
        }
    }

    void accelerate() {
        if(activated) {
            speed += 20;
            activeEngine->Status(speed);
        } else {
            cout << "The Car is not running." << endl;
        }
    }

    void brake() {
        if(speed >= 20) {
            speed -= 20;
            activeEngine->Status(speed);
        } else {
            speed = 0;
            cout << "The Car is stopped" << endl;
        }
    }

    void setEngine(Engine* newEngine) {
        activeEngine = newEngine;
        cout << "Engine changed now" << endl;
    }
};

class Factory {
public:
    static Car* createCar(string type) {
        if(type == "gas") return new Car(new GasEngine());
        if(type == "electric") return new Car(new ElecEngine());
        if(type == "hybrid") return new Car(new HybirdEngine());
        return nullptr;
    }
};
int main() {
	
    ///Assumed Scenario will be :
    ///1.craete a car with gas engine and start it.
    ///2.Accelerate the car and then change the engine to hybrid.
    ///3.Accelerate the car again and then brake it twice and stop it.
    
	Car* Car1 = Factory::createCar("gas");
	Car1->start();
	
	Car1->accelerate();
	
	HybirdEngine newEngine;
	Car1->setEngine(&newEngine);
	
	Car1->accelerate();
	
	Car1->brake();
	Car1->brake();
	Car1->stop();
	
	
	delete Car1;
	
	return 0;
}