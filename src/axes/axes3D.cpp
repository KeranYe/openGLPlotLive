//
// Created by bcub3d-desktop on 30/1/21.
//

#include "axes3D.h"


namespace GLPL {


    Axes3D::Axes3D(float x, float y, float width, float height, std::shared_ptr<ParentDimensions> parentDimensions)
            : Axes(x, y, width, height, parentDimensions) {

        // Create Axes
        Axes3D::createAxesLines();

    }

    void Axes3D::createAxesLines() {
        // Get parent pointers
        std::shared_ptr<ParentDimensions> ourParentDimensions = createParentDimensions();
        // Create axes
        axesArea->addAxesLine("x", X_AXES_CENTRE);
        axesArea->addAxesLine("y", Y_AXES_CENTRE);
    }

    void Axes3D::addText(const char* textString, float x, float y, float fontSize, AttachLocation attachLocation) {
        // Create Parent Dimensions
        std::shared_ptr<ParentDimensions> newParentPointers = IDrawable::createParentDimensions();
        // Create Text String
        std::shared_ptr<IDrawable> textStringObj = std::make_shared<TextString>(textString, x, y, fontSize, newParentPointers);
        std::shared_ptr<TextString> textStringPt = std::dynamic_pointer_cast<TextString>(textStringObj);
        // Set pin position
        textStringPt->setAttachLocation(attachLocation);
        // Register Child
        Axes::registerChild(textStringObj);
        // Store Text String
        textStringMap.insert(std::pair<unsigned int, std::shared_ptr<TextString>>(textStringCount, textStringPt));
        textStringCount += 1;
    }

    std::shared_ptr<TextString> Axes3D::getText(unsigned int textStringId) {
        if (textStringMap.count(textStringId) > 0) {
            return textStringMap.at(textStringId);
        } else {
            std::cout << "TextString " << textStringId << " does not exist!" << std::endl;
            return nullptr;
        }
    }

    void Axes3D::removeTextString(unsigned int textStringId) {
        if (textStringMap.count(textStringId) > 0) {
            std::shared_ptr<TextString> textString2Remove = textStringMap.at(textStringId);
            // Remove child
            IDrawable::removeChild(textString2Remove);
            // Remove axes
            textStringMap.erase(textStringId);
        } else {
            std::cout << "Cannot remove TextString " << textStringId << ", TextString does not exist!" << std::endl;
        }
    }

    std::shared_ptr<ILine2D> Axes3D::addLine(std::vector<float> *dataPtX, std::vector<float> *dataPtY, LineType lineType, glm::vec3 colour,
                                           float opacityRatio, std::string label) {
        return axesArea->addLine(dataPtX, dataPtY, lineType, colour, opacityRatio, std::move(label));
    }

    std::shared_ptr<IScatterPlot> Axes3D::addScatterPlot(std::vector<float> *dataPtX, std::vector<float> *dataPtY,
                                                       glm::vec3 colour, float opacityRatio, MarkerType markerType, std::string label) {
        return axesArea->addScatterPlot(dataPtX, dataPtY, colour, opacityRatio, markerType, std::move(label));
    }

    void Axes3D::setTitle(std::string newTitle) {
        axesArea->setText("axes-title", std::move(newTitle));
    }

    void Axes3D::setXLabel(std::string newXLabel) {
        axesArea->setText("x-label", std::move(newXLabel));
    }

    void Axes3D::setYLabel(std::string newYLabel) {
        axesArea->setText("y-label", std::move(newYLabel));
    }

    void Axes3D::setXLabelRotation(TextRotation newTextRotation) {
        axesArea->setTextRotation("x-label", newTextRotation);
    }

    void Axes3D::setYLabelRotation(TextRotation newTextRotation) {
        axesArea->setTextRotation("y-label", newTextRotation);
    }


}