set zoomStatus to "stopped"
set muteStatus to "muted"
set videoStatus to "stopped"
set shareStatus to "stopped"

tell application "System Events"
	if exists (window 1 of process "zoom.us") then
		set zoomStatus to "open"
	end if
end tell

if (zoomStatus is equal to "open") then
	tell application "System Events" to tell application process "zoom.us"
		if exists (menu item "Mute audio" of menu 1 of menu bar item "Meeting" of menu bar 1) then
			set muteStatus to "unmuted"
		end if
		if exists (menu item "Stop Video" of menu 1 of menu bar item "Meeting" of menu bar 1) then
			set videoStatus to "started"
		else
			set videoStatus to "stopped"
		end if
		if exists (menu item "Stop Share" of menu 1 of menu bar item "Meeting" of menu bar 1) then
			set shareStatus to "started"
		end if
	end tell
	
	tell application "System Events"
		if (muteStatus is equal to "unmuted") then
			tell application "zoom.us" to activate
			keystroke "a" using {shift down, command down}
		end if
		if (videoStatus is equal to "started") then
			tell application "zoom.us" to activate
			keystroke "v" using {shift down, command down}
		end if
		if (shareStatus is equal to "started") then
			tell application "zoom.us" to activate
			keystroke "s" using {shift down, command down}
		end if
	end tell
else
	say "Zoom is not running"	
end if

