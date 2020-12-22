//
// Created by bcub3d-laptop-dell on 12/12/20.
//

#include "IButton.h"

#include <utility>

namespace GLPL {

    IButton::IButton(std::string newButtonName, float x, float y, float width, float height,
                     std::shared_ptr<ParentDimensions> parentDimensions) :
        ConstantXYDrawable(x, y, width, height, CONSTANT_SCALE, CONSTANT_SCALE, std::move(parentDimensions)) {
        // Set button name
        buttonName = std::move(newButtonName);

        // Set Bounding Box Color
        boundingBoxColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        // Setup Shading Buffers
        IButton::setupShadingBuffers();
    }

    void IButton::Draw() {
        // Draw button shading
        IButton::drawButtonShading();

        // Draw button logo
        // TODO - Implement button logo

        // Draw button outline
        IButton::drawButtonOutline();
    }

    void IButton::onClick() {
        toggleActive();
    }

    std::string IButton::getID() {
        return "IButton:" + buttonName + ":" + std::to_string(x) + ":" + std::to_string(y);
    }

    void IButton::setupShadingBuffers() {
        unsigned int indicesDataSizeBytes = internalIndices.size()*sizeof(internalIndices[0]);

        glGenBuffers(1, &EBO);

        // Setup Buffers
        // Bind to existing VAO
        glBindVertexArray(VAO);
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesDataSizeBytes, &internalIndices[0], GL_STATIC_DRAW);

        glBindVertexArray(0); // Unbind VAO

        // EBO - Send Indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, internalIndices.size()*sizeof(internalIndices[0]), &internalIndices[0], GL_STATIC_DRAW);
    }

    void IButton::drawButtonShading() {
        // Draws the data currently stored in the shaded line corresponding to the given VAO
        // The VAO is bound to the EBO from earlier
        // Select colour
        glm::vec4 inColor;
        if (selected && !isActive()) {
            inColor = buttonInactiveShadingHoverColor;
        } else if (!selected && !isActive()) {
            inColor = buttonInactiveShadingColor;
        } else if (selected && isActive()) {
            inColor = buttonActiveShadingHoverColor;
        } else if (!selected && isActive()) {
            inColor = buttonActiveShadingColor;
        }

        // Select Shader
        std::shared_ptr<Shader> shader = shaderSetPt->getPlot2dShader();
        shader->Use();

        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "transformViewport"), 1, GL_FALSE, glm::value_ptr(overallTransform));
        GLfloat zDepthVal = getZDepthValue();
        glUniform4fv(glGetUniformLocation(shader->Program, "inColor"), 1, glm::value_ptr(inColor));
        glUniform1f(glGetUniformLocation(shader->Program, "z"), zDepthVal);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, internalIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

    }

    void IButton::drawButtonLogo() {

    }

    void IButton::drawButtonOutline() {
        // Select colour
        glm::vec4 inColor;
        if (isHovered() && !isActive()) {
            inColor = buttonInactiveOutlineHoverColor;
        } else if (!isHovered() && !isActive()) {
            inColor = buttonInactiveOutlineColor;
        } else if (isHovered() && isActive()) {
            inColor = buttonActiveOutlineHoverColor;
        } else if (!isHovered() && isActive()) {
            inColor = buttonActiveOutlineColor;
        }

        // Select shader
        std::shared_ptr<Shader> shader = shaderSetPt->getPlot2dShader();
        shader->Use();

        glUniformMatrix4fv(glGetUniformLocation(shader->Program,"transformViewport"), 1, GL_FALSE, glm::value_ptr(overallTransform));
        glUniform4fv(glGetUniformLocation(shader->Program,"inColor"),1,glm::value_ptr(inColor));
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP,0,4);
        glBindVertexArray(0);
    }

}