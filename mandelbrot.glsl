#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Output fragment color
out vec4 color;

uniform int iterations;
uniform vec2 s;
uniform vec2 t;

// Function to calculate the magnitude (r) and angle (theta) of a complex number
void cpolar(vec2 z, out float r, out float theta) {
    r = sqrt(z.x * z.x + z.y * z.y);
    theta = atan(z.y, z.x);
}

// Function to create a complex number from magnitude (r) and angle (theta)
vec2 ccomplex(float r, float theta) {
    return vec2(r * cos(theta), r * sin(theta));
}

// Function to raise a complex number to a power (n)
vec2 cpow(vec2 z, float n) {
    float r, theta;
    cpolar(z, r, theta);
    return ccomplex(pow(r, n), n * theta);
}

// old function for classic mandelbrot set
vec2 cpow2(vec2 z)
{
    return vec2(z.x*z.x - z.y*z.y, 2*z.x*z.y);
}

// util
vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0/3.0, 1.0/3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz)*6.0 - K.www);
    return c.z*mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    vec2 c = vec2(fragTexCoord.x, fragTexCoord.y);
    // vec2 c = vec2(0, 0);
    c -= 0.5; //T
    c *= s;   //S
    c += 0.5; //T
    c += t;   //T

    vec2 z = vec2(0, 0);
    // vec2 z = vec2(fragTexCoord.x, fragTexCoord.y);
    // z -= 0.5; //T
    // z *= s;   //S
    // z += 0.5; //T
    // z += t;   //T

    int iter;
    for (iter = 0; iter < iterations && dot(z,z)<4; ++iter)
    {
        z = cpow2(z) + c;
        // z = cpow(z, 3) + c;
    }

    float x = iter + 1 - log(log(length(z))/log(2.0));
    float norm = x/iterations;

    if (norm > 0.999) 
        color = vec4(0, 0, 0, 1);
    else 
        color = vec4(hsv2rgb(vec3(240.0/360.0 - norm, 1.0, 1.0)), 1.0);
}
