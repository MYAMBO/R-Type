## Data

The **Data** component acts as a flexible, generic storage container for an entity.  
It allows associating arbitrary metadata (key-value pairs of strings) with an entity without needing to create a specific component for every small piece of information (e.g., storing an enemy's specific sub-type, a dialogue ID, or a state description).

---

### Public Methods

| Method | Signature | Description |
|:------|:----------|:------------|
| **Get all data** | `std::map<std::string, std::string> getDataSet() const;` | Returns the entire map of key-value pairs stored in the component. |
| **Get value** | `std::string getData(const std::string& key) const;` | Retrieves the value associated with a specific key. Behavior is undefined if key doesn't exist (use `hasData` first). |
| **Check existence** | `bool hasData(const std::string& key) const;` | Returns `true` if the specified key exists in the data set. |
| **Set all data** | `void setDataSet(const std::map<std::string, std::string>& data);` | Replaces the current data set with a new map. |
| **Set value** | `void setData(const std::string& key, const std::string& value);` | Inserts or updates a key-value pair. |

---

### Constructor

| Constructor | Signature | Description |
|:------------|:----------|:------------|
| **Data** | `Data(std::map<std::string, std::string> data = {});` | Initializes the component, optionally with a pre-filled map of data. |

---

### Internal Data

```mermaid
classDiagram
  class Data {
    - _data: std::map~string, string~
    + Data(data: map)
    + getDataSet() map
    + getData(key: strin