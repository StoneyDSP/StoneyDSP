/*
  ==============================================================================

    HorizontalMeter.h
    Created: 11 July 2022 2:56:03am
    Author:  StoneyDSP

  ==============================================================================
*/

namespace stoneydsp
{
namespace graphics
{

class HorizontalMeter : public juce::Component
{
public:
    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();

        g.setColour(juce::Colours::white.withBrightness(0.4f));
        g.fillRoundedRectangle(bounds, 5.0f);

        g.setColour(juce::Colours::white);
        const auto scaledX = juce::jmap(level, -60.0f, +6.0f, 0.0f, static_cast<float>(getWidth()));
        g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.0f);
    }

    void setLevel(const float value)
    {
        level = value;
    };

private:
    float level = { -60.0f };
};

}
}
