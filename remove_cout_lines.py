import os
import re

def remove_cout_lines(file_path):
    """
    מוחק כל השורות שמכילות std::cout מקובץ C++
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            lines = file.readlines()
    except UnicodeDecodeError:
        # אם יש בעיה עם קידוד UTF-8, נסה עם קידוד אחר
        with open(file_path, 'r', encoding='latin-1') as file:
            lines = file.readlines()
    
    original_line_count = len(lines)
    filtered_lines = []
    removed_lines = []
    
    for i, line in enumerate(lines):
        # בדיקה אם השורה מכילה std::cout
        if 'std::cout' in line:
            removed_lines.append((i + 1, line.strip()))
        else:
            filtered_lines.append(line)
    
    # כתיבה חזרה לקובץ
    with open(file_path, 'w', encoding='utf-8') as file:
        file.writelines(filtered_lines)
    
    return original_line_count, len(filtered_lines), removed_lines

def process_directory(directory_path):
    """
    עובר על כל הקבצים בתיקיה ובתיקיות הפנימיות
    """
    if not os.path.exists(directory_path):
        print(f"התיקיה {directory_path} לא קיימת")
        return
    
    # סוגי קבצים שרלוונטיים לC++
    cpp_extensions = ['.cpp', '.cxx', '.cc', '.c', '.h', '.hpp', '.hxx']
    
    files_processed = 0
    total_lines_removed = 0
    
    for root, dirs, files in os.walk(directory_path):
        for file in files:
            # בדיקה אם הקובץ הוא קובץ C++
            file_extension = os.path.splitext(file)[1].lower()
            if file_extension in cpp_extensions:
                file_path = os.path.join(root, file)
                print(f"מעבד קובץ: {file_path}")
                
                try:
                    original_count, new_count, removed_lines = remove_cout_lines(file_path)
                    files_processed += 1
                    lines_removed = original_count - new_count
                    total_lines_removed += lines_removed
                    
                    if lines_removed > 0:
                        print(f"✓ הושלם: {file_path}")
                        print(f"  הוסרו {lines_removed} שורות std::cout")
                        
                        # הדפסת השורות שהוסרו (אופציונלי)
                        if lines_removed <= 5:  # מציג רק אם יש מעט שורות
                            for line_num, line_content in removed_lines:
                                print(f"    שורה {line_num}: {line_content}")
                        else:
                            print(f"    דוגמאות לשורות שהוסרו:")
                            for line_num, line_content in removed_lines[:3]:
                                print(f"    שורה {line_num}: {line_content}")
                            print(f"    ... ועוד {lines_removed - 3} שורות")
                    else:
                        print(f"✓ הושלם: {file_path} (לא נמצאו שורות std::cout)")
                        
                except Exception as e:
                    print(f"✗ שגיאה בקובץ {file_path}: {str(e)}")
    
    print(f"\nהושלמה עיבוד {files_processed} קבצים בתיקיה {directory_path}")
    print(f"סה\"כ הוסרו {total_lines_removed} שורות std::cout")

def main():
    """
    פונקציה ראשית - מעבדת את תיקיות include ו-src
    """
    print("מתחיל תהליך מחיקת שורות std::cout מקבצי C++")
    print("="*60)
    
    # שאלת אישור מהמשתמש
    response = input("האם אתה בטוח שברצונך למחוק את כל שורות std::cout? (כן/לא): ").lower()
    if response not in ['כן', 'yes', 'y']:
        print("התהליך בוטל.")
        return
    
    # רשימת התיקיות לעיבוד
    directories = ['include', 'src']
    
    total_files_processed = 0
    total_lines_removed = 0
    
    for directory in directories:
        print(f"\nמעבד תיקיה: {directory}")
        print("-" * 40)
        
        if os.path.exists(directory):
            process_directory(directory)
        else:
            print(f"התיקיה {directory} לא נמצאה בתיקיה הנוכחית")
    
    print("\n" + "="*60)
    print("תהליך מחיקת שורות std::cout הושלם!")
    print("\nהערות חשובות:")
    print("• וודא שהקוד עדיין מתקמפל ועובד כראוי")
    print("• יתכן שתצטרך להסיר #include <iostream> אם הוא לא בשימוש")
    print("• מומלץ לבדוק שלא הוסרו שורות חיוניות בטעות")

if __name__ == "__main__":
    main()