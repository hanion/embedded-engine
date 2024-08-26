=== === === === ===
# embedded engine #
=== === === === ===

## queue ##

 - create struct `Color`, holds only uint8_t, red() ... set_red() ... does bitwise operations
    renderer takes Color

 - create `Mesh` struct, holds [vertices, indices]

 - use polygon-vertex structure for 3d models
    just add an index buffer to each mesh

 - fill polygon function

---

##### maybe #####

 - create a depth buffer

 - fill polygons in the depth buffer, with fill_polygon


