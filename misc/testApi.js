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
    var rightClickAt = Module.cwrap('TestApi_RightClickAt', null, ['number', 'number']);
    var scroll = Module.cwrap('TestApi_Scroll', null, ['number']);
    var teleportTo = Module.cwrap('TestApi_TeleportTo', null, ['number', 'number', 'number', 'number']);
    var getBattleStateRaw = Module.cwrap('TestApi_GetBattleState', 'string', []);

    window.TestAPI = {
      keyDown: keyDown,
      keyUp: keyUp,
      tapKey: tapKey,
      clickAt: clickAt,
      rightClickAt: rightClickAt,
      scroll: scroll,
      // warps the player to a MapLocation instead of walking there
      teleportTo: function (chunkX, chunkY, tileX, tileY) {
        teleportTo(chunkX, chunkY, tileX, tileY);
      },
      // JSON dump of the running battle (party HP/selection/timestop), or null outside battle
      getBattleState: function () {
        return JSON.parse(getBattleStateRaw());
      },
      KEY: {
        W: 87, A: 65, S: 83, D: 68,
        ENTER: 257, UP: 265, DOWN: 264, LEFT: 263,
        M: 77, B: 66, H: 72, V: 86, F: 70
      }
    };

    console.log('[TestAPI] ready');
  };
})(Module['onRuntimeInitialized']);
