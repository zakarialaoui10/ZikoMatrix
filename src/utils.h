template<typename T>
T _clamp(T x,T min,T max){
   return x<min?min:x>max?max:x; 
}
template<typename T>
T _lerp(T x,T min,T max){
    return (max-min)*x+min;
}
template<typename T>
T _norm(T x,T min,T max){
    return (x-min)/(max-min);
}
template<typename T>
T _map(T x,T a1,T b1,T a2,T b2){
    return _lerp(_norm(x,a1,b1),a2,b2);
}
template<typename T>
T _pow(T x,int n){
    T p=1;
    for(int i=0;i<n;i++)p*=x;
    return p;
}
 