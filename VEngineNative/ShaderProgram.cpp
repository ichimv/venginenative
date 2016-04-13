#include "stdafx.h"
#include "ShaderProgram.h"
#include "Media.h"

ShaderProgram * ShaderProgram::current = nullptr;

ShaderProgram::ShaderProgram(string vertex, string fragment, string geometry, string tesscontrol, string tesseval)
{
    vertexFile = vertex;
    fragmentFile = fragment;
    geometryFile = geometry;
    tessControlFile = tesscontrol;
    tessEvalFile = tesseval;
    generated = false;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(handle);
}

void ShaderProgram::recompile()
{
    generated = false;
}

void ShaderProgram::use()
{
    if (!generated)
        compile();
    current = this;
    glUseProgram(handle);
}

void ShaderProgram::setUniform(const string &name, const GLint &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform1i(location, value);
}

void ShaderProgram::setUniform(const string &name, const GLuint &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform1ui(location, value);
}

void ShaderProgram::setUniform(const string &name, const float &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform1f(location, value);
}

void ShaderProgram::setUniform(const string &name, const bool &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform1i(location, value ? 1 : 0);
}

void ShaderProgram::setUniform(const string &name, const glm::vec2 &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform2f(location, value.x, value.y);
}

void ShaderProgram::setUniform(const string &name, const glm::vec3 &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::setUniform(const string &name, const glm::vec4 &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const string &name, const glm::quat &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const string &name, const glm::mat3 &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const string &name, const glm::mat4 &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniformVector(const string &name, const vector<GLint> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform1iv(location, (GLsizei)value.size(), value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<GLuint> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform1uiv(location, (GLsizei)value.size(), value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<float> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform1fv(location, (GLsizei)value.size(), value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<glm::vec2> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform2fv(location, (GLsizei)value.size(), (GLfloat*)value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<glm::vec3> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform3fv(location, (GLsizei)value.size(), (GLfloat*)value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<glm::vec4> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform4fv(location, (GLsizei)value.size(), (GLfloat*)value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<glm::quat> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniform4fv(location, (GLsizei)value.size(), (GLfloat*)value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<glm::mat3> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniformMatrix3fv(location, (GLsizei)value.size(), GL_FALSE, (GLfloat*)value.data());
}

void ShaderProgram::setUniformVector(const string &name, const vector<glm::mat4> &value)
{
    GLint location = getUniformLocation(name);
    if (location < 0) return;
    glUniformMatrix4fv(location, (GLsizei)value.size(), GL_FALSE, (GLfloat*)value.data());
}

GLint ShaderProgram::getUniformLocation(const string &name)
{
    if (!generated) return -1;
    if (uniformLocationsMap.find(name) == uniformLocationsMap.end()) {
        GLuint location = glGetUniformLocation(handle, name.c_str());
        uniformLocationsMap[name] = location;
        return location;
    }
    else {
        return uniformLocationsMap.at(name);
    }
}

void ShaderProgram::compile()
{
    uniformLocationsMap = {};
    handle = glCreateProgram();
    GLuint vertexHandle = compileSingleShader(GL_VERTEX_SHADER, vertexFile, Media::readString(vertexFile));
    glAttachShader(handle, vertexHandle);

    if (fragmentFile != "") {
        GLuint fragmentHandle = compileSingleShader(GL_FRAGMENT_SHADER, fragmentFile, Media::readString(fragmentFile));
        glAttachShader(handle, fragmentHandle);
    }
    if (geometryFile != "") {
        GLuint geometryHandle = compileSingleShader(GL_GEOMETRY_SHADER, geometryFile, Media::readString(geometryFile));
        glAttachShader(handle, geometryHandle);
    }
    if (tessControlFile != "") {
        GLuint tesscHandle = compileSingleShader(GL_TESS_CONTROL_SHADER, tessControlFile, Media::readString(tessControlFile));
        glAttachShader(handle, tesscHandle);
    }
    if (tessEvalFile != "") {
        GLuint tesseHandle = compileSingleShader(GL_TESS_EVALUATION_SHADER, tessEvalFile, Media::readString(tessEvalFile));
        glAttachShader(handle, tesseHandle);
    }
    glLinkProgram(handle);
    GLint status;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    if (status != 1) {
        GLint loglen;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &loglen);
        char* log = new char[loglen + 1, sizeof(char)];
        glGetProgramInfoLog(handle, loglen, NULL, log);
        printf("LINKING FAILED WITH MESSAGE::\n%s\n", log);
        delete log;
        glDeleteProgram(handle);
    }
    generated = true;
}

string ShaderProgram::resolveIncludes(string source)
{
    string src = source;
    regex includeregex("\\#include (.+)\n");
    smatch match;
    while (regex_search(src, match, includeregex)) {
        int64_t pos = match.position();
        int64_t len = match.length();
        string group = match[1];
        string includedSrc = resolveIncludes(Media::readString(group));
        stringstream ss;
        ss << src.substr(0, pos) << "\n" << includedSrc << "\n" << src.substr(pos + len);
        src = ss.str();
    }
    return src;
}

GLuint ShaderProgram::compileSingleShader(GLenum type, string filename, string source)
{
    //  printf("Compiling shader %s\n", filename.c_str());
    string resolved = resolveIncludes(source);
    //   printf("Compiling source %s\n", resolved.c_str());
    GLuint shader = glCreateShader(type);
    const char* cstr = resolved.c_str();
    glShaderSource(shader, 1, &cstr, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
        GLint loglen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
        char* log = new char[loglen + 1];
        glGetShaderInfoLog(shader, loglen, NULL, log);
        log[loglen] = 0;
        printf("COMPILATION FAILED WITH MESSAGE::\n%s\n", log);
        delete log;
        glDeleteShader(shader);
        //throw exception("Shader compilation failed");
    }
    return shader;
}