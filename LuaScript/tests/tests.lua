codelite.Trace("Launching tests")

editor = codelite.manager:NewEditor()

assert(editor:GetEditorText() == "")
editor:SetEditorText("text")
assert(editor:GetEditorText() == "text")

text = editor:GetSelection()
assert(editor:GetSelection() == "")
editor:SelectText(1, 2)
assert(editor:GetSelection() == "ex")
editor:SelectText(1, 18)
assert(editor:GetSelection() == "ext")
