//
// Created by bcub3d-desktop on 4/7/20.
//

#ifndef OPENGLPLOTLIVE_PROJ_AXESLINETICKS_H
#define OPENGLPLOTLIVE_PROJ_AXESLINETICKS_H


// Project Includes
#include "../rendering/IDrawable.h"
#include "../rendering/ConstantXYDrawable.h"


namespace GLPL {

    enum AxesDirection {
        X_AXES_TOP,     // Attached to top, line on bottom
        X_AXES_BOTTOM,  // Attached to bottom, line on top
        X_AXES_CENTRE,  // Attached at centre, line in centre
        Y_AXES_LEFT,    // Attached to left, line on right
        Y_AXES_RIGHT,   // Attached to right, line on left
        Y_AXES_CENTRE   // Attached to centre, line on right
    };

    class AxesLineTicks : public ConstantXYDrawable {
    public:
        // Constructor
        AxesLineTicks(AxesDirection axesDirection, std::shared_ptr<ParentDimensions> parentDimensions);

        // Functions
        void Draw();
        void setParentDimensions(glm::mat4 newParentTransform,
                                 int newParentXPx,
                                 int newParentYPx,
                                 int newParentWidthPx,
                                 int newParentHeightPx);
        void setParentDimensions(std::shared_ptr<ParentDimensions> parentDimensions);


    private:
        // Functions
        void generateAllVertices();
        void generateAxesLines();
        std::tuple<unsigned int, std::vector<float>, std::vector<float>>
                                generateEquallySpacingBetweenLimits(float sectionWidthRel,
                                                                    float sectionWidthAxesUnits,
                                                                    float midRelPos);
        void generateTickVerts();
        void updateSize();
        void setMinMax(float newMin, float newMax);
        void createAndSetupAxesLineBuffers();
        void updateAxesLineBuffers();
        void drawAxesLine();
        void drawMajorTicks();
        void drawMinorTicks();

        // Axes Line Buffers
        AxesDirection axesDirection;
        GLuint axesLineVAO, axesLineVBO;
        std::vector<GLfloat> axesLineVerts;

        // Major Tick Buffers
        GLuint majorTickVAO, majorTickVBO;
        std::vector<GLfloat> majorTickVerts;    // Holds the vertices (-1 to 1) to plot
        std::vector<float> majorTickAxesPos;    // Holds the graph value at this vertex

        // Minor Tick Buffers
        GLuint minorTickVAO, minorTickVBO;
        std::vector<GLfloat> minorTickVerts;    // Holds the vertices (-1 to 1) to plot
        std::vector<float> minorTickAxesPos;    // Holds the graph value at this vertex


        // Settings
        float xMin = -2;
        float xMax = 6;
        float yMin = -0.5;
        float yMax = 1.5;
        glm::vec4 axesLineColor = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);
        unsigned int minorTickSpacingPx = 20;   // Suggested space between minor ticks
        unsigned int minorTickLengthPx = 10;    // Length of minor ticks
        unsigned int majorTickLengthPx = 20;    // Length of major ticks
        unsigned int minorSpacingsPerMajor = 3; // Number of minor spacings between two major spacings

    };

}


#endif //OPENGLPLOTLIVE_PROJ_AXESLINETICKS_H
