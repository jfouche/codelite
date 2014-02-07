editor = codelite.manager:GetActiveEditor()
if editor then
	sel = editor:GetSelection()
	if #sel > 0 then
		text = "/* " .. sel .. " */"
		editor:ReplaceSelection(text)
	end
end