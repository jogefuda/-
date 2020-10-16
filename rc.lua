-- If LuaRocks is installed, make sure that packages installed through it are
-- found (e.g. lgi). If LuaRocks is not installed, do nothing.
pcall(require, "luarocks.loader")

-- Standard awesome library
local gears = require("gears")
local awful = require("awful")
require("awful.autofocus")
-- Widget and layout library
local wibox = require("wibox")
-- Theme handling library
local beautiful = require("beautiful")
-- Notification library
local naughty = require("naughty")
local menubar = require("menubar")
local hotkeys_popup = require("awful.hotkeys_popup")

--  {{{ i dont know what it is used for
-- Enable hotkeys help widget for VIM and other apps
-- when client with a matching name is opened:
require("awful.hotkeys_popup.keys")
-- }}}

require("main.error_handling")
require("main.signal")

RC = {
    vars = require("main.user_vars")
}


-- TODO: move to theme
-- Themes define colours, icons, font and wallpapers.
beautiful.init(gears.filesystem.get_themes_dir() .. "zenburn/theme.lua")
local theme = beautiful.get()
theme.font = "Cantarell 11"
--theme.font = "3270 11"

local main = {
    key_bind    = require("main.keyboard"),
    button_bind = require("main.button"),
    layout      = require("main.layout"),
    rule        = require("main.rule"),
    menu        = require("main.menu"),
    statusbar   = require("main.statusbar")
}

awful.layout.layouts = main.layout


-- set global hotkey
root.buttons(main.button_bind.global)
root.keys(main.key_bind.global)

-- set rule and client hotkey
awful.rules.rules = main.rule(main.key_bind.client, main.button_bind.client)

awful.util.spawn("xset r rate 240 38", false)


