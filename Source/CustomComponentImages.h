#ifndef CUSTOMCOMPONENTIMAGES_H
#define CUSTOMCOMPONENTIMAGES_H

#include <string>

// Note: These SVGs contain all the different gradients and colors needed
// for the different component states e.g. when the switch is on and off.
// The replacements at the end of the file just replace parts of the SVG
// string with the appropriate gradients and colors for the different states.

static const std::string SliderSvg = R"SVG(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg
   width="530.58057"
   height="60.999992"
   viewBox="0 0 140.38277 16.139581"
   version="1.1"
   id="Slider"
   xmlns:xlink="http://www.w3.org/1999/xlink"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1">
    <linearGradient
       id="TrackGradientStops">
      <stop
         style="stop-color:#bcbcbc;stop-opacity:1;"
         offset="0"
         id="stop1" />
      <stop
         style="stop-color:#e6e6e6;stop-opacity:1;"
         offset="0.67914414"
         id="stop4" />
    </linearGradient>
    <linearGradient
       xlink:href="#TrackGradientStops"
       id="TrackGradient"
       gradientUnits="userSpaceOnUse"
       gradientTransform="matrix(0.26458333,0,0,0.26458333,34.844736,-4.4121039)"
       x1="212.21814"
       y1="19.43902"
       x2="212.21814"
       y2="45.285606" />
  </defs>
  <path
     id="IncDecArea"
     style="fill:#f6b648;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:0.529167"
     d="m 44.591595,0.2645835 c -5.369267,0 -5.781226,15.6104145 0,15.6104145 h 19.596752 c 0.45079,0 0.26458,-1.5875 1.5875,-1.5875 0.38363,0 2.08975,1.202558 2.37711,0.843359 2.11667,-2.645833 2.11667,-11.3770805 0,-14.0229145 -0.31184,-0.38980496 -1.97449,0.79375 -2.38125,0.79375 -1.32291,0 -1.15114,-1.637109 -1.58336,-1.637109 z" />
  <path
     style="fill:url(#TrackGradient);fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:0;stroke-dasharray:none;stroke-opacity:1"
     d="m 41.1358,7.5841914 c -0.901512,-0.443519 -1.663565,-0.8338713 -1.974035,-1.8527633 -0.491276,-1.612247 0.374309,-4.3848576 1.835248,-5.1702756 0.71148,-0.3825 1.783689,-0.248613 46.334162,-0.30004 l 47.209735,-0.05267 1.2782,1.602375 C 136.5044,2.669911 138.03598,0 138.53296,1.1088305 c 1.67897,3.746023 1.58491,6.8590129 1.58491,6.8590129 l -52.285235,-0.0045 C 43.674599,7.9595429 41.867939,7.9443734 41.1358,7.5841724 Z"
     id="SliderTrackBackground" />
  <path
     id="SliderTrackOutline"
     style="fill:#000000;fill-opacity:0;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:0.529167"
     d="m 44.592435,0.2654755 c -2.723223,0 -4.164416,3.8786589 -4.175976,7.7023719 h 99.701411 c 0.0148,-2.749185 -0.51195,-5.5178159 -1.58491,-6.8590129 -0.31185,-0.389805 -1.97449,0.79375 -2.38125,0.79375 -1.32291,0 -1.15114,-1.637109 -1.58336,-1.637109 z" />
  <path
     id="TitleArea"
     style="fill:#f6d9a7;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:0.529167"
     d="m 5.816701,0.2645835 c -0.432226,0 -0.260451,1.637109 -1.583367,1.637109 -0.406758,0 -2.0694073,-1.18355496 -2.3812503,-0.79375 -2.11666694,2.645834 -2.11666694,11.3770815 0,14.0229145 0.287359,0.359199 1.9934823,-0.843359 2.3771173,-0.843359 1.322916,0 1.1367,1.5875 1.5875,1.5875 h 40.843504 c -0.18367,-0.491596 -0.74716,-4.038512 -2.07275,-4.038512 -0.38441,0 -1.162088,1.0493 -1.321362,0.674893 -0.932762,-2.192628 -0.932762,-7.7488765 0,-9.8474585 0.179337,-0.403484 0.917922,0.635619 1.325502,0.635619 1.32559,0 1.897,-2.54144496 2.08463,-3.034956 z" />
</svg>
)SVG";

static const std::string StepperSvg = R"SVG(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg
   version="1.1"
   id="Stepper"
   width="465.86475"
   height="59.483624"
   viewBox="0 0 465.86474 59.483623"
   xmlns:xlink="http://www.w3.org/1999/xlink"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1">
    <linearGradient
       id="InnerCircleGradientStops">
      <stop
         style="stop-color:#4d4d4d;stop-opacity:1;"
         offset="0"
         id="stop42" />
      <stop
         style="stop-color:#d1d1d1;stop-opacity:1;"
         offset="1"
         id="stop43" />
    </linearGradient>
    <linearGradient
       id="OuterCircleGradientStops">
      <stop
         style="stop-color:#a4a4a4;stop-opacity:1;"
         offset="0"
         id="stop38" />
      <stop
         style="stop-color:#ededed;stop-opacity:1;"
         offset="1"
         id="stop39" />
    </linearGradient>
    <linearGradient
       xlink:href="#OuterCircleGradientStops"
       id="LeftOuterCircleGradient"
       x1="258"
       y1="129.5"
       x2="247"
       y2="163"
       gradientUnits="userSpaceOnUse"
       gradientTransform="translate(-45.800019,-124.73108)" />
    <linearGradient
       xlink:href="#InnerCircleGradientStops"
       id="LeftInnerCircleGradient"
       x1="207.18228"
       y1="195.51503"
       x2="201.74521"
       y2="210.69447"
       gradientUnits="userSpaceOnUse"
       gradientTransform="matrix(1.881356,0,0,1.9272728,-178.46045,-359.61909)" />
    <linearGradient
       xlink:href="#OuterCircleGradientStops"
       id="RightOuterCircleGradient"
       gradientUnits="userSpaceOnUse"
       gradientTransform="translate(11.865461,-124.73152)"
       x1="258"
       y1="129.5"
       x2="247"
       y2="163" />
    <linearGradient
       xlink:href="#InnerCircleGradientStops"
       id="RightInnerCircleGradient"
       gradientUnits="userSpaceOnUse"
       gradientTransform="matrix(1.881356,0,0,1.9272728,-120.79503,-359.61953)"
       x1="207.18228"
       y1="195.51503"
       x2="201.74521"
       y2="210.69447" />
    <linearGradient
       xlink:href="#InnerHighlightGradientStops"
       id="LeftOnInnerHighlightGradient"
       x1="179.33228"
       y1="38.816334"
       x2="161.10036"
       y2="82.036331"
       gradientUnits="userSpaceOnUse"
       gradientTransform="translate(83.58855,0.36589462)" />
    <linearGradient
       xlink:href="#InnerHighlightGradientStops"
       id="RightOnInnerHighlightGradient"
       x1="179.33228"
       y1="38.816334"
       x2="161.10036"
       y2="82.036331"
       gradientUnits="userSpaceOnUse"
       gradientTransform="translate(141.21777,0.14079175)" />
    <linearGradient
       id="InnerHighlightGradientStops">
      <stop
         style="stop-color:#fce1b0;stop-opacity:1;"
         offset="0"
         id="stop1" />
      <stop
         style="stop-color:#d98f08;stop-opacity:1;"
         offset="1"
         id="stop2-8" />
    </linearGradient>
  </defs>
  <path
     id="TitleArea"
     style="fill:#f6d9a7;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     d="m 21.984375,1.0031545 c -1.63361,0 -0.984375,6.1875 -5.984375,6.1875 -1.53735,0 -7.82138,-4.47328 -9,-3 -8,10.0000005 -8,41.4804695 0,51.4804695 1.08608,1.3576 7.534415,-3.1875 8.984375,-3.1875 5,0 4.29619,6 6,6 H 165.41992 c 1.70382,0 1,-6 6,-6 1.44997,0 7.8983,4.5451 8.98438,3.1875 8,-10 8,-41.480469 0,-51.4804695 -1.17862,-1.47328 -7.46265,3 -9,3 -5,0 -4.35076,-6.1875 -5.98438,-6.1875 z" />
  <path
     id="ValueArea"
     style="fill:#f6b648;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     d="m 302.06028,1.003154 c -1.63361,0 -0.98437,6.1875 -5.98437,6.1875 -1.53735,0 -7.82138,-4.473279 -9,-3 -8,10.000001 -8,41.48047 0,51.48047 1.08608,1.3576 7.53441,-3.1875 8.98437,-3.1875 5,0 4.29619,6 6,6 h 141.8201 c 1.70381,0 1,-6 6,-6 1.44997,0 7.89829,4.5451 8.98438,3.1875 8,-10 8,-41.480469 0,-51.48047 -1.17863,-1.473279 -7.46266,3 -9,3 -5,0 -4.35077,-6.1875 -5.98438,-6.1875 z" />
  <path
     style="fill:url(#LeftOuterCircleGradient);fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:0;stroke-dasharray:none"
     d="m 198.26675,57.894523 c -13.70433,-3.03455 -23.30089,-15.50405 -22.52215,-29.26469 0.25205,-4.45381 0.93109,-7.13768 2.78504,-11.00752 4.21371,-8.795497 12.50117,-14.673357 22.57076,-16.008237 8.60726,-1.1410296 17.84889,2.31443 24.09672,9.009817 3.02456,3.24123 4.69104,5.92365 6.04251,9.72624 2.69857,7.59287 2.26759,14.83242 -1.32086,22.18859 -3.44183,7.05558 -9.10639,11.93248 -16.90472,14.55415 -2.83388,0.95268 -4.00711,1.14139 -7.75512,1.24729 -3.06264,0.0865 -5.20563,-0.0501 -6.99218,-0.44564 z m 10.56214,-9.02192 c 8.71098,-1.79544 13.5979,-7.91935 14.33232,-17.09441 0.64985,-8.11855 -2.22913,-14.29893 -9.28126,-17.9714 -8.48335,-4.417787 -16.25456,-3.42527 -22.92438,3.16055 -4.63335,4.57497 -5.87202,8.1315 -5.5114,14.86271 0.57733,10.7762 7.49036,17.32388 18.41661,17.41839 1.65988,0.0143 3.89553,-0.15478 4.96811,-0.37584 z"
     id="LeftOuterCircleBackground" />
  <ellipse
     style="fill:url(#LeftInnerCircleGradient);fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:0;stroke-dasharray:none"
     id="LeftInnerCircleBackground"
     cx="204.33902"
     cy="30.478905"
     rx="19.622211"
     ry="18.738331" />
  <circle
     style="fill:#000000;fill-opacity:0;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     id="LeftInnerCircleOutline"
     cx="204.24454"
     cy="30.184769"
     r="19.084202" />
  <circle
     style="fill:#000000;fill-opacity:0;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     id="LeftOuterCircleOutline"
     cx="204.34039"
     cy="29.741959"
     r="28.741665" />
  <path
     id="LeftArrowDown"
     style="fill:#f6b648;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2;stroke-dasharray:none"
     d="m 200.23044,31.241021 v -16.25 h 7.5 v 16.25 l 8.75,-7.5 v 10 l -12.5,11.25 -12.5,-11.25 v -10 z" />
  <path
     style="fill:url(#RightOuterCircleGradient);fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:0;stroke-dasharray:none"
     d="m 255.93223,57.894244 c -13.70433,-3.03455 -23.30089,-15.50405 -22.52215,-29.264691 0.25205,-4.45381 0.93109,-7.13768 2.78504,-11.00752 4.21371,-8.795506 12.50117,-14.673366 22.57076,-16.0082469 8.60726,-1.1410303 17.84889,2.3144299 24.09672,9.0098269 3.02456,3.24123 4.69104,5.92365 6.04251,9.72624 2.69857,7.59287 2.26759,14.832421 -1.32086,22.188591 -3.44183,7.05558 -9.10639,11.93248 -16.90472,14.55415 -2.83388,0.95268 -4.00711,1.14139 -7.75512,1.24729 -3.06264,0.0865 -5.20563,-0.0501 -6.99218,-0.44564 z m 10.56214,-9.02192 c 8.71098,-1.79544 13.5979,-7.91935 14.33232,-17.094411 0.64985,-8.11855 -2.22913,-14.29893 -9.28126,-17.9714 -8.48335,-4.417798 -16.25456,-3.42527 -22.92438,3.16055 -4.63335,4.57497 -5.87202,8.1315 -5.5114,14.86271 0.57733,10.776201 7.49036,17.323881 18.41661,17.418391 1.65988,0.0143 3.89553,-0.15478 4.96811,-0.37584 z"
     id="RightOuterCircleBackground" />
  <ellipse
     style="fill:url(#RightInnerCircleGradient);fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:0;stroke-dasharray:none"
     id="RightInnerCircleBackground"
     cx="262.00461"
     cy="30.478611"
     rx="19.622211"
     ry="18.738331" />
  <circle
     style="fill:#000000;fill-opacity:0;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     id="RightInnerCircleOutline"
     cx="261.91013"
     cy="30.184475"
     r="19.084202" />
  <circle
     style="fill:#000000;fill-opacity:0;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     id="RightOuterCircleOutline"
     cx="262.00598"
     cy="29.741665"
     r="28.741665" />
  <path
     id="RightArrowUp"
     style="fill:#f6b648;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2;stroke-dasharray:none"
     d="m 258.15603,28.893655 v 16.25 h 7.5 v -16.25 l 8.75,7.5 v -10 l -12.5,-11.25 -12.5,11.25 v 10 z" />
</svg>
)SVG";

static const std::string SwitchSvg = R"SVG(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg
   version="1.1"
   id="Switch"
   width="415.61783"
   height="59.48333"
   viewBox="0 0 415.61784 59.483329"
   xmlns:xlink="http://www.w3.org/1999/xlink"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
  <defs
     id="defs1">
    <linearGradient
       xlink:href="#OuterCircleGradientStops"
       id="OuterCircleGradient"
       x1="265.28979"
       y1="123.49665"
       x2="250.43048"
       y2="156.13904"
       gradientUnits="userSpaceOnUse"
       gradientTransform="translate(-42.15512,-124.95384)" />
    <linearGradient
       id="OuterCircleGradientStops">
      <stop
         style="stop-color:#a4a4a4;stop-opacity:1;"
         offset="0"
         id="stop38-3" />
      <stop
         style="stop-color:#fdfdfd;stop-opacity:1;"
         offset="1"
         id="stop39-5" />
    </linearGradient>
    <linearGradient
       id="InnerCircleGradientStops">
      <stop
         style="stop-color:#363636;stop-opacity:1;"
         offset="0"
         id="stop42-9" />
      <stop
         style="stop-color:#ffffff;stop-opacity:1;"
         offset="1"
         id="stop43-1" />
    </linearGradient>
    <linearGradient
       xlink:href="#InnerCircleGradientStops"
       id="InnerCircleGradient"
       x1="213.00055"
       y1="182.79572"
       x2="202.80664"
       y2="204.271"
       gradientUnits="userSpaceOnUse"
       gradientTransform="matrix(1.881356,0,0,1.9272728,-175.11064,-359.86738)" />
    <linearGradient
       xlink:href="#OnInnerHighlightGradientStops"
       id="OnInnerHighlightGradient"
       x1="179.33228"
       y1="38.816334"
       x2="161.10036"
       y2="82.036331"
       gradientUnits="userSpaceOnUse"
       gradientTransform="translate(45.886293,-48.305357)" />
    <linearGradient
       id="OnInnerHighlightGradientStops">
      <stop
         style="stop-color:#fce1b0;stop-opacity:1;"
         offset="0"
         id="stop1" />
      <stop
         style="stop-color:#d98f08;stop-opacity:1;"
         offset="1"
         id="stop2" />
    </linearGradient>
  </defs>
  <path
     id="TitleArea"
     style="fill:#f6d9a7;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     d="m 21.984375,1.000001 c -1.63361,0 -0.984375,6.1875 -5.984375,6.1875 -1.53735,0 -7.82138,-4.47328 -9,-3 -8,10 -8,41.480469 0,51.480469 1.08608,1.3576 7.534415,-3.1875 8.984375,-3.1875 5,0 4.29619,6 6,6 H 167.41992 c 1.70382,0 1,-6 6,-6 1.44997,0 7.8983,4.5451 8.98438,3.1875 8,-10 8,-41.480469 0,-51.480469 -1.17862,-1.47328 -7.46265,3 -9,3 -5,0 -4.35076,-6.1875 -5.98438,-6.1875 z" />
  <path
     id="ValueArea"
     style="fill:#a9a9a9;fill-opacity:1;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     d="m 248.19791,1 c -1.63361,0 -0.98437,6.1875 -5.98437,6.1875 -1.53735,0 -7.82138,-4.47328 -9,-3 -8,10 -8,41.48047 0,51.48047 1.08608,1.3576 7.53441,-3.1875 8.98437,-3.1875 5,0 4.29619,6 6,6 h 145.43555 c 1.70382,0 1,-6 6,-6 1.44997,0 7.8983,4.5451 8.98438,3.1875 8,-10 8,-41.48047 0,-51.48047 -1.17862,-1.47328 -7.46265,3 -9,3 -5,0 -4.35076,-6.1875 -5.98438,-6.1875 z" />
  <path
     style="fill:url(#OuterCircleGradient);fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:0;stroke-dasharray:none"
     d="m 201.91164,57.671783 c -13.70433,-3.03455 -23.30089,-15.504055 -22.52215,-29.264695 0.25205,-4.45381 0.93109,-7.13768 2.78504,-11.00752 4.21371,-8.7954955 12.50117,-14.6733555 22.57076,-16.0082355 8.60726,-1.14103018 17.84889,2.31443 24.09672,9.0098155 3.02456,3.24123 4.69104,5.92365 6.04251,9.72624 2.69857,7.59287 2.26759,14.83242 -1.32086,22.18859 -3.44183,7.05558 -9.10639,11.932485 -16.90472,14.554155 -2.83388,0.95268 -4.00711,1.14139 -7.75512,1.24729 -3.06264,0.0865 -5.20563,-0.0501 -6.99218,-0.44564 z m 10.56214,-9.021925 c 8.71098,-1.79544 13.5979,-7.91935 14.33232,-17.09441 0.64985,-8.11855 -2.22913,-14.29893 -9.28126,-17.9714 -8.48335,-4.4177871 -16.25456,-3.42527 -22.92438,3.16055 -4.63335,4.57497 -5.87202,8.1315 -5.5114,14.86271 0.57733,10.7762 7.49036,17.32388 18.41661,17.41839 1.65988,0.0143 3.89553,-0.15478 4.96811,-0.37584 z"
     id="OuterCircleBackground" />
  <ellipse
     style="fill:url(#InnerCircleGradient);fill-opacity:1;fill-rule:evenodd;stroke:#000000;stroke-width:0;stroke-dasharray:none"
     id="InnerCircleBackground"
     cx="207.68881"
     cy="30.230597"
     rx="19.622211"
     ry="18.738331" />
  <circle
     style="fill:#000000;fill-opacity:0;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     id="InnerCircleOutline"
     cx="207.71342"
     cy="30.184477"
     r="19.084202" />
  <circle
     style="fill:#000000;fill-opacity:0;fill-rule:evenodd;stroke:#6b6b6b;stroke-width:2"
     id="OuterCircleOutline"
     cx="207.80928"
     cy="29.741667"
     r="28.741665" />
</svg>
)SVG";

static const juce::String SwitchOnSvg = juce::String(SwitchSvg).replace("#a9a9a9", "#f6b648").replace("(#InnerCircleGradient)", "(#OnInnerHighlightGradient)");

static const juce::String StepperDownOnSvg = juce::String(StepperSvg).replace("(#LeftInnerCircleGradient)",  "(#LeftOnInnerHighlightGradient)");

static const juce::String StepperUpOnSvg = juce::String(StepperSvg).replace("(#RightInnerCircleGradient)", "(#RightOnInnerHighlightGradient)");

#endif // CUSTOMCOMPONENTIMAGES_H
