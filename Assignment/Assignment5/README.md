# Assignment5

## Compile and Run it
**Compile**<br>
```unix
mkdir Code/build; cd Code/build
cmake ..
make
```
**Run**<br>
```
./Raytracing
```
![binary.ppm](Sources/Raytracing.png)

<br>

## Techniques
### Recursive Ray Tracing
![RecursiveRayTracing.png](Sources/RecursiveRayTracing.png)
#### 1. Find the primary ray
```cpp
// Render.cpp func Render(Scene&)
    std::vector<Vector3f> framebuffer(scene.width * scene.height);
    float scale = std::tan(deg2rad(scene.fov * 0.5f));
    float imageAspectRatio = scene.width / (float)scene.height;
    Vector3f eye_pos(0);
    int m = 0;
    for (int j = 0; j < scene.height; ++j)
    {
        for (int i = 0; i < scene.width; ++i)
        {
            float nx = (i + 0.5f) * 2 / scene.width - 1.0f;
            float ny = (j + 0.5f) * 2 / scene.height - 1.0f;
            float x = nx * scale * imageAspectRatio;
            float y = -ny * scale;
            Vector3f dir = Vector3f(x, y, -1); 
            dir = normalize(dir);
            framebuffer[m++] = castRay(eye_pos, dir, scene, 0);
        }
        UpdateProgress(j / (float)scene.height);
    }

```


#### 2. Called `castRay()` recursively
```cpp
// Render.cpp func Render(Scene&)
            framebuffer[m++] = castRay(eye_pos, dir, scene, 0);
// for the implementation of castRay()  check it in Render.cpp
```



### Ray intersection
![MT.png](Sources/MT.png)
```cpp
// Render.cpp func castRay()
    if (auto payload = trace(orig, dir, scene.get_objects()); payload)

// Render.cpp func trace()
        if (object->intersect(orig, dir, tNearK, indexK, uvK) && tNearK < tNear)

// Triangle.cpp func intersect()
            if (rayTriangleIntersect(v0, v1, v2, orig, dir, t, u, v) && t < tnear)

// Triangle.cpp func rayTriangleInterset()
bool rayTriangleIntersect(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, const Vector3f& orig,
                          const Vector3f& dir, float& tnear, float& u, float& v)
{
    Vector3f E1 = v1 - v0, E2 = v2 - v0, S = orig - v0;
    Vector3f S1 = crossProduct(dir,E2);
    Vector3f S2 = crossProduct(S,E1);

    tnear = 1.0 / dotProduct(S1,E1) * dotProduct(S2,E2);
    u = 1.0 / dotProduct(S1,E1) * dotProduct(S1,S);
    v = 1.0 / dotProduct(S1,E1) * dotProduct(S2,dir);

    return (tnear > 0 && u > 0 && v > 0 && (1 - u - v) > 0);
}


```
