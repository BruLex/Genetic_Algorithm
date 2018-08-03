#ifndef GENERIC_H
#define GENERIC_H

#include <cmath>
#include <ctime>

#define CNT_GEN 38
#define GEN_SIZE 8
#define GEN_SELECTION 0.75
#define GEN_MUTATION 0.01

class Generic{
private:
    bool individ[GEN_SIZE];
    int x;
    double Fx;
    double normFx;
    double proz=0;

    void take_binary() {
        int k = 128;
        for(int i = 0;i < GEN_SIZE;i++){
            individ[i] = bool(x&k);
            k = k >> 1;
        }
    }

    double funcFx(int x){ return sin(x*M_PI/256); }
public:
    Generic(){
        x = rand() % 255;
        take_binary();
        Fx = funcFx(x);
    }


    int get_x(){ return x; }
    int set_x(int genX){
        x = genX;
        take_binary();
        Fx = funcFx(x);
    }

    double get_Fx(){ return Fx; }

    double get_normFx(){ return normFx; }

    double set_normFx(double normFx){ this->normFx = normFx; }

    double get_proz(){ return proz; }

    double set_proz(double proz){ return this->proz = proz; }

    bool get_individ_for_pos(int pos){
        if(pos >= 0 && pos < GEN_SIZE){
            return individ[pos];
        }else return -1;
    }

    void copyGen(Generic gen){
        x = gen.get_x();
        Fx = gen.get_Fx();
        normFx = gen.get_normFx();
        proz = gen.get_proz();
        take_binary();
    }

};



#endif // GENERIC_H
