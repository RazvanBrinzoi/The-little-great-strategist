The little courier must complete his tasks at work in an efficient matter.

He is responsible for delivering products to different citzens of Bucharest.

Like the rest of traffic participants he must chose a transport so he 

chooses the subway. Then from each station he must deliver the products at 
the client adress.

Considering he is low on time and the traffic keeps changing he requires help,
try to implement a software solution that automates this process.

Tasks:

1) conexion x,y -> Check if there is a street between two clients.

2) link x -> Prints the subway stations that have a direct link.

3) jam_tunnel x,y -> The way between two subway stations gets blocked.

4) jam_street x,y -> The way between two streets gets crowded.

5) add_way x,y,distance_value -> A way between two subway station gets constructed.

6) delete_way x,y -> Closes a way between two subway stations.

7) add_street x,y,distance_value -> A street between two clients gets added.

8) delete_street x,y -> Closes a way between two clients.

9) distance_street x,y -> Calculates the shortest time from x and y where x,y are
clients. Clients will be printed in the order in which the product was delivered 
starting from the first to the last.

10) distance_way x,y -> Calculates the shortest time to deliver the order to 
a certain station. The courier will choose the way with the shortest amount of 
time as the first client then he will deliver the rest of the products.

11) station_order total_value -> Prints the stations where sum of products delivered 
is greater or equal to the total_value.
