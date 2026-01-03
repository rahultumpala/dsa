defmodule DSA.Node do
  defstruct prev: nil,
            next: nil,
            value: nil

  def new(value) do
    %__MODULE__{value: value}
  end

  def new(%__MODULE__{} = prev, value, %__MODULE__{} = next) do
    %__MODULE__{value: value, prev: prev, next: next}
  end

  def with_prev(%__MODULE__{} = prev, %__MODULE__{} = cur) do
    prev = update_in(prev.next, fn _ -> cur end)
    %__MODULE__{cur | prev: prev}
  end

  def with_prev(%__MODULE__{} = prev, value) do
    cur = %__MODULE__{value: value}
    prev = update_in(prev.next, fn _ -> cur end)
    update_in(cur.prev, fn _ -> prev end)
  end

  def with_next(nil, %__MODULE__{} = cur) do
    cur
  end

  def with_next(%__MODULE__{} = next, %__MODULE__{} = cur) do
    next = update_in(next.prev, fn _ -> cur end)
    %__MODULE__{cur | next: next}
  end

  def with_next(%__MODULE__{} = next, value) do
    cur = %__MODULE__{value: value}
    next = update_in(next.prev, fn _ -> cur end)
    update_in(cur.next, fn _ -> next end)
  end

  @doc """
    Iterates forward when mode = :next
    Iterates backward when mode = :prev
    until a nil value is found at the prev/next locations.
  """
  def read_all(node, mode, acc \\ [])

  def read_all(%__MODULE__{} = node, mode, acc) do
    case mode do
      :next ->
        read_all(node.next, mode, [node.value | acc])

      :prev ->
        read_all(node.prev, mode, [node.value | acc])
    end
  end

  def read_all(nil, _mode, acc) when is_list(acc) do
    acc
  end
end
