#include "PluginEditor.h"
#include "BinaryData.h"


PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), 
    webView (juce::WebBrowserComponent::Options {}
        .withNativeIntegrationEnabled()
        .withBackend (juce::WebBrowserComponent::Options::Backend::webview2)
        .withWinWebView2Options (juce::WebBrowserComponent::Options::WinWebView2 {}
            .withUserDataFolder (juce::File::getSpecialLocation (juce::File::SpecialLocationType::tempDirectory)))
        .withOptionsFrom (gainSliderRelay).withOptionsFrom (trebleSliderRelay).withOptionsFrom (bassSliderRelay)
        .withResourceProvider ([this] (const juce::String& urlPath) -> std::optional<juce::WebBrowserComponent::Resource> {
          auto assetPath = urlPath == "/" ? "index_html" : urlPath.substring (1).replace (".", "_");

          int dataSize = 0;

          if (auto dataPtr = BinaryData::getNamedResource (assetPath.toRawUTF8(), dataSize))
          {
              // Mime type for vanillaJS
              juce::String mimeType = "text/plain";
              if (urlPath == "/" || urlPath.endsWith (".html"))
                  mimeType = "text/html";
              else if (urlPath.endsWith (".js"))
                  mimeType = "application/javascript";
              else if (urlPath.endsWith (".css"))
                  mimeType = "text/css";

              return juce::WebBrowserComponent::Resource {
                  std::vector<std::byte> (reinterpret_cast<const std::byte*> (dataPtr),
                      reinterpret_cast<const std::byte*> (dataPtr) + dataSize),
                  mimeType
              };
          }
          return std::nullopt;
      },
                                                       "demo-origin"))

{
    setSize (600, 400);
    addAndMakeVisible (webView);
    webView.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());
    
    juce::ignoreUnused (processorRef);

#if JUCE_DEBUG
    addAndMakeVisible (inspectButton);

    inspectButton.onClick = [&] {
        if (!inspector)
        {
            inspector = std::make_unique<melatonin::Inspector> (*this);
            inspector->onClose = [this]() { inspector.reset(); };
        }
        inspector->setVisible (true);
    };
#endif

    auto gainParam = processorRef.apvts.getParameter ("gain");
    auto trebleParam = processorRef.apvts.getParameter ("treble");
    auto bassParam = processorRef.apvts.getParameter ("bass");

    if (gainParam != nullptr)
        gainAttachment = std::make_unique<juce::WebSliderParameterAttachment> (*gainParam, gainSliderRelay);

    if (trebleParam != nullptr)
        trebleAttachment = std::make_unique<juce::WebSliderParameterAttachment> (*trebleParam, trebleSliderRelay);

    if (bassParam != nullptr)
        bassAttachment = std::make_unique<juce::WebSliderParameterAttachment> (*bassParam, bassSliderRelay);

    
} 

PluginEditor::~PluginEditor()
{

}

void PluginEditor::resized()
{
    webView.setBounds (getLocalBounds());
    
    #if JUCE_DEBUG
        inspectButton.setBounds (getLocalBounds().withSizeKeepingCentre(100, 50));
    #endif
}

void PluginEditor::parameterValueChanged (int parameterIndex, float newValue)
{
    // This is called when a parameter value changes
    // The WebSliderParameterAttachment handles syncing to the web view automatically
    // You can add custom logic here if needed
    juce::ignoreUnused (parameterIndex, newValue);
}
