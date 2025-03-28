#include <bits/stdc++.h>
using namespace std;

/**
 * 计算两个长度为 len 的字符串 s 和 t 在对应位置上不同的字符数。
 */
int countDifferences(const string &s, const string &t, int len) {
    int diff = 0;
    for(int i = 0; i < len; i++) {
        if(s[i] != t[i]) diff++;
        if(diff > 2) break; // 超过2个就可以提前停止
    }
    return diff;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入 n, m, l
    int n, m, l;
    cin >> n >> m >> l;

    // 读入电影情绪串 S
    string S;
    cin >> S;

    // 如果片段长度小于3，那么“最多允许2处不同”就意味着无论什么片段都能匹配上
    // 因为长度1最多只会有1处不同，长度2最多也就2处不同
    if(l < 3) {
        cout << m << "\n"; // 直接全部成功
        return 0;
    }

    // 三段的长度 w
    int w = l / 3;

    // --- 第一步：记录 S 中所有“长度为 w 的子串”出现的起始位置 ---
    // map:  key   = S中某个长度为w的子串
    //       value = 该子串在S中出现的所有起始下标
    unordered_map<string, vector<int>> posMap;
    posMap.reserve(n); // 预留空间（非必须）
    for(int i = 0; i + w <= n; i++){
        string subW = S.substr(i, w);
        posMap[subW].push_back(i);
    }

    // --- 第二步：依次读取每个改编片段，判断是否成功 ---
    int answer = 0; // 统计成功的片段数

    while(m--){
        string T;
        cin >> T;

        // 将改编片段 T 分成3段 s1, s2, s3
        // 注意：l/3 的结果若有小数会被截断，题解中要求 l <= min(100, n)，
        // 一般情况下 l 可以被3整除或接近整除，这里先照题解思路写。
        string s1 = T.substr(0,      w);
        string s2 = T.substr(w,      w);
        string s3 = T.substr(2 * w,  w);

        bool success = false; // 标记当前片段是否能成功匹配

        // （1）若 s1 在 S 中出现，则枚举它所有出现位置 st
        //     s1 对应 T 的前 w 个字符 => 在 S 中起点 st => S[st...(st+w-1)]
        //     整个 T 就对应 S[st...(st+l-1)]
        //     需保证 st + l <= n，否则越界
        if(!success && posMap.count(s1)){
            for(int st : posMap[s1]) {
                if(st + l <= n) {
                    // 检查完整长度l的子串是否与T差异不超过2
                    if(countDifferences(S.substr(st, l), T, l) <= 2) {
                        success = true;
                        break;
                    }
                }
            }
        }

        // （2）若还没成功，则看 s2
        //     s2 是 T 的中间 w 个字符 => 对应在 S 中的位置可能是 st => T 整体应对齐 st-w
        //     因为 T[0..w-1] 对应 S[st-w..st-1]
        if(!success && posMap.count(s2)){
            for(int st : posMap[s2]) {
                int startPos = st - w; // 对齐整段 T 的开头
                if(startPos >= 0 && startPos + l <= n) {
                    if(countDifferences(S.substr(startPos, l), T, l) <= 2) {
                        success = true;
                        break;
                    }
                }
            }
        }

        // （3）若还没成功，则看 s3
        //     s3 对应 T 的最后 w 个字符 => 在 S 中出现的位置 st => T 整体应对齐 st-2*w
        if(!success && posMap.count(s3)){
            for(int st : posMap[s3]) {
                int startPos = st - 2*w;
                if(startPos >= 0 && startPos + l <= n) {
                    if(countDifferences(S.substr(startPos, l), T, l) <= 2) {
                        success = true;
                        break;
                    }
                }
            }
        }

        // 如果三段检查完依旧 success == false，说明找不到合适的子串
        if(success) answer++;
    }

    // 输出改编成功的总数
    cout << answer << "\n";
    return 0;
}