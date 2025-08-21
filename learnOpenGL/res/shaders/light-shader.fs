#version 330 core

in vec4 vertexColor;
in vec4 vertexNormal;
in vec3 FragPosition;

out vec4 FragColor;

uniform vec4 lightColor;
uniform float ambientLightStrength;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform int specularFocus;
uniform float specularStrength;

void main()
{
   // Ambient light
   vec3 ambient = ambientLightStrength * lightColor.rgb;

   // Calculate diffuse
   vec3 norm = normalize(vertexNormal.xyz);
   vec3 lightDirection = normalize(lightPosition - FragPosition);
   float difference = max(dot(norm, lightDirection), 0.0);
   vec3 diffuse = difference * lightColor.rgb;

   // Specular lighting
   vec3 viewDirection = normalize(cameraPosition - FragPosition);
   vec3 reflectDirection = reflect(-lightDirection, norm);  
   float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularFocus);
   vec3 specular = specularStrength * spec * lightColor.rgb;
   
   // Combine results
   vec3 finalColor = (ambient + diffuse + specular) * vertexColor.rgb;
   FragColor = vec4(finalColor, 1.0);
}
