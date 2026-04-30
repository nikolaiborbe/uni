#include "simulator.h"


// ------------------------------
// -------- Stopwatch -----------
// ------------------------------
void Stopwatch::toggleWatch()
{
   timeEvents.push_back(std::chrono::steady_clock::now());
}


std::chrono::duration<int64_t, std::nano> Stopwatch::getTime()
{
    std::chrono::duration<int64_t, std::nano> time = std::chrono::steady_clock::now() - std::chrono::steady_clock::now();

    if (timeEvents.size() > 1)
    {
        for (std::size_t i=0; i < timeEvents.size()-1; i+=2)
        {
            time += (timeEvents[i+1] - timeEvents[i]);
        }
    }

    if (timeEvents.size() % 2 == 1)
    {
        time += std::chrono::steady_clock::now() - timeEvents[timeEvents.size()-1];
    }

    return time;
}


// TASK: T7
// Convert the integer timeInMilliseconds to a string on the form
// "minutes:seconds:milliseconds"
string Stopwatch::millisecondsToString(int timeInMilliseconds)
{
// BEGIN: T7
    int min = std::floor(timeInMilliseconds/1000/60);
    int sec = std::floor((timeInMilliseconds - min*60*1000)/1000);
    int ms = timeInMilliseconds - min*60*1000 - sec*1000;
    return to_string(min) + "." + to_string(sec) + "." + to_string(ms);
// END: T7
}


string Stopwatch::timeToString(std::chrono::duration<int64_t, std::nano> clock)
{
    auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(clock).count();
    string s = to_string(milli);
    int time = stoi(s);

    return millisecondsToString(time);
}


// TASK: T8
// Convert the string time, which is on the form
// "minutes.seconds.milliseconds" to an integer
// representing the time in milliseconds.
int Stopwatch::stringToMilliseconds(string time)
{
// BEGIN: T8
    string word{};
    std::array<int, 3> times{};
    uint8_t current_index = 0;
    for (size_t i{}; i < time.size(); ++i) {
        if (time[i] != '.')
            word.push_back(time[i]);
        else {
            times[current_index] = stoi(word);
            ++current_index;
            word = "";
        }
    }

    times[current_index] = stoi(word); // add the last time.

    int minutes = times[0];
    int seconds = times[1];
    int ms      = times[2];

    int tot_ms = minutes*60*1000 + seconds*1000 + ms;

    return tot_ms;
// END: T8
}


// TASK: T2
// Increment the local variable hits.
void Target::hit()
{
// BEGIN: T2
    ++hits;
// END: T2
}


int Target::getHits() { return hits; }


// Draws a shooting target for the skier.
void Target::draw(AnimationWindow *window, TDT4102::Point position, int size)
{
    int height = static_cast<int>(30 * size);
    int width = static_cast<int>(60 * size);
    window->draw_rectangle(position, width, height, Color::white, Color::black);

    for (int i=0; i<MAX_HITS; i++)
    {
        TDT4102::Point placement = 
        {
            position.x + static_cast<int>(width / 10) + static_cast<int>(width / MAX_HITS * i),
            position.y + static_cast<int>(height / 2)
        };
        if (i < hits)
        {
            window->draw_circle(placement, 3 * size, Color::white, Color::black);
        } else {
            window->draw_circle(placement, 3 * size, Color::black);
        }
    }
}


bool Gun::shoot(double accuracy)
{
    ammo--;
    loaded = false;
    loading = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution;
    bool hit = distribution(gen) < accuracy;

    return hit;
}


bool Gun::load(double operatorSpeed)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(operatorSpeed, 1);
    loading += static_cast<int>(distribution(gen) * SPEED_SCALE);

    if (loading > 250) loaded = true;

    return isLoaded();
}


int Gun::getAmmo() const { return ammo; }


bool Gun::isLoaded() { return loaded; }


Skier::Skier(string name, double speed)
    : name{name},
    speed{speed}
{}


string Skier::getName() { return name; }


int Skier::getShots() { return gun.getAmmo(); }


double Skier::getPosition() { return position; }


NPC::NPC(string name, double accuracy, double speed, double loadingTime)
    : Skier(name, speed), accuracy{accuracy}, loadingTime{loadingTime}
{}


void NPC::shoot()
{
    if ( gun.isLoaded() )
    {
        bool hit = gun.shoot(accuracy);

        if ( hit ) target.hit();
    } else {
        if ( gun.getAmmo() > 0 ) {
            gun.load(loadingTime);
            return;
        } else {
            state = SKIING;
        }
    }
}


void NPC::updatePosition(Map &map)
{
    if (state == SHOOTING) { return; }
    if (state == FINISHED) { return; }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(speed, 1);
    double movement = distribution(gen);

    double newPosition = position + movement;


    if (newPosition > map.distance)
    {
        position = map.distance;
        state = FINISHED;
    } else if (newPosition > map.shootingPosition && gun.getAmmo() > 0) {
        position = map.shootingPosition;
        state = SHOOTING;
    } else {
        position += movement * SPEED_SCALE;
    }
}


// ----------------------------------
// ------ Simulation ----------------
// ----------------------------------
Simulator::Simulator()
    : window(WINDOW_OFFSET, WINDOW_OFFSET, WINDOW_WIDTH, WINDOW_HEIGHT, "Biathlon")
{
    map = {25000, 25000 / 2};
    this->watch = make_unique<Stopwatch>();
    this->table = make_unique<Table>();

    skiers.push_back(make_shared<NPC>("Alexander", 0.87, 7.6, 3.7));
    skiers.push_back(make_shared<NPC>("Therese", 0.85, 7.8, 5.1));
    skiers.push_back(make_shared<NPC>("Petter", 0.75, 8.1, 5.5));
    skiers.push_back(make_shared<NPC>("Kari", 0.93, 7.3, 8.9));
    skiers.push_back(make_shared<NPC>("Marit", 0.71, 7.5, 6.0));

#ifndef ADD_ROW_NOT_IMPLEMENTED
    for (auto skier : skiers)
    {
        vector<TableData<string>> row;
        row.push_back({"Name", skier->getName()});
        row.push_back({"Time", watch->timeToString(watch->getTime())});
        row.push_back({"Hits", to_string(skier->target.getHits())});
        row.push_back({"Result", ""});

        table->addRow(row);
    }
#endif
}


// TASK: T9
// Use previously implemented functions to calculate the result of
// the skier based on time and hits.
string Simulator::finaliseResult(vector<TableData<string>> &row)
{
// BEGIN: T9
    int PENALTY_FACTOR = static_cast<int>(PENALTY / SPEED_SCALE);
    int hits_index = table->getColumnIndexInRow("Hits",row); 
    if (hits_index == -1)
        return "Hits missing";

    int time_index = table->getColumnIndexInRow("Time", row);
    if (time_index == -1)
        return "Time missing";

    int ms_time = watch->stringToMilliseconds(row.at(time_index).value);
    int hits = stoi(row.at(hits_index).value);
    int missing = MAX_HITS - hits;

    int new_time = missing*PENALTY_FACTOR + ms_time;

    return watch->millisecondsToString(new_time);
// END: T9
}


// Draws shooting targets for all the skiers at the left of the map
// next to the shooting icon.
void Simulator::drawTargets(TDT4102::Point centerPoint, int outerRadius)
{
    int targetSpacing = 45;
    for (std::size_t i=0; i < skiers.size(); i++)
    {
        if (skiers[i]->state == SHOOTING || skiers[i]->getShots() == 0)
        {
            TDT4102::Point position =
            {
                centerPoint.x - outerRadius - 100,
                centerPoint.y + 80 - targetSpacing * static_cast<int>(i)
            };
            
            skiers[i]->target.draw(&window, position, 1);
        }
    }
}


// TASK: T3
// Use the local window variable in Simulator
// and place two flags and one crosshair at the
// given locations. The .png files can be found in
// the images folder.
void Simulator::placeImages(TDT4102::Point centerPoint,
                                int innerRadius, int outerRadius, int size)
{
// BEGIN: T3
    TDT4102::Point crosshairPosition = 
    {
        centerPoint.x - outerRadius - 30,
        centerPoint.y - 12
    };
    TDT4102::Point flagPosLeft = 
    {
        centerPoint.x + innerRadius - 30,
        centerPoint.y - 12
    };
    TDT4102::Point flagPosRight = 
    {
        centerPoint.x + outerRadius + 10,
        centerPoint.y - 12
    };
    TDT4102::Image flag_img{"images/race.png"};
    TDT4102::Image crosshair_img{"images/crosshair.png"};
    window.draw_image(flagPosLeft, flag_img, size, size);
    window.draw_image(flagPosRight, flag_img, size, size);
    window.draw_image(crosshairPosition, crosshair_img, size, size);
// END: T3
}


// TASK: T4
// Calculate the position of the skier.
TDT4102::Point Simulator::calculateSkierPosition(TDT4102::Point centerPoint,
                                                    Skier &skier, int radius)
{
// BEGIN: T4
    double theta = 2*M_PI*skier.getPosition()/map.distance;

    int x_new = centerPoint.x + radius*std::cos(theta);
    int y_new = centerPoint.y + radius*std::sin(theta);

    TDT4102::Point new_point {x_new, y_new};
    return new_point;
    // END: T4
}


void Simulator::drawSkiers(TDT4102::Point centerPoint,
                            int innerRadius, int outerRadius, int skierSize)
{
    int lane_size = (outerRadius - innerRadius) / static_cast<int>(skiers.size());
    int lane = lane_size / 2;
    for (auto skier : skiers)
    {
        auto radius = innerRadius + lane;
        auto position = calculateSkierPosition(centerPoint, *skier, radius);

        window.draw_circle(position, skierSize);

        lane += lane_size;
    }
}


void Simulator::drawRace(TDT4102::Point centerPoint)
{
    constexpr int innerRadius = 100;
    constexpr int outerRadius = 150;
    window.draw_arc(centerPoint, innerRadius, innerRadius, 0, 360);
    window.draw_arc(centerPoint, outerRadius, outerRadius, 0, 360);

    placeImages(centerPoint, innerRadius, outerRadius, 25);
    drawSkiers(centerPoint, innerRadius, outerRadius, 4);
    drawTargets(centerPoint, outerRadius);
}


void Simulator::drawTable(TDT4102::Point topLeftCorner)
{
    table->draw(window, 200, 600, topLeftCorner);
}


void Simulator::drawBackground()
{
    window.draw_rectangle({0, DASHBOARD_SIZE},
                        WINDOW_WIDTH, WINDOW_HEIGHT - DASHBOARD_SIZE,
                        Color::light_gray, Color::black);
}


void Simulator::updateState()
{
    for (auto skier : skiers)
    {
        if (skier->state == SKIING)
        {
            skier->updatePosition(map);
        } else if (skier->state == SHOOTING) {
            skier->shoot();
        }
    }
}


void Simulator::updateTable()
{
#ifndef GET_INDEX_NOT_IMPLEMENTED
    for (std::size_t i=0; i<skiers.size(); i++)
    {
        vector<TableData<string>> row = table->getRow<string>(i);
        for (auto skier : skiers)
        {
            int index = table->getColumnIndexInRow("Name", row);

            // Name is used as primary-key
            if (index < 0) { return; }

            std::size_t index_us = static_cast<std::size_t>(index);

            if (skier->getName() == row[index_us].value)
            {
                if (skier->state == FINISHED)
                {
                    index = table->getColumnIndexInRow("Result", row);
                    if (index < 0) { continue; }
                    index_us = static_cast<std::size_t>(index);

                    if (row[index_us].value == "")
                    {
                        table->updateValue(i, index_us, finaliseResult(row));
                    }
                } else {
                    index = table->getColumnIndexInRow("Time", row);
                    if (index >= 0)
                    {
                        index_us = static_cast<std::size_t>(index);
                        table->updateValue(i, index_us, watch->timeToString(watch->getTime()));
                    }

                    index = table->getColumnIndexInRow("Hits", row);
                    if (index >= 0)
                    {
                        index_us = static_cast<std::size_t>(index);
                        table->updateValue(i, index_us, to_string(skier->target.getHits()));
                    }
                }
                break;
            }
        }
    }
#endif
}


bool Simulator::checkIfDone()
{
    for (auto skier : skiers)
    {
        if (skier->state != FINISHED) return false;
    }
    return true;
}


void Simulator::run()
{
    ToggleButton toggleButton{};
    ToggleButton::setSimulator(this);
    window.add(toggleButton);

    while(!window.should_close())
    {
        drawBackground();
        if (running)
        {
            updateState();
            updateTable();
            if (checkIfDone())
            {
                table->storeTable("race.txt");
            }
        }
        drawRace({WINDOW_WIDTH / 2, DASHBOARD_SIZE + 200});
        drawTable({WINDOW_WIDTH / 5, DASHBOARD_SIZE + 400});

        window.next_frame();
    }
}


// ---------------------------------
// -------------- GUI --------------
// ---------------------------------
ToggleButton::ToggleButton() : Button({20, 5}, 200, 50, "Start")
{
    setCallback(bind(&ToggleButton::callback, this));
    setLabelColor(Color::sea_shell);
    setButtonColor(Color::sea_green);
    setButtonColorHover(Color::gray);
    setButtonColorActive(Color::gray);
}


void ToggleButton::callback()
{
#ifndef START_BUTTON_NO_ACCESS_TO_RUNNING_AND_WATCH
    sim->running = !sim->running;
    sim->watch->toggleWatch();
    if (sim->running)
    {
        setButtonColor(Color::brown);
        setLabel("Stop");
    } else {
        setButtonColor(Color::sea_green);
        setLabel("Start");
    }
#endif
}


void ToggleButton::setSimulator(Simulator* const _sim)
{
    sim = _sim;
}


Simulator *ToggleButton::sim = nullptr;
