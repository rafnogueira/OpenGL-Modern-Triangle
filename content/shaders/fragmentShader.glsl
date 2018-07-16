
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texKitten;

uniform sampler2D  texPuppy;

void main()
{        
    vec4 coolKitten = texture( texKitten, TexCoord);
    vec4 colPuppy = texture( texPuppy, TexCoord);
    
    FragColor = mix(coolKitten, colPuppy, 0.5);

}

