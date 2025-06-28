# 批量重命名脚本
Get-ChildItem -Path . -Filter "click (*).png" | ForEach-Object {
    # 从文件名中提取数字
    $currentNumber = [regex]::Match($_.Name, 'click \((\d+)\)\.png').Groups[1].Value
    
    if ($currentNumber) {
        # 计算新数字：原始数字 + 19
        $newNumber = [int]$currentNumber + 19
        
        # 构造新文件名
        $newName = "$newNumber.png"
        
        # 执行重命名
        Rename-Item -Path $_.FullName -NewName $newName
        
        # 显示操作结果
        Write-Host "rename: $($_.Name) -> $newName"
    }
}
Write-Host "Finish！"