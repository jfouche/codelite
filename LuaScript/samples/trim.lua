function rtrim(s)
  local n = #s
  while n > 0 and s:find("^%s", n) do n = n - 1 end
  return s:sub(1, n)
end

function lines(str)
  local t = {}
  local function helper(line) table.insert(t, line) return "" end
  helper((str:gsub("(.-)\r?\n", helper)))
  return t
end

editor = cl_manager:GetActiveEditor()
if editor then
	text = editor:GetEditorText()
	if #text ~= 0 then
		l = lines(text)
		for i, line in ipair(l) do
			l[i] = rtrim(line)
		end
		newText = table.concat(l, "\n")
		editor.SetEditorText(newText)
	end
end