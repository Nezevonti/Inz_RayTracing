// Inz_RayTracing.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Vec3.h"
#include "Ray.h"
#include "AABB.h"
#include "Voxel.h"
#include "VoxelGrid.h"

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

int main()
{
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

    Vec3 aabbMin(-2, -2, -2);
    Vec3 aabbMax(2, 2, 2);
    
    Vec3 rayOrigin(-2, 0, -2.5);
    Vec3 rayDirection(1, 0, 2);
    Ray ray(rayOrigin, rayDirection);

    VoxelGrid grid(4, 4, 4, aabbMin, aabbMax);

    Vec3 intersectionPoint(0, 0, 0);
    AABB_Face intersectionFace;

    float tmin = -INFINITY;
    float tmax = INFINITY;

    bool intersect = grid.mainVoxel.intersect(ray, intersectionPoint, intersectionFace);

    if (intersect) {
        std::cout << "Intersection occurred at : ";
        intersectionPoint.print();
        std::cout << "\nnormal : ";
        std::cout << grid.mainVoxel.getFaceName(intersectionFace) << "\n";
        grid.mainVoxel.getFaceNormal(intersectionFace).print();
        std::cout << "\n\n";
    }
    else {
        std::cout << "No intersection" << std::endl;
    }
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln


        

