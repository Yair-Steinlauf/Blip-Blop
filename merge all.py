import os

def extract_cpp_code_to_file(output_filename='merged_code.txt'):
    # תיקיות לחיפוש
    folders_to_search = ['src', 'include']
    
    # סיומות קבצים של C++ לזיהוי
    cpp_extensions = {'.cpp', '.h', '.hpp', '.cxx', '.hxx', '.cc', '.c', '.inl'}
    
    # פתיחת קובץ הפלט
    with open(output_filename, 'w', encoding='utf-8') as outfile:
        for folder in folders_to_search:
            if not os.path.exists(folder):
                print(f"Warning: Folder '{folder}' does not exist, skipping...")
                continue
                
            # סריקה רקורסיבית של התיקייה
            for root, dirs, files in os.walk(folder):
                for file in files:
                    # בדיקה אם הקובץ הוא קובץ C++
                    if any(file.endswith(ext) for ext in cpp_extensions):
                        file_path = os.path.join(root, file)
                        try:
                            # כתיבת נתיב הקובץ כהפרדה
                            outfile.write(f"\n\n// ====== File: {file_path} ======\n\n")
                            
                            # קריאת תוכן הקובץ והוספה לפלט
                            with open(file_path, 'r', encoding='utf-8') as infile:
                                outfile.write(infile.read())
                                
                        except Exception as e:
                            print(f"Error processing file {file_path}: {str(e)}")

    print(f"All C++ code has been merged into {output_filename}")

# הרצת הפונקציה
extract_cpp_code_to_file()