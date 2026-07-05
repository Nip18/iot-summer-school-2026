import os

def count_ino_files():
    ino_count = 0
    # to walk through all directories and subdirectories
    for root, dirs, files in os.walk('.'):
        # to skkip hidden Git tracking directories
        if '.git' in root:
            continue
        for file in files:
            if file.endswith('.ino'):
                ino_count += 1
                print(f"Found Arduino sketch: {os.path.join(root, file)}")
                
    print("\n" + "="*30)
    print(f"Total number of .ino files: {ino_count}")
    print("="*30)

if __name__ == "__main__":
    count_ino_files()
