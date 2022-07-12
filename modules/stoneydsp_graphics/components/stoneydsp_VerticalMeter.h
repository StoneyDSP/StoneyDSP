/*
  ==============================================================================

    VerticalMeter.h
    Created: 11 July 2022 2:56:03am
    Author:  StoneyDSP

  ==============================================================================
*/

namespace stoneydsp
{
namespace graphics
{

class VerticalMeter : public juce::Component, juce::Timer
{
public:
    VerticalMeter(std::function<float()>&& valueFunction) : valueSupplier(std::move(valueFunction))
    {
        startTimerHz(60);
    }

    void timerCallback() override
    {
        repaint();
    }

    void paint(juce::Graphics& g) override
    {
        const auto level = valueSupplier();

        auto bounds = getLocalBounds().toFloat();

        g.setColour(juce::Colours::white.withBrightness(0.4f));
        g.fillRoundedRectangle(bounds, 5.0f);

        g.setColour(juce::Colours::white);
        const auto scaledY = juce::jmap(level, -60.0f, +6.0f, 0.0f, static_cast<float>(getHeight()));
        g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), 5.0f);
    }
private:

    std::function<float()> valueSupplier;
};

}
}
