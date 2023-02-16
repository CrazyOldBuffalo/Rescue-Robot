
class Drive
{
private:
    Zumo32U4Motors motors;
public:
    void turnleft();
    void turnleft(int16_t leftval, int16_t rightval);
    void turnright();
    void turnright(int16_t leftval, int16_t rightval);
    void stop();
    void forward();
    void backward(); 
};