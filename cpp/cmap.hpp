#include <vector>
#include <unordered_map>


class VBox {
public:
    VBox(int r1, int r2, int g1, int g2, int b1, int b2, std::vector<int>* histo) :
        r1(r1), r2(r2), g1(g1), g2(g2), b1(b1), b2(b2), histo(histo),
        avg_initialized(false), count_initialized(false) {}

    int volume() {
        int sub_r = r2 - r1;
        int sub_g = g2 - g1;
        int sub_b = b2 - b1;
        return (sub_r + 1) * (sub_g + 1) * (sub_b + 1);
    }

    VBox copy() {return VBox(r1, r2, g1, g2, b1, b2, histo);}
    color_t avg() {if (!avg_initialized) {init_avg();} return avg_cache;}
    bool contains(const color_t& pixel) {
        int rval = std::get<0>(pixel) >> RSHIFT;
        int gval = std::get<1>(pixel) >> RSHIFT;
        int bval = std::get<2>(pixel) >> RSHIFT;
        return rval >= r1 && rval <= r2 && 
               gval >= g1 && gval <= g2 &&
               bval >= b1 && bval <= b2;
    }
    int count() {if (!count_initialized) {init_count();} return count_cache;}

    void init_avg() {
        int ntot = 0;
        int mult = 1 << (8 - SIGBITS);
        double r_sum = 0;
        double g_sum = 0;
        double b_sum = 0;

        for (int i=r1; i<r2 + 1; i++) {
            for (int j=g1; j<g2 + 1; j++) {
                for (int k=b1; k<b2 + 1; k++) {
                    int histoindex = get_color_index(i, j, k);
                    int hval = (*histo)[histoindex];
                    ntot += hval;
                    r_sum += hval * (i + 0.5) * mult;
                    g_sum += hval * (j + 0.5) * mult;
                    b_sum += hval * (k + 0.5) * mult;
                }
            }
        }

        int r_avg;
        int g_avg;
        int b_avg;

        if (ntot > 0) {
            r_avg = int(r_sum / ntot);
            g_avg = int(g_sum / ntot);
            b_avg = int(b_sum / ntot);
        } else {
            r_avg = int(mult * (r1 + r2 + 1) / 2.0);
            g_avg = int(mult * (g1 + g2 + 1) / 2.0);
            b_avg = int(mult * (b1 + b2 + 1) / 2.0);
        }

        avg_cache = {r_avg, g_avg, b_avg};
        avg_initialized = true;
    }

    void init_count() {
        int npix = 0;
        for (int i=r1; i<r2 + 1; i++) {
            for (int j=g1; j<g2 + 1; j++) {
                for (int k=b1; k<b2 + 1; k++) {
                    int index = get_color_index(i, j, k);
                    npix += (*histo)[index];
                }
            }
        }
        count_cache = npix;
        count_initialized = true;
    }

    int r1;
    int r2;
    int g1;
    int g2;
    int b1;
    int b2;
    std::vector<int>* histo;

    color_t avg_cache;
    bool avg_initialized;
    int count_cache;
    bool count_initialized;
};

std::ostream &operator<<(std::ostream &os, VBox& box) {
    os << box.r1 << "-" << box.r2 << " " << box.g1 << "-" << box.g2 << " " << box.b1 << "-" << box.b2 << " Count: " << box.count() << " Volume: " << box.volume() << " Count * volume: " << uint64_t(box.count()) * uint64_t(box.volume());
    return os;
}


inline bool cmap_compare(const std::tuple<VBox, color_t>& a, const std::tuple<VBox, color_t>& b) {
    VBox box1 = std::get<0>(a);
    VBox box2 = std::get<0>(b);
    return uint64_t(box1.count()) * uint64_t(box1.volume()) < uint64_t(box2.count()) * uint64_t(box2.volume());
}


template<typename T, typename COMP>
class PQueue {
public:
    PQueue(COMP* sort_key) : sort_key(sort_key), contents({}), sorted(false) { }
    
    void sort() { 
        std::sort(contents.begin(), contents.end(), sort_key); 
        sorted = true;
    }

    void push(const T& o) {
        contents.push_back(o);
        sorted = false;
    }

    T pop() {
        if (!sorted) {
            sort();
        }
        
        T result = contents.back();
        contents.pop_back();
        return result;
    }

    int size() {return contents.size();}
    std::vector<T> get_contents() {return contents;}

private:
    std::vector<T> contents;
    COMP* sort_key;
    bool sorted;
};


class CMap {
public:
    CMap(decltype(cmap_compare)* compare_fn) : vboxes(compare_fn) { }

    std::vector<color_t> pallete() {
        std::vector<color_t> colors;
        for (auto& [vbox, avg_color] : vboxes.get_contents()) {
            colors.push_back(avg_color);
        }
        return colors;
    }

    void push(VBox&& box) {
        vboxes.push({box, box.avg()});
    }

    int size() {return vboxes.size();}

private:
    PQueue<std::tuple<VBox, color_t>, decltype(cmap_compare)> vboxes;
};

