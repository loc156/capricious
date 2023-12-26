#pragma once

#include"des_base_.h"
#include"des_key_library.h"

namespace des{
    inline namespace v1{
        //Drop class
        template<class T>class Drop {
        private:
            T* drop = NULL;
            int size_len = 0;
            int point = 0;
        public:
            Drop(int n) {
                drop = new T[n];
                size_len = n;
                for (int i = 0; i < n; i++) {
                    drop[i] = 0;
                }
            }
            int& getPostVar(int n) {
                return drop[n];
            }
            template<typename ...args>void setCote(T first, args... arg) {
                if (point < size_len) {
                    drop[point] = first;
                    point++;
                    setCote(arg...);
                }
                point = 0;
            }
            void setCote(T end) {
                if (point < size_len) {
                    drop[point] = end;
                }
            }
        };
        template<class T>class Teis:public base::_base_temLis_<T>{
        public:
            Teis(){}
            template<class Ty>Teis(des::base::_dis_key_<Ty> key){}
            template<typename ...Args>Teis(T var,Args... arg){
                base::_base_temLis_<T>::add(var,arg...); 
            }
            
        };
        //
        using pT = Teis<int>;
        using pF = Teis<float>;
        using pFD = Teis<double>;
        //

    }
}