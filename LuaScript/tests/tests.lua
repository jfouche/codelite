function assertEquals(expected, value)
	message = "Assertion failed. Expected [" .. expected .. "], got [" .. value .. "]"
	assert(expected == value, message)
end

-- Starts tests
codelite.Trace("Launching tests")
editor = codelite.manager:NewEditor()

assertEquals("", editor:GetEditorText())
editor:SetEditorText("world")
assertEquals("world", editor:GetEditorText())
editor:InsertText(0, "hello ")
assertEquals("hello world", editor:GetEditorText())
editor:AppendText("!")
assertEquals("hello world!", editor:GetEditorText())

-- caret
assertEquals(0, editor:GetCurrentPosition())

-- Selection
assertEquals("", editor:GetSelection())
editor:SelectText(1, 2)
assertEquals("el", editor:GetSelection())
editor:SelectText(6, 18)
assertEquals("world!", editor:GetSelection())
editor:ReplaceSelection("WORLD!")
assertEquals("hello WORLD!", editor:GetEditorText())
editor:SelectText(5, 0)
assertEquals("", editor:GetSelection())
