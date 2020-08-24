//
//  uncstr.h
//  HomeworkVerify
//
//  Created by LegitMichel777 on 2020/8/3.
//  Copyright © 2020 LegitMichel777. All rights reserved.
//

#ifndef uncstr_h
#define uncstr_h

typedef long long ll;
using namespace std;
#include <vector>
unsigned char premsk(unsigned char x,int bits) { //removes the first x bits
    if (bits==0) return x;
    if (bits<0||bits>8) cerr<<"premsk bit error"<<endl;
    return x&((1<<(8-bits))-1);
}
class uncstr {
public:
    vector<string>errorlog;
    long cval(int index) const {
        if (index<0||index>=dt.size()) return -1; //out of bounds
        if (index<cvalcache.size()) return cvalcache[index];
        //find the very first 0
        int fir;
        for (fir=7;(dt[index][0]&(1<<fir))&&fir>=0;fir--);
        if (fir==-1||fir==6) return -2;
        long rturn=premsk(dt[index][0],7-fir);
        for (int i=1;i<dt[index].size();i++) {
            rturn<<=6;
            rturn|=premsk(dt[index][i],2);
        }
        return rturn;
    }
    size_t find(string s) {
        for (int i=0;i<(int)dt.size()-(int)s.size()+1;i++) {
            //does s match with index i...i+s.size()
            bool match=true;
            for (int j=i;j<i+s.size()&&match;j++) {
                if (cval(j)!=s[j-i]) match=false;
            }
            if (match) return i;
        }
        return string::npos;
    }
    size_t size() const {
        return dt.size();
    }
    vector<unsigned char>& operator[] (int ind) {
        return dt[ind];
    }
    uncstr substr(int beg,int len) {
        uncstr rturn;
        for (int i=beg;i<beg+len;i++) rturn.dt.push_back(dt[i]);
        // TODO: build on cval cache
        return rturn;
    }
    void make(string s) {
        *this=uncstr(s);
    }
    uncstr& operator+=(const uncstr& dis) {
        for (int i=0;i<dis.dt.size();i++) dt.push_back(dis.dt[i]);
        for (int i=0;i<dis.cvalcache.size();i++) cvalcache.push_back(dis.cvalcache[i]);
        // add cval values in
        return *this;
    }
    uncstr& operator+=(const string& dis) {
        //simplicity over speed. copies twice.
        *this+=uncstr(dis);
        return *this;
    }
    bool operator <(const uncstr& dis) const {
        for (int i=0;i< min(size(),dis.dt.size());i++) {
            ll comptmpa=cval(i),comptmpb=dis.cval(i);
            if (comptmpa<comptmpb) return true;
            else if (comptmpa>comptmpb) return false;
        }
        //all chars before are equal
        return size()<dis.size();
    }
    bool operator ==(const uncstr& a) const {
        if (size()!=a.size()) return false;
        for (int i=0;i<size();i++) for (int j=0;j<dt[i].size();j++) if (dt[i][j]!=a.dt[i][j]) return false;
        return true;
    }
    void clear() {
        dt.clear();
        cvalcache.clear();
    }
    void erase(int index) {
        dt.erase(dt.begin()+index);
        cvalcache.erase(cvalcache.begin()+index);
    }
    void replace(int index,string toput) {
        replace(index,uncstr(toput));
    }
    void replace(int index,uncstr toput) {
        erase(index);
        dt.insert(dt.begin()+index,toput.dt.begin(),toput.dt.end());
        cvalcache.insert(cvalcache.begin()+index,toput.cvalcache.begin(),toput.cvalcache.end());
    }
    string getAsciiStr() {
        string rturn;
        for (int i=0;i<dt.size();i++) {
            if (dt[i].size()==1) {
                if (cval(i)<128) {
                    rturn+=(char)dt[i][0];
                }
            }
        }
        return rturn;
    }
    string toS() {
        string rturn;
        for (int i=0;i<dt.size();i++) {
            for (int j=0;j<dt[i].size();j++) {
                rturn+=(char)dt[i][j];
            }
        }
        return rturn;
    }
    uncstr () { }
    uncstr (string s) {
        for (int i=0;i<s.size();) {
            int fir;
            vector<unsigned char>topsh{static_cast<unsigned char>(s[i])};
            for (fir=7;(s[i]&(1<<fir))&&fir>=0;fir--);
            if (fir==-1||fir==6) {
                errorlog.push_back("Invalid string! (FIR="+to_string(fir)+")");
                dt.clear();
                return;
            }
            int continuationBytes=(fir==7?0:6-fir);
            if (continuationBytes+i>=s.size()) {
                errorlog.push_back("Invalid string! (PARSERR)");
                dt.clear();
                return;
            }
            i++;
            for (int dest=i+continuationBytes-1;i<=dest;i++) {
                if ((s[i]&0xC0)!=0x80) {
                    errorlog.push_back("Invalid string! (CONTERR)");
                    dt.clear();
                    return;
                }
                topsh.push_back(s[i]);
            }
            dt.push_back(topsh);
        }
        // build the cval cache upon creation
        for (int i=0;i<dt.size();i++) {
            cvalcache.push_back(cval(i));
        }
    }
private:
    vector<vector<unsigned char>> dt;
    vector<long>cvalcache;
};

#endif /* uncstr_h */
