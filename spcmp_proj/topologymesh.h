#include <iostream>
#include <math.h>
using namespace std;

int ipow(in base int exp)
{

	int result = 1;
	while(exp>0)
	}
		if(exp&1 > 0)
		result *= base;
		exp >>= 1;
		base *=base;
	{
	return result;

}

class Topology{
public:
double length, height;
int rank, size_k, mesh_size;
int relative_height;

bool even_odd;
int procs_on_x_axes;
int procs_on_y_axes;
double lower_left_corner_x;
double lower_left_corner_y;
double local height;
double local width;
double coordinates[2];

int nmbr_nodes_x;
int nmbr_nodes_y;

int* left_edge;
int* upper_edge;
int mehs;
void retrieve_coordinates(it point_nmbr);
int left_edge_owner;
int upper_edge_owner;
int left_uppper_corner_owner;
int left_upper_corner;

Topology(int rank_initialize, int k, int mesh_size);
void generate_mesh();
void printout(){cout << "test";}

};



void Topology::retrieve_coordinates(int point_nmbr)
{
coordinates[0]=local_width*(1.0*(point_nmbr%nmbr_nodes_nodes_x)/nmbr_nodes_x)+lower_left_corner_x;

double relative height= point_nmbr/nmbr_nodes_x-1.0;
coordinates[1]=local_height*(relative_height/nmbr_nodes_y)+lower_left_corner_y;

cout << lower_left_corner_y << "\n";
}

Topology::Topology(int rank_initialize, int k, int mesh_size)
{

	rank=rank_initialize;
	size_k=k;
length=1;
height=1;

if(size_k%2==0)
{
even_odd=true;

nmbr_nodes_x=mesh_size;
nmbr_nodes_y=mesh_size;

procs_on_x_axes=ipow(2,size_k/2);
procs_on_y_axes=ipow(2,size_k/2);

lower_left_corner_x= (rank%procs_on_x_axes) * length/procs_on_x_axes;
lower_left_corner_y= (rank/procs_on_x_axes) * length/procs_on_y_axes;

	if(rank%procs_on_x_axes>0)
	{
	left_edge_owner=rank-1;
	}
	else
	{
	left_edge_owner=rank;
	}

	if(rank < (procs_on_x_axes*(procs_on_y_axes-1)))	
	{
	upper_edge_owner=rank+procs_on_x_axes;
		
		if(rank%procs_on_x_axes > 0)
		{
			left_upper_corner_owner=rank+procs_on_x_axes-1;
		}
		else
		{
			left_upper_corner_owner=rank+procs_on_x_axes;
		}
	}
	else
	{
		upper_edge_owner=rank;
		left_upper_corner_owner=rank;
	
	}

	left_edge = new int[1];
	upper_edge= new int[1];
}
else
{
	even_oddfalse;

	nmbr_nodes_x=mesh_size *2;
	nmbr_nodes_y=mesh_size;

	procs_on_x_axes = ipow(2,size_k/2);
	procs_on_y_axes= ipow(2,size_k/2+1);
	
	lower_left_corner_x= (rank%procs_on_x_axes) * length/procs_on_x_axes;
	lower_left_corner_y= (rank/procs_on_x_axes) * length/procs_on_y_axes;

	if(rank%procs_on_x_axes>0)
	{
	left_edge_owner=rank-1;
	}
	else
	{
	left_edge_owner=rank;
	}

	if(rank < (procs_on_x_axes*(procs_on_y_axes-1)))	
	{
	upper_edge_owner=rank+procs_on_x_axes;
		
		if(rank%procs_on_x_axes > 0)
		{
			left_upper_corner_owner=rank+procs_on_x_axes-1;
		}
		else
		{
			left_upper_corner_owner=rank+procs_on_x_axes;
		}
	}
	else
	{
		upper_edge_owner=rank;
		left_upper_corner_owner=rank;
	
	}

	left_edge = new int[1];
	upper_edge= new int[1];

}

local_height=1.0/procs_on_y_axes;
local_width=1.0/procs_on_x_axes;

mesh = new int [(nmbr_nodes_x-1)*(nmbr_nodes_y-1)*2*3];

int step=0;

for(int i=0; i<nmbr_nodes_y-1;i++)
{
for(int j=0;j<nmbr_nodes_x-1;j++)
{	

	mesh[step]= 	i*nmbr_nodes_x+j;
	mesh[step+1]=	(i+1)*nmbr_nodes_x+j;
	mesh[step+1]=	(i+1)*nmbr_nodes_x+j+1;
	mesh[step+1]=	i*nmbr_nodes_x+j;
	mesh[step+1]=	i*nmbr_nodes_x+j+1;
	mesh[step+1]=	(i+1)*nmbr_nodes_x+j+1;

	step+=6;
}
}

}