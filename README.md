# Units

c++ units for common tasks

- **Algorithm** – collection with useful things: iterator range, lazy_value, object_pool, dictionary, etc
- **BinaryFStream** -- can parse text-lines from binary filestream (class BinTxtIFStream)
- **CnfReader** -- simple config-files reader
- **ContainerOutput** -- gwLogger (simple singleton Logger) and std container_output library
- **csv** -- simple csv-writer
- **Date** -- try to work with date and time
- **dll_loader** -- RAII-wrapper for work with dll. Sutable for windows and linux. Class DllLoader
- **iniParser** -- Simple ini-reader/writer
- **Math** -- math library
- **MetrologicNumbers** -- class to work with quantities as a value and uncertainty (class MetrNumber)
- **MultiThreadingUtils** – synchronized template
- **profiler** -- simple profiler (classes LogDuration and AddDuration)
- **rapidjson_getters** -- shortcut get functions for rapidjson library
- **StringUnits** -- units to work with string and files
- **TestFrameWork** -- simple test framework for unit tests (class TestRunner)

## Algorithm

### `algo_lib.h`

- **`max_element_if(first, last, p)`** – returns an iterator to the maximum element in `[first, last)` that satisfies unary predicate `p`; returns `last` if no such element exists
- **`sumEqual(first, last, cmp, sump)`** – collapses consecutive elements that are considered equal by binary predicate `cmp` by accumulating them with binary function `sump` into the first of the group; returns a past-the-end iterator for the new logical range (similar to `std::unique` but summing instead of removing)
- **`sumVectors(vTo, vFrom)`** – adds `vFrom` element-wise into `vTo` (`vTo += vFrom`); both vectors must have the same size

### `iterator_range.h`

- **`IteratorRange<It>`** – lightweight class that holds a `[begin, end)` iterator pair and exposes `begin()`, `end()`, `size()`, and `empty()`; useful for passing sub-ranges without copying containers
- **`Head(container, top)`** – returns an `IteratorRange` covering the first `top` elements of `container` (clamped to `[0, size]`)
- **`asRange(container)`** – wraps any container in an `IteratorRange` over its full extent

### `lazy_value.h`

- **`LazyValue<T>`** – stores a value that is computed on first access only; constructed with an `std::function<T()>` initializer; exposes `get()` (computes and caches on first call) and `hasValue()` (checks whether the value has been computed yet)

### `object_pool.h`

- **`ObjectPool<T>`** – memory pool for objects of type `T`; `allocate()` returns a pointer (reusing a freed object or allocating a new one), `tryAllocate()` returns `nullptr` if the free list is empty, `deallocate(ptr)` returns the object to the pool; destructor frees all memory

### `dictionary.h`

- **`Dict<K, V>`** – ordered dictionary that combines `std::unordered_map` (O(1) lookup) with `std::list` (insertion-order iteration); exposes the same interface as `std::unordered_map` (`operator[]`, `at`, `get`, `find`, `count`, `contains`, `erase`, `clear`, `size`, `empty`, `begin`, `end`), but iterating over a `Dict` yields elements in the order they were inserted

### `double_counter_map.h`

- **`DoubleCounterMap<T>`** – maps floating-point values to counters with approximate equality (within a configurable `epsilon`); `add_value(value)` increments the counter for a matching key or inserts a new one with count 1; `inc_value_cnt(value, cnt)` increments by `cnt`; `getCounterDict()` returns a read-only reference to the underlying `std::map<double, T>`; `clear()` resets the map

### `stack_vector.h`

- **`StackVector<T, N>`** – fixed-capacity vector backed by `std::array<T, N>` (stack-allocated, no heap); supports `push_back`, `pop_back`, `operator[]`, `front`, `back`, `begin`, `end`, `size`, `capacity`, `empty`, and `clear`; throws `std::invalid_argument` on construction if `size > N` and `std::overflow_error` on `push_back` when full

## BinaryFStream

### `bintext_fstream.h`

- **`BinTxtIFStream`** – input stream adapter for reading text data embedded in binary files; wraps `std::ifstream` opened in binary mode and provides line-oriented and name=value parsing on top of raw binary reads. Not copyable. Key capabilities:
  - reads text lines with a configurable line separator (default `'\n'`)
  - reads `name=value` pairs up to a specified stop-name, with a configurable separator (default `'='`)
  - reads numeric values stored in binary format via the templated `read_number<T>(value)` method
  - converts to `bool` to check stream health (mirrors `std::ifstream::operator bool`)
  - free function `getline(BinTxtIFStream&, line, sep)` mirrors the standard `std::getline` interface and returns `true` if the line is non-empty

## CnfReader

### `cnfreader.h`

- **`CnfReader`** – simple config-file parser for `name = value` text files; supports `#` and `//` comment lines. Can be constructed from a filename or an existing `std::istream`. The separator string between name and value is configurable, as is an optional decimal separator for floating-point values. All values are stored internally as strings and converted on demand. Key methods:
  - **`hasValue(name)`** – returns `true` if the key was found in the file
  - **`getStringValue(name)`** – returns the raw string value for a key
  - **`getValue<T>(name)`** – returns the value converted to type `T` (`bool`, integral, floating-point, or any stream-extractable type); throws `std::invalid_argument` if the key is missing or has a bad type
  - **`getOptValue<T>(name)`** – same as `getValue` but returns `std::optional<T>`; returns `std::nullopt` instead of throwing
  - **`getValueDef<T>(name, default)`** – returns the converted value or `default` if the key is absent
  - **`updateValueIfExists<T>(name, value)`** – overwrites `value` in-place only if the key exists; leaves it unchanged otherwise
  - **`setValue(name, value)`** – adds or updates a key programmatically
  - **`saveToFile(filename)`** – serialises the current key-value map back to a file

## csv

### `csv_writer.h`

- **`CsvWriter`** – simple CSV writer that outputs values to an `std::ostream` or a file; the separator character is configurable (default `,`). Not copyable. Usage:
  - **`operator<<(value)`** – writes a single value, automatically prepending the separator after the first column; `std::string` and `std::string_view` values are automatically enclosed in double quotes
  - **`writeLine(sequence, is_end_line)`** – writes all elements of a vector as a row; optionally calls `endLine()` at the end
  - **`endLine()`** – writes a newline and resets the column position to the start of a new row
  - Can be constructed from an existing `std::ostream` or from a filename (with optional append mode)

### `csv_reader.h`

- **`CsvReader`** – simple CSV reader that parses a file line by line or as a column dictionary; the separator character is configurable (default `,`), and header handling is optional. Not copyable. Usage:
  - **`readLine()`** – reads the next data row and returns it as `std::optional<std::vector<std::string>>`; returns `std::nullopt` at end of file; the first line is treated as a header and parsed separately on first call if `has_header` is `true`
  - **`readColumns()`** – reads the entire file and returns an `std::unordered_map<std::string, std::vector<std::string>>` mapping each column name to its values

## dll_loader

### `dll_loader.h`

- **`DllLoader`** – cross-platform RAII wrapper for loading shared libraries (`.dll` on Windows, `.so` on Linux) using the native OS API (`LoadLibrary` / `dlopen`). Not copyable, but movable. Key behaviour:
  - constructed from a library filename; throws `std::invalid_argument` if the library cannot be opened
  - destructor automatically unloads the library (`FreeLibrary` / `dlclose`)
  - **`loadFunction<ProcType>(name)`** – resolves a function by name and returns it as the requested function-pointer type; throws `std::invalid_argument` (with the OS error code on Windows) if the symbol is not found
  - **`loadFunctionNoThrow<ProcType>(name)`** – same but returns `nullptr` instead of throwing when the symbol is absent

- **`tryLoadDllFromNames(dll_names)`** – attempts to load libraries from a list of names in order, returning an `std::optional<DllLoader>` for the first one that succeeds; useful for writing platform-independent code where the library filename differs across operating systems

## iniParser

### `iniparser.h`

- **`IniParser`** – ini-file parser and writer that supports sections (`[section_name]`), `name = value` pairs, and `#` / `//` comment lines. Internally stores data in insertion-order `Dict` containers so the original section and key order is preserved on write-back. Can be constructed from a filename or an existing `std::istream`; an optional decimal separator can be supplied for locale-aware float parsing. Key methods:
  - **`hasSection(section)`** – returns `true` if the section exists
  - **`hasValue(section, key)`** – returns `true` if the key exists within the given section
  - **`getStringValue(section, key)`** / **`getStringValueDef(section, key, default)`** – returns the raw string value (or a default)
  - **`getValue<T>(section, key)`** – returns the value converted to type `T` (`bool`, integral, floating-point, or any stream-extractable type); throws `std::invalid_argument` if missing or unconvertible
  - **`getOptValue<T>(section, key)`** – same as `getValue` but returns `std::optional<T>`; returns `std::nullopt` if the section or key is absent
  - **`getValueDef<T>(section, key, default)`** – returns the converted value or `default` if the section or key is absent
  - **`updateValueIfExists<T>(section, key, value)`** – overwrites `value` in-place only if the key exists; leaves it unchanged otherwise
  - **`setValue<T>(section, key, value)`** – adds or updates a key (creates the section if needed); dispatches to type-specific setters for `bool`, integral, floating-point, and `std::string`; falls back to `operator<<` for other types
  - **`writeToFile(filename)`** / **`writeToStream(out)`** – serialises the current data back to ini format, preserving section and key order
