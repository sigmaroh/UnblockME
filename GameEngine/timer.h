
class timer
{
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;

public:
    timer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();
};
