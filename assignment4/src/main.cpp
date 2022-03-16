#include <iostream>
#include "vector2.h"

int main(int, char **) {
    auto u = Vector2<int> (2, 3);
    auto v = Vector2<int> (-2, 1);
    auto w = Vector2<float> (-1.1f, -1.2f);
    auto p = Vector2<double> (-4.2, -1.37);

    std::cout << "u: " << u << " with type " << typeid(u).name() << std::endl;
    std::cout << "v: " << v << " with type " << typeid(v).name() << std::endl;
    std::cout << "w: " << w << " with type " << typeid(w).name() << std::endl;
    std::cout << "p: " << p << " with type " << typeid(p).name() << std::endl;

    auto upv = u + v;
    std::cout << "u + v: " << upv << " with type " << typeid(upv).name() << std::endl;

    auto upw = u + w;
    std::cout << "u + w: " << upw << " with type " << typeid(upw).name() << std::endl;

    auto wmp = w - p;
    std::cout << "w - p: " << wmp << " with type " << typeid(wmp).name() << std::endl;

    auto mulvli = 2*v;
    std::cout << "2*v: " << mulvli << " with type " << typeid(mulvli).name() << std::endl;

    auto mulvri = v*2;
    std::cout << "v*2: " << mulvri << " with type " << typeid(mulvri).name() << std::endl;

    auto mulvlf = 2.5*v;
    std::cout << "2.5*v: " << mulvlf << " with type " << typeid(mulvlf).name() << std::endl;

    auto divvi = v/2;
    std::cout << "v/2: " << divvi << " with type " << typeid(divvi).name() << std::endl;

    auto divvd = v/2.0;
    std::cout << "v/2.0: " << divvd << " with type " << typeid(divvd).name() << std::endl;

    u += v;
    std::cout << "u after u += v: " << u << " with type " << typeid(u).name() << std::endl;

    u -= v;
    std::cout << "u after u -= v: " << u << " with type " << typeid(u).name() << std::endl;

    auto udotv = u.dot(v);
    std::cout << "u.dot(v): "<< udotv << " with type " << typeid(udotv).name() << std::endl;

    auto udotp = u.dot(p);
    std::cout << "u.dot(p): "<< udotp << " with type " << typeid(udotp).name() << std::endl;

    auto ucrossv = u.cross(v);
    std::cout << "u.cross(v): "<< ucrossv << " with type " << typeid(ucrossv).name() << std::endl;

    auto pcrossw = p.cross(w);
    std::cout << "p.cross(w): "<< pcrossw << " with type " << typeid(pcrossw).name() << std::endl;

    auto uns = u.normSquared();
    std::cout << "u.normSquared(): "<< uns << " with type " << typeid(uns).name() << std::endl;

    auto pns = p.normSquared();
    std::cout << "p.normSquared(): "<< pns << " with type " << typeid(pns).name() << std::endl;

    auto un = u.norm();
    std::cout << "u.norm(): "<< un << " with type " << typeid(un).name() << std::endl;

    auto pn = p.norm();
    std::cout << "p.norm(): "<< pn << " with type " << typeid(pn).name() << std::endl;

    auto vnd = v.normalized();
    std::cout << "v.normalized(): "<< vnd << " with type " << typeid(vnd).name() << std::endl;

    auto wnd = w.normalized();
    std::cout << "w.normalized(): "<< wnd << " with type " << typeid(wnd).name() << std::endl;

    auto uo = u.orthogonal();
    std::cout << "u.orthogonal(): "<< uo << " with type " << typeid(uo).name() << std::endl;

    auto po = p.orthogonal();
    std::cout << "p.orthogonal(): "<< po << " with type " << typeid(po).name() << std::endl;

    v *= 2.2;
    std::cout << "v after v *= 2.2: " << v << " with type " << typeid(v).name() << std::endl;

    p *= 2.2;
    std::cout << "p after p *= 2.2: " << p << " with type " << typeid(p).name() << std::endl;

    v /= 2.2;
    std::cout << "v after v /= 2.2: " << v << " with type " << typeid(v).name() << std::endl;

    p /= 2.2;
    std::cout << "p after p /= 2.2: " << p << " with type " << typeid(p).name() << std::endl;

    std::cout << "And we can also index v as v[0] and v[1]: v[0]=" << v[0] << " and v[1]=" << v[1] << "." << std::endl;

    std::cout << "Please enter 2 integers to change the value of v: " << std::endl;
    std::cin >> v;
    std::cout << "v is now " << v << "." << std::endl;


}