// Inz_RayTracing.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cassert>

#include "Vec3.h"
#include "Ray.h"
#include "AABB.h"
#include "Voxel.h"
#include "VoxelGrid.h"
#include "Camera.h"
#include "Sphere.h"
#include "Cube.h"
#include "scene.h"

void intersectionTest(Ray ray, AABB aabb) {

    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;


    // Test for intersection
    float tmin = -INFINITY;
    float tmax = INFINITY;
    bool intersect = aabb.intersect(ray, intersectionPoint, intersectionFace);


    // Print the intersection result
    if (intersect) {
        std::cout << "Intersection occurred at : ";
        intersectionPoint.print();
        std::cout << "\nnormal : ";
        std::cout << aabb.getFaceName(intersectionFace) << "\n";
        aabb.getFaceNormal(intersectionFace).print();
        std::cout << "\n\n";
    }
    else {
        std::cout << "No intersection" << std::endl;
    }
}


/*
    Vec3 a(0, 0, 1);
    Vec3 b(0, 1, 0);
    Vec3 c(0, 3, 4);

    std::cout << a.sinBetween(b) << "\n";
    std::cout << a.sinBetween(c);
    */
    /*
    Vec3 aabbMin(-1, -1, -1);
    Vec3 aabbMax(1, 1, 1);
    AABB aabb(aabbMin, aabbMax);

    Vec3 rayOrigin(0, 0, -4);
    Vec3 rayDirection(0, 0, 1);
    Ray ray(rayOrigin, rayDirection);

    std::cout << "test0" << std::endl;
    intersectionTest(ray, aabb);
    */

/*
int main()
{
    

    Vec3 aabbMin(-2, -2, -2);
    Vec3 aabbMax(2, 2, 2);
    
    Vec3 rayOrigin(-2, 0, -2.5);
    Vec3 rayDirection(1, 0, 2);
    //Ray ray(rayOrigin, rayDirection);

    VoxelGrid grid(4, 4, 4, aabbMin, aabbMax);

    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;

    float tmin = -INFINITY;
    float tmax = INFINITY;

    //grid.traverseRay(ray);

    Vec3 cameraPosition(-8, 0, 0);
    Vec3 cameraTarget(0,0,0);
    Vec3 up(0, 0, 1);

    Camera c(cameraPosition, cameraTarget,up, 0.45);

    int pixelX = 0;
    int pixelY = 0;
    Ray ray = c.getRay(pixelX, pixelY);
    assert(ray.origin == c.position);
    
    pixelX = c.imageWidth / 2;
    pixelY = c.imageHeight / 2;
    ray = c.getRay(pixelX, pixelY);
    assert(ray.origin == c.position);
    assert(ray.direction == c.direction);


}

*/


#include <Windows.h>
#include <vector>

// Window dimensions
const int WindowWidth = 640;
const int WindowHeight = 480;

// Array of pixels in RGB format
Vec3 *pixels;

// Win32 Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Iterate over the pixels and set their colors on the window
        for (int y = 0; y < WindowHeight; ++y)
        {
            for (int x = 0; x < WindowWidth; ++x)
            {
                int index = y * WindowWidth + x;
                const Vec3& pixel = pixels[index];
                
                COLORREF color = RGB(pixel.x * 255, pixel.y * 255, pixel.z * 255);
                SetPixel(hdc, x, y, color);
            }
        }

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Create a window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RayTracingWindow";
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        L"RayTracingWindow",
        L"Ray Tracing Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WindowWidth,
        WindowHeight,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }




    


    Vec3 aabbMin(-4, -4, -4);
    Vec3 aabbMax(4, 4, 4);

    Vec3 rayOrigin(-2, 0, -2.5);
    Vec3 rayDirection(1, 0, 2);
    //Ray ray(rayOrigin, rayDirection);

    VoxelGrid grid(16, 16, 16, aabbMin, aabbMax);

    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;

    float tmin = -INFINITY;
    float tmax = INFINITY;

    //grid.traverseRay(ray);

    Vec3 cameraPosition(-20, 0, 0);
    Vec3 cameraTarget(0, 0, 0);
    Vec3 up(0, 0, 1);

    Camera cam(cameraPosition, cameraTarget, up, (3.1415/3.0));


    //create scene object
    Scene scene(grid, cam);

    //create primitives
    Sphere *s1 = new Sphere(Vec3(), 1.0);
    //Cube *c1 = new Cube(Vec3(2, 2, 2), Vec3(2.5, 2.5, 2.5));

    
    //scene.addPrimitive(s1);
    scene.addPrimitive(s1);

    /*
    bool b;
    char buffer[100];
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            for (int z = 0; z < 16; z++) {
                b = grid.getVoxel(x, y, z).occupied;
                if (b) {
                    sprintf_s(buffer, "(%d,%d,%d) %c\n", x, y, z, b ? 'T' : 'F');
                    OutputDebugStringA(buffer);
                    b = false;
                }
            }
        }
    }
    */

    //cam.draw(grid);
    scene.render();

    pixels = cam.getPixels();


    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Enter the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}


