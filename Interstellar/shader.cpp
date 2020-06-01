#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{
	int success;
	char infoLog[512];

	const char* vertexSource;
	const char* fragmentSource;

	// Load in shader source

	std::ifstream inFile;

	inFile.open(vertexPath);

	std::string temp = "";
	std::string vertSrc = "";
	std::string fragSrc = "";

	if (inFile.is_open())
	{
		while (std::getline(inFile, temp))
			vertSrc += temp + "\n";
	}
	else
	{
		std::cout << "ERROR::SHADER::VERTEX::COULD_NOT_OPEN_SOURCE_FILE" << std::endl;
	}

	inFile.close();

	vertexSource = vertSrc.c_str();

	temp = "";

	inFile.open(fragmentPath);

	if (inFile.is_open())
	{
		while (std::getline(inFile, temp))
			fragSrc += temp + "\n";
	}
	else
	{
		std::cout << "ERROR::SHADER::FRAGMENT::COULD_NOT_OPEN_SOURCE_FILE" << std::endl;
	}

	inFile.close();
	
	fragmentSource = fragSrc.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COULD_NOT_COMPILE\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COULD_NOT_COMPILE\n" << infoLog << std::endl;
	}

	// Program

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAML::LINKING_ERROR\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(0);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::deleteShader()
{
	glDeleteShader(ID);
}

#pragma region value setters

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

#pragma endregion
