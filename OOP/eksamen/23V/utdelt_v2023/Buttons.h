#ifndef BUTTONS_HPP_G2DJXV35
#define BUTTONS_HPP_G2DJXV35

#include <AnimationWindow.h>
#include <widgets/Button.h>
#include <mutex>
#include "TileSelector.h"
#include "TilePool.h"
#include "Context.h"
#include "LevelLoader.h"
#include <functional>

static bool show_walkable_overlay = false;

class IncrementButton : public TDT4102::Button {
public:

    IncrementButton () : TDT4102::Button({110, 20}, 100, 40, "+") {
        setCallback(IncrementButton::callback);
    }

    ~IncrementButton() {}

    static void callback() {
        IncrementButton::ts->increment();
    }

    static void setTileSelector(TileSelector * const _ts) {
        while ( ! ts_lock.try_lock() ) { }

        ts = _ts;

        ts_lock.unlock();
    }

private:
    static TileSelector *ts;
    static std::mutex ts_lock;
};

TileSelector *IncrementButton::ts = nullptr;
std::mutex IncrementButton::ts_lock{};



class DecrementButton : public TDT4102::Button {
public:

    DecrementButton () : TDT4102::Button({20, 20}, 100, 40, "-") {
        setCallback(DecrementButton::callback);
    }

    void test() {
        ts->decrement();
    }

    ~DecrementButton() {}

    static void callback() {
        DecrementButton::ts->decrement();
    }

    static void setTileSelector(TileSelector * const _ts) {
        while ( ! ts_lock.try_lock() ) { }

        ts = _ts;

        ts_lock.unlock();
    }



private:
    static TileSelector *ts;
    static std::mutex ts_lock;
};

TileSelector *DecrementButton::ts = nullptr;
std::mutex DecrementButton::ts_lock{};


class SaveButton : public TDT4102::Button {
public:
    SaveButton() : TDT4102::Button({20, 258}, 100, 40, "Save")
    {
        setCallback(SaveButton::callback);
    }

    ~SaveButton() { }

    static void callback() {
        while ( ! level_lock.try_lock() ) { }

        try {
            LevelWriter::write("level_save", *level);
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }

        level_lock.unlock();

    }

    static void setLevel(const Level *lvl) {
        while ( ! level_lock.try_lock() ) { }

        level = lvl;

        level_lock.unlock();
    }


private:
    static const Level *level;
    static std::mutex level_lock;
};

const Level * SaveButton::level = nullptr;
std::mutex SaveButton::level_lock{};

class OverlayButton : public TDT4102::Button
{
public:
    OverlayButton() : TDT4102::Button(OverlayButton::render_location, 100, 40, "Overlay") {
        setCallback(OverlayButton::callback);
    }

    static void callback() {
        show_walkable_overlay = ! show_walkable_overlay;
    }

private:
    static constexpr TDT4102::Point render_location{125, 258};
};


struct TilePreview
{
    static constexpr TDT4102::Point render_location{46,65};
    static inline void render(TDT4102::AnimationWindow &window, std::optional<Tile> &tile)
    {
        if ( tile.has_value() ) {
            window.draw_image(render_location, *(tile.value().image), 128, 128);
        } else {
            window.draw_rectangle(render_location, 128,128, TDT4102::Color{200,200,200,255});
        }
    }
};


#endif /* end of include guard: BUTTONS_HPP_G2DJXV35 */

