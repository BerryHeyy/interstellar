#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,

    UP,
    DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{

public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    bool constrainPitch = true;

    double mouseXOffset;
    double mouseYOffset;
    double lastX;
    double lastY;

    static double newX;
    static double newY;
    static bool firstMouse;

    static double scrollYOffset;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;

        this->mouseXOffset = 0;
        this->mouseYOffset = 0;
        this->lastX = 0;
        this->lastY = 0;
        this->newX = 0;
        this->newY = 0;
        this->firstMouse = false;
        this->scrollYOffset = 0;

        

        updateCameraVectors();
    }
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;

        if (direction == UP)
            Position += Up * velocity;
        if (direction == DOWN)
            Position -= Up * velocity;
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement()
    {
        mouseXOffset *= MouseSensitivity;
        mouseYOffset *= MouseSensitivity;

        Yaw += mouseXOffset;
        Pitch += mouseYOffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        std::cout << "Offsets: " << mouseXOffset << ", " << mouseYOffset << std::endl;

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void processMouseScroll()
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= this->scrollYOffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;

        std::cout << "Scroll Offset: " << scrollYOffset << "Zoom: " << Zoom << std::endl;
    }

    void processMouseCallback()
    {
        if (firstMouse)
        {
            lastX = newX;
            lastY = newY;
            firstMouse = false;
        }

        this->mouseXOffset = newX - lastX;
        this->mouseYOffset = lastY - newY; // reversed since y-coordinates go from bottom to top

        lastX = newX;
        lastY = newY;
        
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "Lasts: " << lastX << ", " << lastY << " News: " << newX << ", " << newY << std::endl;
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));

        std::cout << "Yaw: " << Yaw << ", Pitch: " << Pitch << std::endl;
        std::cout << "Front vector: " << front.x << ", " << front.y << ", " << front.z << ", " << std::endl;
    }

};

