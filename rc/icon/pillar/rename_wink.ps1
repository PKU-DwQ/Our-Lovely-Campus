# 修正后的重命名脚本
Get-ChildItem -Path . -Filter "click-眨眼 (*).png" | ForEach-Object {
    # 精确匹配文件名格式
    if ($_.Name -match '^click-眨眼 \((\d+)\)\.png$') {
        $currentNumber = [int]$matches[1]
        $newNumber = $currentNumber + 20
        $newName = "$newNumber.png"
        
        # 执行重命名并显示结果
        Rename-Item -Path $_.FullName -NewName $newName -ErrorAction Stop
        Write-Host "✅ 成功重命名: $($_.Name) -> $newName" -ForegroundColor Green
    }
    else {
        Write-Host "❌ 未匹配的文件: $($_.Name)" -ForegroundColor Yellow
    }
}
Write-Host "所有文件处理完成。" -ForegroundColor Cyan