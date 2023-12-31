#pragma once
namespace des{
    namespace base{
        template<typename T>class _dis_key_{
        private:
            struct _dis_key__ijurt__{};
            _dis_key__ijurt__* _imemr;
            T _ID_;
        public:
            _dis_key_(T _id_ = 0){
                _imemr = new _dis_key__ijurt__();
                _ID_=_id_;
            }
            ~_dis_key_() {
                delete _imemr;
            }
            bool operator==(const _dis_key_& diskey){
                return _imemr==diskey._imemr;
            }
            _dis_key_& operator=(_dis_key_ _K) {
                _imemr = _K._imemr;
                return *this;
            }
            _dis_key_& operator()(T _id) {
                _ID_ = _id;
                return *this;
            }
            T& GST() {
                return _ID_;
            }
        };
        template<typename T>class _base_temLis_{
        private:
            T* list=0;
            int point = 0;
            int lengh = 0;
        public:
            ~_base_temLis_() {
                delete[] list;
            }
            int getlengh(){
                return point;
            }
            T& operator[](int i){
                return list[i];
            }
            void add(){}
            void add(T var){
                if(point == lengh){
                    T* temp = list;
                    list = new T[lengh+5];
                    for(int i=0;i<lengh;i++){
                        list[i]=temp[i];
                    }
                    delete temp;
                    lengh+=5;
                }
                list[point]=var;
                point++;
            }
            template<typename ...Args>
            void add(T val,Args... arg){
                    add(val);
                    add(arg...);
            }
        };
    }
}
