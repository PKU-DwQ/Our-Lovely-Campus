Get-ChildItem -Path . -Filter "*.png" | ForEach-Object {
    # 从文件名中提取数字（假设文件名格式为"数字.png"，如"20.png"）
    $currentNumber = [regex]::Match($_.Name, '^(\d+)\.png$').Groups[1].Value
    if ($currentNumber) {
        # 计算新数字：原始数字 / 2 - 1
        $newNumber = [int]$currentNumber / 2 - 1
        # 构造新文件名
        $newName = "$newNumber.png"
        # 执行重命名
        Rename-Item -Path $_.FullName -NewName $newName
        # 显示操作结果
        Write-Host "rename: $($_.Name) -> $newName"
    }
}
Write-Host "Finish！"