attribute vec3 vertexPosition;  //attribute変数定義:　.cppに書いてシェーダ(vert/frag)で受け取る　//頂点ごとに異なるデータを受け取る
attribute vec3 vertexNormal;

attribute vec2 vertexUV_a;
varying vec2 vertexUV;   //varying変数定義：　頂点シェーダからフラグメントシェーダにデータを渡したい場合

varying vec3 lightIntensity;

uniform vec3 lightPosition; //uniform変数定義: .cppに書いてシェーダ(vert/frag)で受け取る //全ての頂点に対して一律に処理される情報として受け取る

uniform vec3 lightKd;
uniform vec3 lightLd;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjMatrix;

//-start- myChange
in vec4 color;
//out vec4 varyingColor;
varying vec4 varying_myColor;
in vec2 acolor;
//-end- myChange

void main()
{
    vertexUV = vertexUV_a;

    // Diffuse
    vec3 tnorm = normalize(normalMatrix * vertexNormal);
    vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition, 1.0);
    vec3 s = normalize(vec3( vec4(lightPosition, 1.0) - eyeCoords));
    lightIntensity = lightLd * lightKd * max( dot(s, tnorm), 0.0);
    gl_Position = modelViewProjMatrix * vec4(vertexPosition, 1.0);

    //-start- myChange OK
    //varyingColor = color;
    //varying_myColor = vec4(lightLd * max( dot(s, tnorm), 0.0), 1.0) * color; //lightKdだけ除外する ( lightKdはGUIフォームで設定されているだけなので　） //1.0 は透明度 0.0～1.0の値を指定する。 数値が小さいほど透明。
    //-end- myChange

    //-start- myChange
    vec3 prelightIntensity = lightLd * max( dot(s, tnorm), 0.0) * color; //lightKdだけ除外する ( lightKdはGUIフォームで設定されているだけのもの　） //1.0 は透明度 0.0～1.0の値を指定する。 数値が小さいほど透明。
    //varying_myColor = vec4(prelightIntensity, 1.0 );     //全部、通常表示する。（半透明透明なし）
    varying_myColor = vec4(prelightIntensity, 0.3 );     //全部、半透明にする。
    //varying_myColor = vec4(prelightIntensity, acolor); //面ごとに透明・半透明違えて描画したかったが、意図通り表示されない。。　これから書き方考える
    //-end- myChange
}
