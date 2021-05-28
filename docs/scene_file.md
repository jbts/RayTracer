# Scene Files

A *scene file* is a .txt file that tells the ray tracer about the scene it
should trace. It contains information about the geometry in the scene, like
triangles and spheres, and also information about the camera, output image, and
other related things. Much of the structure of these files comes from Dr. Guy.

A scene file can contain any number of lines, each of which may be
- a blank line, which is ignored
- a line starting with '#', which is comment and ignored by the parser
- one of the commands below, which is parsed and applied by the parser

Each command starts with a keyword, like `film_resolution`, followed by a colon
`:` and a list of arguments. A particular keyword always takes the same number
and type of arguments.

The available commands are...

#### `film_resolution: w h` 

Sets the resolution of the output image to `w` pixels wide by `h` pixels tall.

#### `output_image: filename`

Sets the name of the output image.

#### `sample_jitter: n`

Tells the tracer to use jittered super-sampling by taking `n` random samples throughout each pixel instead of taking one sample through each pixel's center. Improves image quality by reducing jaggies/pixelation, but takes about `n` times as long to trace. `n=10` is a good starting point to see how the scene looks.

#### `max_depth: n`

Tells the tracer the maximum number of times a reflection or refraction ray can be recursively traced. Higher values of `n` result in higher-quality reflections and refractions, but take longer to trace.

#### `camera_pos: x y z`

Sets the position of the camera.

#### `camera_fwd: dx dy dz`

Sets the camera's forward direction, which counter-intuitively points *toward* the camera instead of *away* from it. This vector is normalized by the parser.

#### `camera_up: dx dy dz`

Sets the camera's up direction. This vector is normalized by the parser.

#### `camera_fov_ha: ha`

Sets the camera's field of vision half angle. This is the angle from the camera's forward direction to a vector pointing from the camera to the top of the view frame. You can think of it as the "zoom" of the camera. High values for `ha` cause a lot of perspective distortion.

#### `background: r g b`

Sets the color of the scene's background.

#### `material: ar ag ab dr dg db sr sg sb ns tr tg tb ior`

Sets the current material for the scene file. This material will be applied to each primitive until another call to `material`, which changes the current material.

`(ar, ag, ab)` is the ambient color of the material

`(dr, dg, db)` is the diffuse color of the material

`(sr, sg, sb)` is the specular color of the material

`ns` is the Phong exponent for the material

`(tr, tg, tb)` is the transmissive color of the material

`ior` is the index of refraction of the material

#### `sphere: x y z r`

Adds a sphere to the scene at position `(x, y, z)` and with radius `r`.

#### `vertex: x y z`

Adds a vertex to the scene's vertex list.

#### `normal: dx dy dz`

Adds a normal vector to the scene's normal list.

#### `triangle: v1 v2 v3`

Adds a triangle to the scene. `v1`, `v2`, and `v3` are integer indices into the scene's vertex list, which is indexed starting at 0. These are the three vertices or corners of the triangle. The triangle is double-sided, so winding order does not matter.

#### `normal_triangle: v1 v2 v3 n1 n2 n3`

Adds a triangle with normal interpolation to the scene. `v1`, `v2`, and `v3` are as in the `triangle` command. `n1`, `n2`, and `n3` are integer indices into the scene's normal list, which is indexed starting at 0. These are the normals at the corresponding vertex of the triangle. The normal of the triangle at a point inside it is found by interpolating these normals using barycentric coordinates. This means that these triangles are 1-sided, depending on the direction of their normal.

#### `circle: x y z r dx dy dz`

Adds a circle to the scene with center `(x, y, z)` and radius `r`. The normal of the circle is `(dx, dy, dz)`. The circle is 2D and double-sided like triangles created with the `triangle` command.

#### `ambient_light: r g b`

Adds an ambient light to the scene with the given intensity. Ambient lights shine everywhere equally.

#### `point_light: r g b x y z`

Adds a point light to the scene at `(x, y, z)` with intensity `(r, g, b)`. Point lights shine equally in all directions from their position. Their intensity falls off as the square of the distance from the position of the point light.

#### `directional_light: r g b dx dy dz`

Adds a directional light to the scene that shines in direction `(dx, dy, dz)` with intensity `(r, g, b)`. Directional lights are like the sun. They are very far away, and they shine in a single direction. Their intensity does not vary in space.

#### `spot_light: r g b x y z dx dy dz angle1 angle2`

Adds a spot light to the scene at position `(x, y, z)` with intensity `(r, g, b)`. The spot light points in the direction `(dx, dy, dz)`. Spot lights are similar to point lights. They shine from a position outward and their intensity falls off with the square of the distance from their position. But they also shine in a particular direction, and their intensity falls off as the angle from this direction grows. Up until `angle1`, the intensity is not modified by the angle. From `angle1` to `angle2`, the intensity falls off smoothly, until at angles greater than or equal to `angle2` the intensity is 0. Think of a desk lamp, flashlight, or Luxo Jr. from the Pixar short.
