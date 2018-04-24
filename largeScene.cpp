//18446744073709551615 max 64 bit unsigned int
//size_t on 64 bit is the same as unsigned long long int but better and easier to write

class LargeScene {
  private:
    size_t cellSizeX; //size of every cell of the scene on the x axis
    size_t cellSizeY; //size of every cell of the scene on the y axis
    size_t cellNumX; //number of cells on the x axis
    size_t cellNumY; //number of cells on the y axis
    size_t positionCellSizeX; //position inside a cell on the x axis
    size_t positionCellSizeY; //position inside a cell on the y axis
    size_t positionCellNumX; //position on the cell grid on the x axis
    size_t positionCellNumY; //position on the cell grid on the y axis
  public:
    LargeScene(size_t cellSizeX, size_t cellSizeY, size_t cellNumX, size_t cellNumY, 
               size_t positionCellSizeX, size_t positionCellSizeY, size_t positionCellNumX, 
              size_t positionCellNumY);
    
};
