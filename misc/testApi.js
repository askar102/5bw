// Test-only bridge for automated testing (Playwright etc).
// Exposes window.TestAPI so input can be injected deterministically at
// the game-logic level, instead of relying on real DOM key/mouse events
// which go through canvas focus + letterbox mouse scaling and real frame
// timing (both flaky to drive from an automation tool).
Module['onRuntimeInitialized'] = (function (prevInit) {
  return function () {
    if (prevInit) prevInit();

    var keyDown = Module.cwrap('TestApi_KeyDown', null, ['number']);
    var keyUp   = Module.cwrap('TestApi_KeyUp', null, ['number']);
    var tapKey  = Module.cwrap('TestApi_TapKey', null, ['number']);
    var clickAt = Module.cwrap('TestApi_ClickAt', null, ['number', 'number']);

    window.TestAPI = {
      keyDown: keyDown,
      keyUp: keyUp,
      tapKey: tapKey,
      clickAt: clickAt,
      KEY: {
        W: 87, A: 65, S: 83, D: 68,
        ENTER: 257, UP: 265, DOWN: 264, LEFT: 263,
        M: 77, B: 66, H: 72, V: 86
      }
    };

    console.log('[TestAPI] ready');
  };
})(Module['onRuntimeInitialized']);
