#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (fuel <= 0) {
        printf("Mission failed. Fuel exhausted before reaching Planet %d.\n", planet);
        return;
    }

    if (planet > totalPlanets) {
        printf("Mission successful. Spacecraft completed the journey.\n");
        return;
    }

    fuel -= consumption;
    fuel += recharge;

    if (planet % 4 == 0)
        fuel += solarBonus;

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int fuel = 500;
    int consumption = 70;
    int recharge = 20;
    int solarBonus = 100;
    int totalPlanets = 10;

    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);

    return 0;
}
