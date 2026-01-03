defmodule DSA.Stack do
  defstruct items: []

  @doc """
  Push an item into the Stack.
  Returns updated struct.
  """
  def push(%__MODULE__{} = stk, item) do
    update_in(stk.items, &[item | &1])
  end

  def push(stk, item) when is_list(stk) do
    [item | stk]
  end

  def top(%__MODULE__{items: items} = _stk) do
    case items do
      [] -> {:error, "Cannot read from empty stack."}
      [top | _rest] -> {:ok, top}
    end
  end

  @doc """
  Pop an item from the Stack.
  Returns:
   updated struct if stack is not empty.
   {:error, message} if stack is empty.
  """
  def pop(%__MODULE__{items: items} = stk) do
    case items do
      [] -> {:error, "Cannot pop from empty stack."}
      [_top | rest] -> update_in(stk.items, fn _v -> rest end)
    end
  end

  def pop(stk) when is_list(stk) do
    case stk do
      [] -> {:error, "Cannot pop from empty stack."}
      [_top | rest] -> rest
    end
  end
end
