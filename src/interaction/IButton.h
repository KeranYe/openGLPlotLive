//
// Created by bcub3d-laptop-dell on 12/12/20.
//

#ifndef OPENGLPLOTLIVE_PROJ_IBUTTON_H
#define OPENGLPLOTLIVE_PROJ_IBUTTON_H

#include "../rendering/IDrawable.h"
#include "../rendering/ConstantXYDrawable.h"
#include "IClickable.h"

namespace GLPL {

    class IButton : public ConstantXYDrawable {
    public:
        // Constructor
        IButton(std::string newButtonName, float x, float y, float width, float height,
                std::shared_ptr<ParentDimensions> parentDimensions);

        // Functions
        void Draw();
        void onClick() override;
        std::string getID();


    private:
        std::string buttonName;

        // Shading
        GLuint EBO;
        std::vector<int> internalIndices = {0, 1, 3, 2, 3, 1};

        // Functions
        void setupShadingBuffers();
        void drawButtonShading();
        void drawButtonLogo();
        void drawButtonOutline();

        // Button Appearance
        glm::vec4 buttonInactiveOutlineColor      = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 buttonInactiveOutlineHoverColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 buttonInactiveShadingColor      = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
        glm::vec4 buttonInactiveShadingHoverColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
        glm::vec4 buttonActiveOutlineColor        = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 buttonActiveOutlineHoverColor   = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 buttonActiveShadingColor        = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
        glm::vec4 buttonActiveShadingHoverColor   = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);


    };

}


#endif //OPENGLPLOTLIVE_PROJ_IBUTTON_H
