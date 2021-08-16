# References and Sources

This is a list of references and sources I've used while working on this project.
It's intended to be complete, but it's possible that I've missed a references here
or there. There is often also documentation in the code where I've used a specific
algorithm or technique.

## Axis-Aligned Bounding Box "Slab Method" for Intersections

This is implemented in `spatial/BVHBoundingNode.cpp`'s `RayIntersectsBounds()`
function. It's an efficient method for checking ray-box intersections for
axis-aligned boxes.

I learned about this method from three webpages/papers:
- [https://tavianator.com/2011/ray_box.html](https://tavianator.com/2011/ray_box.html)
- [www.jcgt.org/published/0007/03/04/paper_lowres.pdf](www.jcgt.org/published/0007/03/04/paper_lowres.pdf)
- [https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection)

## Tone Mapping, HDR, and Bloom

This presentation was very helpful for learning about the concepts and about
some particular tone maps:
[https://download.nvidia.com/developer/presentations/2004/6800_Leagues/6800_Leagues_HDR.pdf](https://download.nvidia.com/developer/presentations/2004/6800_Leagues/6800_Leagues_HDR.pdf).