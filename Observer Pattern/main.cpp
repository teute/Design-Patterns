#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Observer;

class Observable
{
public:
    virtual void addObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notifyObservers() = 0;
};

class Observer
{
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class DisplayElement
{
public:
    virtual void display() = 0;
};

class WeatherData : public Observable
{
public:
    WeatherData() {
        temperature = 0.0f;
        humidity = 0.0f;
        pressure = 0.0f;
    }

    virtual ~WeatherData() {}

    void addObserver(Observer* o) {
        if (o != nullptr) {
            observers.push_back(o);
            //cout << "Added observer (" << observers.size() << ")" << endl;
        }
    }

    void removeObserver(Observer* o) {
        if (o != nullptr) {
            for (vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) {
                if (*it == o) {
                    observers.erase(it);
                    //cout << "Removed observer (" << observers.size() << ")" << endl;
                    break;
                }
            }
            //observers.erase(remove(observers.begin(), observers.end(), o), observers.end);
        }
    }

    void notifyObservers() {
        for (vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) {
            (*it)->update(temperature, humidity, pressure);
        }
    }

    void measurementsChanged() {
        notifyObservers();
    }

    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }

private:
    vector<Observer*> observers;
    float temperature;
    float humidity;
    float pressure;
};

class CurrentConditionsDisplay : public Observer, DisplayElement
{
public:
    CurrentConditionsDisplay(Observable* o) {
        weatherData = o;

        if (weatherData != nullptr) {
            weatherData->addObserver(this);
        }
    }

    void update(float temp, float humidity, float pressure) {
        temperature = temp;
        this->humidity = humidity;
        display();
    }

    void display() {
        cout << "Current conditions: " << temperature << "F degrees and " << humidity << "% humidity" << endl;
    }

private:
    float temperature;
    float humidity;
    Observable* weatherData;
};

class SmartWatchDisplay : public Observer, DisplayElement
{
public:
    SmartWatchDisplay(Observable* o) {
        weatherData = o;

        if (weatherData != nullptr) {
            weatherData->addObserver(this);
        }
    }

    void update(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        display();
    }

    void display() {
        cout << temperature << "F , " << humidity << "% , " << pressure << "mb" << endl;
    }

private:
    float temperature;
    float humidity;
    float pressure;
    Observable* weatherData;
};

class HeatIndexDisplay : public Observer, DisplayElement
{
public:
    HeatIndexDisplay(Observable* o) {
        weatherData = o;

        if (weatherData != nullptr) {
            weatherData->addObserver(this);
        }
    }

    void update(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display() {
        cout << "Heat index is " << computeHeatIndex(temperature, humidity) << endl;
    }

private:
    float temperature;
    float humidity;
    Observable* weatherData;

    float computeHeatIndex(float t, float rh) {
        float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) +
            (0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) +
            (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
            (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
            (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
            (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
            0.000000000843296 * (t * t * rh * rh * rh)) -
            (0.0000000000481975 * (t * t * t * rh * rh * rh)));
        return index;
    }
};

int main()
{
    WeatherData* weatherData = new WeatherData();

    CurrentConditionsDisplay currentDisplay(weatherData);
    SmartWatchDisplay smartDisplay(weatherData);
    HeatIndexDisplay heatIndexDisplay(weatherData);

    weatherData->setMeasurements(80.0f, 65.0f, 30.4f);
    weatherData->setMeasurements(82.0f, 70.0f, 29.2f);
    weatherData->removeObserver(&currentDisplay);
    weatherData->setMeasurements(78.0f, 90.0f, 29.2f);

    delete weatherData;

    return 0;
}
