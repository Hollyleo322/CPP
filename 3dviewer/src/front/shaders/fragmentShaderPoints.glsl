#version 330 core

in vec4 vertexColor;
flat in vec3 vertPos; // Приходит в диапазоне [-1, 1] без интерполяции

uniform vec2 u_resolution;
uniform float u_pointSize;
uniform bool circles;

void main() {
    if (circles) {
        vec2 pixelCoord = gl_FragCoord.xy;
        // Преобразуем vertPos из [-1, 1] в пиксельные координаты
        vec2 center = (vertPos.xy + 1.0) * 0.5 * u_resolution;
        // Вычисляем расстояние в пикселях
        float dist = length(pixelCoord - center);
        float radius = u_pointSize/2; 
        // Отбрасываем фрагменты вне круга
        if (dist > radius) {
            discard;
        }
    }
    gl_FragDepth = 0.0; // всегда на переднем плане
    gl_FragColor = vertexColor;
}