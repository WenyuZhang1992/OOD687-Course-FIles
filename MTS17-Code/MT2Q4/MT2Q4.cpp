/////////////////////////////////////////////////////////////////////
// MT2Q4.cpp - Package Dependency Storage class                    //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

class PackageDependency
{
public:
  using File = std::string;
  using Dependencies = std::vector<File>;
  using DepMap = std::unordered_map<File, Dependencies>;

  PackageDependency& add(const File& parent, const File& child)
  {
    if (hasKey(parent))
      depRel[parent].push_back(child);
    else
    {
      Dependencies d;
      d.push_back(child);
      depRel[parent] = d;
    }
    return *this;
  }

  Dependencies get(const File& file)
  {
    if (hasKey(file))
      return depRel[file];
    else
    {
      Dependencies d;
      return d;
    }
  }

  void show()
  {
    DepMap::iterator iter = depRel.begin();
    for (iter = depRel.begin(); iter != depRel.end(); ++iter)
    {
      std::cout << "\n  " << iter->first;
      for (File f : iter->second)
        std::cout << "\n    " << f;
    }
  }
  void clear()
  {
    depRel.clear();
  }
private:
  bool hasKey(const File& f)
  {
    if (depRel.find(f) == depRel.end())
      return false;
    return true;
  }
  DepMap depRel;
};

int main()
{
  std::cout << "\n  MT2Q4 - Package Dependency Container";
  std::cout << "\n ======================================";
  PackageDependency pd;
  pd.add("file1", "file2").add("file1", "file3");
  pd.add("file2", "file1").add("file2", "file4").add("file2", "file5");
  pd.add("file4", "file3");
  pd.show();
  std::cout << "\n\n  file2 has dependencies: ";
  for (PackageDependency::File f : pd.get("file2"))
    std::cout << f << " ";
  std::cout << "\n\n";
}
