#include "Camera.h"

Ray Camera::getRay(int i, int j) {
	return Ray(position, Vector(j - width / 2 + 0.5, i - height / 2 + 0.5, - height / (2. * tan(fov / 360 * 3.141592))).get_normalized());
}