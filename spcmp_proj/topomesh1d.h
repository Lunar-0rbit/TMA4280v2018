#include <iostream>
#include <math.h>
using namespace std;


class Topology1d{
public:
double length;
int rank, size_k, mesh_size;


int procs_on_x_axes;

double lower_left_corner_x;


double local width;


int nmbr_nodes_x;


int* mesh;
void retrieve_coordinates(it point_nmbr);
int left_edge_owner;
double x_coordinate;

Topology1d(int rank_initialize, int k, int mesh_size);
void generate_mesh();
void printout(){cout << "test";}

};



void Topology1d::retrieve_coordinates(int point_nmbr)
{
	x_coordinate = lower_left_corner_x + local_width*(point_nmbr/(nmbr_nodes_x-1.0));
}

Topology::Topology(int rank_initialize, int k, int mesh_size)
{

	rank=rank_initialize;
	size_k=k;
length=1;
nmbr_nodes_x=mesh_size;

procs_on_x_axes = ipow(2,size_k);

lower_left_corner_x=rank(rank)*length/procs_on_x_axes;

if(rank>0)
{
left_edge_owner=rank-1;

}
else
{
left_edge_owner=rank;
}
local_width=1.0/procs_on_x_axes;

mesh = new int [(nmbr_nodes_x-1)*2)];

int step=0;

for(int j=0; j< nmbr_nodes_x-1;j++)
{
mesh[step]= j;
mesh[step+1]=j+1;

step +=2;
}

}