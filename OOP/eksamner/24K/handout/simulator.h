#pragma once

#include "std_lib_facilities.h"
#include <chrono>
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "Table.h"


constexpr int WINDOW_OFFSET = 50;
constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 800;
constexpr int DASHBOARD_SIZE = 50;
constexpr int SPEED_SCALE = 3;
constexpr int MAX_HITS = 5;
constexpr double PENALTY = 5000.0;


struct Map
{
    double distance;
    double shootingPosition;
};


enum State
{
    SKIING,
    SHOOTING,
    FINISHED
};


class Target
{
public:
    void hit();
    void draw(AnimationWindow *window, TDT4102::Point position, int size);
    int getHits();

private:
    int hits = 0;
};


class Stopwatch
{
public:
    void toggleWatch();
    std::chrono::duration<int64_t, std::nano> getTime();

    string timeToString(std::chrono::duration<int64_t, std::nano> clock);
    string millisecondsToString(int time);
    int stringToMilliseconds(string time);

private:
    vector<std::chrono::time_point<std::chrono::steady_clock>> timeEvents;
};


class Gun
{
public:

  Gun() = default;

  Gun(const Gun &) = default;
  Gun(Gun &&) = default;
  Gun &operator=(const Gun &) = default;
  Gun &operator=(Gun &&) = default;

  bool isLoaded();

  bool shoot(double accuracy);

  bool load(double operatorSpeed);

  int getAmmo() const;

private:
  int ammo = 5;
  bool loaded = true;
  int loading = 0;

};


class Skier
{
public:
    Skier(string name, double speed);
    virtual ~Skier() = default;

    int getShots();
    virtual void shoot() = 0;
    double getPosition();
    string getName();

    virtual void updatePosition(Map &map) = 0;

    State state = SKIING;
    Target target;

protected:
    std::string name;
    double speed;
    double position = 0;

    Gun gun{};
};


class NPC : public Skier
{
public:
    NPC(string name, double accuracy, double speed, double loadingTime);
    virtual ~NPC() = default;

    void shoot() override;
    void updatePosition(Map &map) override;

private:
    double accuracy;
    double loadingTime;
};


class Simulator;


class ToggleButton : public Button
{
public:
    ToggleButton ();
    ~ToggleButton () = default;

    void callback();
    static void setSimulator(Simulator* const _sim);

private:
    static Simulator *sim;
};


class Simulator
{
public:
    Simulator();
    void run();

// Remove this part to make everything public if you
// did not manage to complete task T1
// REMOVE
private:
// REMOVE

    void updateState();
    void updateTable();

    bool checkIfDone();


    TDT4102::Point calculateSkierPosition(TDT4102::Point centerPoint, Skier &skier, int radius);

    string finaliseResult(vector<TableData<string>> &row);

    void drawRace(TDT4102::Point centerPoint);
    void drawBackground();
    void drawTable(TDT4102::Point topLeftCorner);
    void drawTargets(TDT4102::Point centerPoint, int outerRadius);

    void placeImages(TDT4102::Point centerPoint, int innerRadius, int outerRadius, int size);
    void drawSkiers(TDT4102::Point centerPoint, int innerRadius, int outerRadius, int skierSize);

    Map map;

    AnimationWindow window;
    unique_ptr<Table> table;
    vector<shared_ptr<Skier>> skiers;

    bool running = false;
    unique_ptr<Stopwatch> watch;

// TASK: T1
// Give the ToggleButton class access to
// private members of the Simulator class.
// BEGIN: T1
#define START_BUTTON_NO_ACCESS_TO_RUNNING_AND_WATCH
// END: T1
};
