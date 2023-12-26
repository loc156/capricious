#pragma once

#include<iostream>
#include<Windows.h>
#include"des_usrtr.h"

namespace des{
    inline namespace v1{
        //Mprint
        class Mprint{
        public:
            Mprint& operator()(_KEY_ _K) {
                if (_K == ENPTR) for (int i = 0; i < ENPTR.GST(); i++) std::cout << "\n";
                else if (_K == SLEEP) Sleep(SLEEP.GST());
                return *this;
            }
            template<typename T>
            Mprint& operator()(T val) {
                std::cout<<val;
                return *this;
            }
            template<typename Ty1,typename... Ty2>
            Mprint& operator()(Ty1 val,Ty2... arg) {
                (*this)(val);
                (*this)(arg...);
                return *this;
            }
        };
        Mprint tprint;
        template<typename T>std::ostream& operator<<(std::ostream& out,Teis<T>& te){
            int len=te.getlengh();
            std::cout<<"("<<te[0];
            for(int i=1;i<len;i++){
                std::cout<<","<<te[i];
            }
            std::cout<<")";
            return out;
        }

        //IVal class
        template<typename T>
        class IVal{
        private:
            T val;
        public:
            IVal(){std::cin>>val;}
            T operator()(){
                return val;
            }
        };
        template<typename T>

        T getInput(){
            int temp;
            std::cin>>temp;
            return temp;
        }

        //...
    }
}