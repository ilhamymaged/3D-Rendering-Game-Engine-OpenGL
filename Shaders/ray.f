#version 460 core
out vec4 FragColor;

uniform float resX;
uniform float resY;

uniform vec3 cameraPos;
uniform mat4 invView;
uniform mat4 invProjection;

uniform int maxBounces;

//-------//
//Structs//
//-------//

struct Ray 
{
    vec3 origin;
    vec3 direction;
};

struct HitInfo
{
    float t;
    vec3 position;
    vec3 normal;
    vec3 color;
    bool hit;
    float reflectivity;
};

struct DirectionalLight 
{ 
    vec3 direction; 
    vec3 color;
    vec3 ambient;
};

struct PointLight
{
    vec3 position;
    vec3 color;
    vec3 ambient;
};

struct Sphere
{
    vec3 center;
    float radius;
    vec3 color;
    float reflectivity;
};


struct Plane 
{
    vec3 point;
    vec3 normal;
    vec3 color;
    float reflectivity;
};

#define MAX_SPHERE_COUNT 32
#define MAX_PLANE_COUNT 16

#define MAX_POINT_LIGHTS 8

uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;

#define POINT_LIGHT_RADIUS 0.1

Ray generateRay(vec2 fragCoord, float resX, float resY, mat4 v, mat4 invProjection, vec3 cameraPos);
bool rayIntersectsSphere(Ray ray, Sphere sphere, out float t);
bool rayIntersectsPlane(Ray ray, Plane plane, out float t);
vec3 shadeRay(Ray ray);

bool findClosestSphere(Ray ray, out HitInfo hit);
bool findClosestPlane(Ray ray, out HitInfo hit);
bool isInShadow(Ray ray, float maxDist);
vec3 checkPointLightsVisual(Ray ray);

uniform Plane planes[MAX_PLANE_COUNT];
uniform Sphere spheres[MAX_SPHERE_COUNT];

uniform int sphereSize;
uniform int planeSize;

void main() 
{
    Ray ray = generateRay(gl_FragCoord.xy, resX, resY, invView, invProjection, cameraPos);
    vec3 color = shadeRay(ray);
    FragColor = vec4(clamp(color, 0.0, 1.0), 1.0);
}

vec3 checkPointLightsVisual(Ray ray)
{
    for (int i = 0; i < pointLightCount; i++)
    {
        PointLight light = pointLights[i];
        
        // Treat light as a small sphere
        Sphere lightSphere;
        lightSphere.center = light.position;
        lightSphere.radius = POINT_LIGHT_RADIUS;
        lightSphere.color = light.color;

        float t;
        if (rayIntersectsSphere(ray, lightSphere, t))
        {
            return light.color; // render the light as itself
        }
    }

    return vec3(-1.0); // -1 means no intersection
}

bool isInShadow(Ray ray, float maxDist)
{
    HitInfo tempHit;
    if (findClosestSphere(ray, tempHit) && tempHit.t < maxDist) return true;
    if (findClosestPlane(ray, tempHit) && tempHit.t < maxDist) return true;
    return false;
}

bool findClosestSphere(Ray ray, out HitInfo hit)
{
    hit.t = 1e30;
    hit.hit = false;

    for (int i = 0; i < sphereSize; i++)
    {
        float t;
        if (rayIntersectsSphere(ray, spheres[i], t) && t < hit.t)
        {
            hit.t = t;
            hit.position = ray.origin + t * ray.direction;
            hit.normal = normalize(hit.position - spheres[i].center);
            hit.color = spheres[i].color;
            hit.hit = true;
            hit.reflectivity = spheres[i].reflectivity;
        }
    }
    return hit.hit;
}

bool findClosestPlane(Ray ray, out HitInfo hit)
{
    hit.t = 1e30;
    hit.hit = false;

    for (int i = 0; i < planeSize; i++)
    {
        float t;
        if (rayIntersectsPlane(ray, planes[i], t) && t < hit.t)
        {
            hit.t = t;
            hit.position = ray.origin + t * ray.direction;
            hit.normal = normalize(planes[i].normal);
            hit.color = planes[i].color;
            hit.hit = true;
            hit.reflectivity = planes[i].reflectivity;
        }
    }
    return hit.hit;
}

bool rayIntersectsPlane(Ray ray, Plane plane, out float t)
{

    float denom = dot(ray.direction, plane.normal);
    if (abs(denom) < 1e-6) return false; // parallel

    t = dot(plane.point - ray.origin, plane.normal) / denom;
    return t > 0.0;
}

Ray generateRay(vec2 fragCoord, float resX, float resY, mat4 invView, mat4 invProjection, vec3 cameraPos) 
{
    vec2 ndc = (fragCoord / vec2(resX, resY)) * 2.0f - 1.0f;
    vec4 clipSpacePos = vec4(ndc.x, ndc.y, -1.0f, 1.0f);

    vec4 viewSpacePos = invProjection * clipSpacePos;
    viewSpacePos /= viewSpacePos.w;

    vec4 worldPos = invView * viewSpacePos;
    vec3 rayDirection = normalize(worldPos.xyz - cameraPos);

    Ray ray;
    ray.origin = cameraPos;
    ray.direction = rayDirection;
    return ray;
}

bool rayIntersectsSphere(Ray ray, Sphere sphere, out float t) 
{
    vec3 OC = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(ray.direction, OC);
    float c = dot(OC, OC) - sphere.radius * sphere.radius;

    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return false;
    } else {
        float sqrtDisc = sqrt(discriminant);
        float t0 = (-b - sqrtDisc) / (2.0 * a);
        float t1 = (-b + sqrtDisc) / (2.0 * a);

        if (t0 > 0.0) {
            t = t0;
        } 
        else if (t1 > 0.0) {
            t = t1;
        } else {
            return false;
        }

        return true;
    }
}

vec3 shadeRay(Ray ray)
{
    vec3 color = vec3(0.0);
    vec3 throughput = vec3(1.0); // keeps track of reflected energy

    for (int depth = 0; depth < maxBounces; depth++) 
    {
        HitInfo sphereHit, planeHit;    
        bool hitSphere = findClosestSphere(ray, sphereHit);
        bool hitPlane  = findClosestPlane(ray, planeHit);

        HitInfo hit;
        if (hitSphere && (!hitPlane || sphereHit.t < planeHit.t))
            hit = sphereHit;
        else if (hitPlane)
            hit = planeHit;
        else
        {
            color += throughput * vec3(0.5, 0.7, 1.0); // sky
            break;
        }

        vec3 localColor = hit.color * 0.05; // ambient

        // Directional light
        DirectionalLight dirLight;
        dirLight.direction = vec3(-0.2, -1.0, -0.3);
        dirLight.color = vec3(1.0);
        dirLight.ambient = vec3(0.2);

        vec3 viewDir = normalize(cameraPos - hit.position);
        vec3 lightDir = normalize(-dirLight.direction);

        Ray shadowRay;
        shadowRay.origin = hit.position + 1e-4 * hit.normal;
        shadowRay.direction = lightDir;

        if (!isInShadow(shadowRay, 1e30))
        {
            float diff = max(dot(hit.normal, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, hit.normal);
            float spec = pow(max(dot(reflectDir, viewDir), 0.0), 32.0);

            localColor += hit.color * diff * dirLight.color + spec * dirLight.color;
        }

        for (int i = 0; i < pointLightCount; i++)
        {
            PointLight light = pointLights[i];
            vec3 L = light.position - hit.position;
            float dist = length(L);
            vec3 lightDir = normalize(L);

            shadowRay.origin = hit.position + 1e-4 * hit.normal;
            shadowRay.direction = lightDir;

            if (!isInShadow(shadowRay, dist))
            {
                float diff = max(dot(hit.normal, lightDir), 0.0);
                vec3 reflectDir = reflect(-lightDir, hit.normal);
                float spec = pow(max(dot(reflectDir, viewDir), 0.0), 32.0);

                float attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * dist * dist);
                localColor += (hit.color * diff + spec) * light.color * attenuation;
            }
        }

        color += throughput * localColor;

        if (hit.reflectivity <= 0.0)
            break;

        throughput *= hit.reflectivity;
        ray.origin = hit.position + 1e-4 * hit.normal;
        ray.direction = reflect(-viewDir, hit.normal);
    }

    return color;
}