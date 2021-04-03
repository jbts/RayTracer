#ifndef LIGHT_SHADING_H_
#define LIGHT_SHADING_H_

#include "core/Color.h"
#include "core/Vector3.h"
#include "light/Material.h"
#include "light/Intensity.h"

/// Compute the color contribution of diffuse reflection due to a light shining on a point of intersection
///
/// normal is the unit normal of the surface at the intersection
/// to_light is a unit vector pointing from the intersection to the light
/// intensity is the intensity of the light at the intersection
/// mat is the material of the surface at the intersection
Color ComputeDiffuseShading(Vector3 normal, Vector3 to_light, Intensity intensity, Material mat);

/// Compute the color contribution of specular reflection due to a light shining on a point of intersection
/// Uses the Phong model
///
/// dir is the unit direction of the sight ray (from the eye to the intersection)
/// light_reflected is the unit direction of the reflected light at the intersection
/// intensity is the intensity of the light at the intersection
/// mat is the material of the surface at the intersection
Color ComputeSpecularShadingPhong(Vector3 dir, Vector3 light_reflected, Intensity intensity, Material mat);

/// Compute the color contribution of specular reflection due to a light shining on a point of intersection
/// Uses the Blinn-Phong model
///
/// dir is the unit direction of the sight ray (from the eye to the intersection)
/// normal is the unit normal vector of the surface at the intersection
/// to_light is a unit vector pointing from the intersection to the light
/// intensity is the intensity of the light at the intersection
/// mat is the material of the surface at the intersection
Color ComputeSpecularShadingBlinnPhong(Vector3 dir, Vector3 normal, Vector3 to_light, Intensity intensity, Material mat);

#endif