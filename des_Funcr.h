#pragma once
#include"des_usrtr.h"
namespace des{
    inline namespace v1{
        //Max&Min
        template<typename T>T Max(T first, T end){
            return (first>=end)?first:end;
        }
        template<typename T, typename ...Args>T Max(T first,Args... arg){
            int other = Max(arg...);
            return (first>=other)?first:other;
        }
        template<typename T>T Max(Teis<T> p){
            int max=p[0];
            for(int i=0;i<p.getlengh();i++){max=(max>=p[i])?max:p[i];}
            return max;
        }
        template<typename T>T Min(T first, T end){
            return (first<=end)?first:end;
        }
        template<typename T, typename ...Args>T Min(T first,Args... arg){
            int other = Max(arg...);
            return (first<=other)?first:other;
        }
        template<typename T>T Min(Teis<T> p){
            int min=p[0];
            for(int i=0;i<p.getlengh();i++){min=(min<=p[i])?min:p[i];}
            return min;
        }
        
        //getInit()
        template<typename T>T getInit(T* val,T initval){
           T temp=*val;
           *val=initval;
           return temp;
        }

        //Pari()
        bool Pari(const int& val){
            return (val&1)^1; 
        }
    
        //range()
        template<typename T>Teis<T> range(T _begin,T _end,T _inx){
            Teis<T> Te;
            if(_begin<_end&&_inx>0){
                for(int i=_begin;i<_end;i+=_inx){
                    Te.add(i);
                }
            }else if(_begin>_end&&_inx<0){
                for(int i=_begin;i>_end;i+=_inx){
                    Te.add(i);
                }
            }
            return Te;
        }
    }
}
