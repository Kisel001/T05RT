**Ray Tracing on CPU.**


To change scene, go to the pirt::rt::rt_win::rt_win() function in src/rt/rt_win.cpp file.


To adding shape, use:  
`Scene << new shape_name(...);`  
_Where shape_name is an avaliable shape (box, sphere, tor, csg::..., g3dm, etc.)._

To adding light, use:  
`Scene << new lights::point_light(cc, cl, cq, color, coord)`  
_Where cc, cl, cq is attenuation coefficients (for example, use {0.7, 0.1, 0.1]})._

To change camera, use:  
`Camera.SetLocAtUp(Pos, At);`

To render scene, press 'R'.
