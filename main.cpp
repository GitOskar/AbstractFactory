#include <iostream>
#include <string>

using namespace std;

class Engine {
protected:
    string fuel;
    double horsePower;
public:
virtual Engine* createEngine() = 0;
virtual ~Engine() {}
};

class GearBox {
protected:
    string type;
public:
virtual GearBox* createGearBox() = 0;
virtual ~GearBox() {};
};



class ComponentFactory
{
public:
    virtual Engine* createComponentEngine() = 0;
    virtual GearBox* createComponentGearBox() = 0;
    virtual ~ComponentFactory() {}
};

class EngineForBmw: public Engine
{
public:
    EngineForBmw()
    {
        fuel = "Benzine";
        horsePower = 150.0;
    }

    Engine * createEngine() override
    {
        return new EngineForBmw();
    }
};

class GearBoxForBmw: public GearBox
{
public:
    GearBoxForBmw()
    {
        type = "Manual";
    }

    GearBox * createGearBox() override
    {
        return new GearBoxForBmw();
    }
};

class BmwComponentFactory : public ComponentFactory
{
public:
    Engine* createComponentEngine() override
    {
        return new EngineForBmw();
    }

    GearBox * createComponentGearBox() override
    {
        return new GearBoxForBmw();
    }
};

class EngineForPorsche: public Engine
{
public:
    EngineForPorsche()
    {
        fuel = "Benzine";
        horsePower = 250.0;
    }

    Engine * createEngine() override
    {
        return new EngineForPorsche();
    }
};

class GearBoxForPorsche: public GearBox
{
public:
    GearBoxForPorsche()
    {
        type = "Automatic";
    }

    GearBox * createGearBox() override
    {
        return new GearBoxForPorsche();
    }
};

class PorscheComponentFactory : public ComponentFactory
{
public:
    Engine* createComponentEngine() override
    {
        return new EngineForPorsche();
    }

    GearBox * createComponentGearBox() override
    {
        return new GearBoxForPorsche();
    }
};

class Car
{
protected:
    Engine* engine;
    GearBox* gearBox;
    ComponentFactory* componentFactory;

    virtual void buildACar() = 0;
public:
    void startEngine()
    {
        cout << "Engine is starting" << endl;
    }

    void drive()
    {
        cout << "Driving" << endl;
    }
    virtual void exhaustSound() = 0;
    virtual ~Car() { }
};

class CarBmw: public Car
{
public:
    CarBmw(ComponentFactory* componentFactory)
    {
        this->componentFactory = componentFactory;
        buildACar();
    }

    void exhaustSound() override
    {
        cout << "Lututuututu\n";
    }

    ~CarBmw()
    {
        delete engine;
        delete gearBox;
        delete componentFactory;
    }
protected:
    void buildACar() override
    {
        engine = componentFactory->createComponentEngine();
        gearBox = componentFactory->createComponentGearBox();
    }
};

class CarPorsche: public Car
{
public:
    CarPorsche(ComponentFactory* componentFactory)
    {
        this->componentFactory = componentFactory;
        buildACar();
    }

    void exhaustSound() override
    {
        cout << "BrrrrrBrrrrrrrr\n";
    }

    ~CarPorsche()
    {
        delete engine;
        delete gearBox;
        delete componentFactory;
    }
protected:
    void buildACar() override
    {
        engine = componentFactory->createComponentEngine();
        gearBox = componentFactory->createComponentGearBox();
    }
};


class CarFactory {

public:

    Car* createCar(string band)
    {
        if (band == "BMW")
            return new CarBmw(new BmwComponentFactory());
        else if (band == "Porsche")
            return new CarPorsche(new PorscheComponentFactory());
        else
            return nullptr;
    }

};

int main()
{
    CarFactory* carFactory = new CarFactory();

    Car* bmw = carFactory->createCar("BMW");
    Car* porsche = carFactory->createCar("Porsche");

    bmw->startEngine();
    bmw->drive();
    bmw->exhaustSound();

    cout << "\n\n";

    porsche->startEngine();
    porsche->drive();
    porsche->exhaustSound();

    delete porsche;
    delete bmw;
    delete carFactory;

    return 0;
}
