//
// Created by MagieSmiley on 2017/12/20.
//


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
//#include <memory.h>

using namespace std;

//求 单源(仅一个src)的最短路径
/**
 *
 * @param graph
 * @param src
 * @param shortestPath
 * @param pre
 *
 * @param cur 最短路径上的(最后一个❤️)下标
 * @param shortestPath[cur] 从源点src到达最新生成的最短路径结点cur的cost总和
 * @param graph[cur][j] 节点cur与j之间的cost
 */
void Dijkstra(const vector<vector<int>>& graph, int src,
              vector<int>& shortestPath, vector<int>& pre) {
    int N = (int) graph.size();
    vector<bool> tickVec(N, false);//分配内存N 并 初始化为false
    shortestPath = graph[src];//记录当前最短路径(vector<int>类型)
    //将src加入集合tickVec
    tickVec[src] = true;
    shortestPath[src] = 0;//源点的cost为0
    int minPathValue;//最短路径值

    for (int cnt = 1; cnt < N; cnt++) {//将剩余的N-1个结点加入集合tickVec
        int cur = -1;//候选结点编号
        minPathValue = -1;;//最短路径值
        for (int j = 0; j < N; j++) {
            if (minPathValue < 0 || minPathValue > shortestPath[j]) {
                //若 (首次 || 后续遍历时，当前最短路径值 > 遍历结点j处的最短路径值)
                minPathValue = shortestPath[j];
                cur = j;//记录下候选结点。当循环结束后，cur的值就是最短路径上的最后一个❤️下标
            }
        }// 本次for循环后，得到最短路径值minPathValue && 最短路径上的最后一个下标
        tickVec[cur] = true;

        //更新shortestPath容器 ，并记录前驱❤️
        for (int j = 0; j < N; j++) {
            if (tickVec[j])//跳过所有当前生成的最短路径上的结点
                continue;

            //若当前j非最短路径上的节点
            if (shortestPath[j] > shortestPath[cur] + graph[cur][j]) {
                //若当前遍历结点的最短路径cost > 最新生成的最短路径结点的cost总和(shortestPath[cur])+ 节点cur与j之间的cost
                // 则更新shortestPath[j]， 并记录j结点的前驱(pre[j])为cur
                shortestPath[j] = shortestPath[cur] + graph[cur][j];
                pre[j] = cur;//记录前驱❤️
            }
        }
    }
}

void MinPath(int start, int end,
             const vector<int>& pre, vector<int>& path)
{
    path.push_back(end);
    int tempEnd = end;
    while (start != tempEnd){
        tempEnd = pre[tempEnd];
        path.push_back(tempEnd);//将每一个节点的前驱加入path，最后reverse一下
    }
    reverse(path.begin(), path.end());
}
