

let dial1 = new Knob({
   size: "large",
   type: "Wedge",
   lowVal: 1,
   highVal: 256,
   value: 125,
   id: "GainKnob",
   label: false,
   callback: (val) => {
       gainState.setNormalisedValue(toNormalized(val));
   }
});
let dial2 = new Knob({
  size: "large",
   type: "Wedge",
   lowVal: 1,
   highVal: 256,
   value: 125,
   id: "TrebleKnob",
   label: false,
   callback: (val) => {
       trebleState.setNormalisedValue(toNormalized(val));
   }
});

let dial3 = new Knob({
  size: "large",
   type: "Wedge",
   lowVal: 1,
   highVal: 256,
   value: 125,
   id: "BassKnob",
   label: false,
   callback: (val) => {
       bassState.setNormalisedValue(toNormalized(val));
   }
});

import * as Juce from './juce/index.js';

const gainState = Juce.getSliderState("GainKnob");
const trebleState = Juce.getSliderState("TrebleKnob");
const bassState = Juce.getSliderState("BassKnob");

const lowVal = 1;
const highVal = 256;
const toNormalized = (val) => (val - lowVal) / (highVal - lowVal);
const fromNormalized = (norm) => norm * (highVal - lowVal) + lowVal;

gainState.valueChangedEvent.addListener(() => {
    let newVal = fromNormalized(gainState.getNormalisedValue());
    dial1.setValue(newVal);
});

trebleState.valueChangedEvent.addListener(() => {
    let newVal = fromNormalized(trebleState.getNormalisedValue());
    dial2.setValue(newVal);
});

bassState.valueChangedEvent.addListener(() => {
    let newVal = fromNormalized(bassState.getNormalisedValue());
    dial3.setValue(newVal);
});

// Optional: Handle mouse drag gestures for proper DAW undo/redo handling
document.getElementById("GainKnob").addEventListener("mousedown", () => gainState.sliderDragStarted());
document.getElementById("GainKnob").addEventListener("mouseup", () => gainState.sliderDragEnded());

document.getElementById("TrebleKnob").addEventListener("mousedown", () => trebleState.sliderDragStarted());
document.getElementById("TrebleKnob").addEventListener("mouseup", () => trebleState.sliderDragEnded());

document.getElementById("BassKnob").addEventListener("mousedown", () => bassState.sliderDragStarted());
document.getElementById("BassKnob").addEventListener("mouseup", () => bassState.sliderDragEnded());


