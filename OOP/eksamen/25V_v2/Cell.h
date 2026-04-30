#ifndef CELL_H_OPO19HTU
#define CELL_H_OPO19HTU

#include "AnimationWindow.h"
#include <optional>
class Grid;

class CellBehavior;

enum class CellType { NONE = 0, SOIL = 1, SNOW = 2, ICE = 3, FUEL = 4, WATER = 5, NUM_CELL_TYPES };

bool isValidCellType(CellType index);

struct IgnitionData {
  bool willIgnite = false;
  bool willExtinguish = false;
  bool ignited = false;
};

struct FluidData {
  double content;
};

struct Cell {
  CellType type;
  IgnitionData ignitionData;
  float temperature = 10.0f;
  FluidData fluidData;

  operator bool() const {
    return isValidCellType(type);
  }

  double fluidContent() const;
  void reset();

  CellBehavior *getBehavior() const;

  CellBehavior *operator->();
};

class CellBehavior {
public:
    virtual void precompute( [[maybe_unused]] const Grid &g,
    [[maybe_unused]] int x,
    [[maybe_unused]] int y) {}

    virtual void interact(Grid &g, int x, int y) = 0;

    virtual CellType getCellType() const;

    virtual void update(Cell &instance);

    virtual void init([[maybe_unused]] Cell &instance) {};

    virtual bool isMovable();

    virtual bool isSlick();

    virtual bool isFluid();

    virtual void draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height);
};
class NoOpCell : public CellBehavior {
public:

    virtual ~NoOpCell() {}

    void interact(Grid &g, int x, int y) override;

    CellType getCellType() const override;

    void draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height) override;
};

class Snow : public CellBehavior
{
public:
  virtual ~Snow() {}

  bool isMovable() override;

  bool isSlick() override;

  void init(Cell &instance) override;

  void interact(Grid &g, int x, int y) override;

  static std::optional<TDT4102::Image> texture;

  void draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height) override;
};


class Soil : public CellBehavior
{
public:

  virtual ~Soil() {}

  bool isMovable() override;

  bool isSlick() override;

  void interact(Grid &g, int x, int y) override;

  static std::optional<TDT4102::Image> texture;

  void draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height) override;
};


class Ice : public CellBehavior
{
public:
  virtual ~Ice() {}

  bool isMovable() override;

  bool isSlick() override;

  void init(Cell &instance) override;

  void interact(Grid &g, int x, int y) override;

  void draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height) override;
};

class Ignitable
{
public:
  virtual ~Ignitable();

  virtual void ignite(Cell &instance) = 0;
  virtual void extinguish(Cell &instance) = 0;

  virtual bool isIgnited(Cell &instance) = 0;
};

class Water : public CellBehavior
{
public:
    virtual ~Water() {}

    bool isMovable() override {
      return false;
    }

    void interact(Grid &g, int x, int y) override;

    CellType getCellType() const override;

    bool isFluid() override;

    void init(Cell &instance) override;

    void draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height) override;

    bool isValidDistributionCandidate(const Grid &g, int x, int y);

    static constexpr double capacity = 1.0;

    double content = 1.0;

  // Right, Up, Left, Down
  static constexpr std::size_t DIR_R = 0, DIR_U = 1, DIR_L = 2, DIR_D = 3;
  // Right, Top, Left, Bottom
  double distribution[4] = {0.0};
};

class Fuel : public CellBehavior, public Ignitable {
public:
    virtual ~Fuel() {}

    void ignite(Cell &instance) override;

    void init(Cell &instance) override;

    void extinguish(Cell &instance) override;

    bool isIgnited(Cell &instance) override;

    void interact(Grid &g, int x, int y) override;

    static std::optional<TDT4102::Image> fireTexture;

    void update(Cell &instance) override;

    void draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height) override;
};

class CellInfo {
public:
  

  static std::unordered_map<CellType, std::unique_ptr<CellBehavior>> cellTypes;

  static std::unordered_map<CellType, std::string> cellTypeNames;

  static void registerCellTypes();

  static std::unique_ptr<CellBehavior> noOpType;

  static CellBehavior *getCellBehavior(CellType type);
};


bool isCellValid(const Cell &c);

void printSimCapabilities();



#endif /* end of include guard: CELL_H_OPO19HTU */
