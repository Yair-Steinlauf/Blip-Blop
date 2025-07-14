import os
import re

def remove_cpp_comments(file_path):
    """
    מוחק הערות // מקובץ C++ תוך שמירה על הפורמט הכללי
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
    except UnicodeDecodeError:
        # אם יש בעיה עם קידוד UTF-8, נסה עם קידוד אחר
        with open(file_path, 'r', encoding='latin-1') as file:
            content = file.read()
    
    # מחיקת הערות // רק אם הן לא בתוך מחרוזת
    # הביטוי הרגולרי מתחשב במחרוזות עם גרש יחיד ודו-גרש
    lines = content.split('\n')
    processed_lines = []
    
    for line in lines:
        # בדיקה אם יש הערה בשורה
        in_string = False
        in_char = False
        escaped = False
        comment_pos = -1
        
        i = 0
        while i < len(line):
            char = line[i]
            
            if escaped:
                escaped = False
                i += 1
                continue
                
            if char == '\\' and (in_string or in_char):
                escaped = True
                i += 1
                continue
                
            if char == '"' and not in_char:
                in_string = not in_string
            elif char == "'" and not in_string:
                in_char = not in_char
            elif char == '/' and i + 1 < len(line) and line[i + 1] == '/' and not in_string and not in_char:
                comment_pos = i
                break
                
            i += 1
        
        # אם נמצאה הערה, חתוך את השורה
        if comment_pos != -1:
            line = line[:comment_pos].rstrip()
        
        processed_lines.append(line)
    
    # כתיבה חזרה לקובץ
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write('\n'.join(processed_lines))

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
    
    for root, dirs, files in os.walk(directory_path):
        for file in files:
            # בדיקה אם הקובץ הוא קובץ C++
            file_extension = os.path.splitext(file)[1].lower()
            if file_extension in cpp_extensions:
                file_path = os.path.join(root, file)
                print(f"מעבד קובץ: {file_path}")
                
                try:
                    remove_cpp_comments(file_path)
                    files_processed += 1
                    print(f"✓ הושלם: {file_path}")
                except Exception as e:
                    print(f"✗ שגיאה בקובץ {file_path}: {str(e)}")
    
    print(f"\nהושלמה עיבוד {files_processed} קבצים בתיקיה {directory_path}")

def main():
    """
    פונקציה ראשית - מעבדת את תיקיות include ו-src
    """
    print("מתחיל תהליך מחיקת הערות מקבצי C++")
    print("="*50)
    
    # רשימת התיקיות לעיבוד
    directories = ['include', 'src']
    
    total_processed = 0
    
    for directory in directories:
        print(f"\nמעבד תיקיה: {directory}")
        print("-" * 30)
        
        if os.path.exists(directory):
            process_directory(directory)
        else:
            print(f"התיקיה {directory} לא נמצאה בתיקיה הנוכחית")
    
    print("\n" + "="*50)
    print("תהליך מחיקת ההערות הושלם!")
    print("\nהערה: מומלץ לבדוק את הקבצים ולוודא שהקוד עדיין עובד כראוי")
    print("מומלץ גם לגבות את הפרויקט לפני הרצת הסקריפט")

if __name__ == "__main__":
    main()