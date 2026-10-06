# legacy_link_definitions

链接时附加此静态库，解决部分VC6的静态库，在用VC6之后的链接器链接时，缺少timezone符号无法链接的问题。

## 使用方法

1. 前往 [Releases 下载页面](https://github.com/aiqinxuancai/legacy_link_definitions/releases)，根据使用的链接器版本选择 VC2017、VC2022 或 VC2026 的 Win32 压缩包。
2. 将压缩包中的 `legacy_link_definitions.lib` 解压到链接器的 `lib` 目录中，并确保该目录中也有 `legacy_stdio_definitions.lib`（本项目的压缩包不包含此文件）。
3. 打开链接器的 INI 配置文件，添加或修改 `extra_args` 配置项：

```ini
extra_args=/DYNAMICBASE "legacy_stdio_definitions.lib" "legacy_link_definitions.lib"
```

如果已有其他 `extra_args` 参数，请合并到同一配置项中，保留原有需要的参数。保存配置后重新编译链接。

## 自动构建与发布

GitHub Actions 会在分支推送、Pull Request 和手动运行时编译以下 Release 静态库：

| 编译器 | 工具集 | 构建环境 | 平台 |
| --- | --- | --- | --- |
| VC2017 | v141 | Windows Server 2022 / VS2022，按需安装 v141 | Win32 |
| VC2022 | v143 | Windows Server 2022 / VS2022 | Win32 |
| VC2026 | v145 | Windows Server 2025 / VS2026 | Win32 |

VC2017 产物使用 VS2017 的 v141 编译器，由 VS2022 的 MSBuild 驱动构建。
构建时通过命令行选择工具集，并检测已完整安装的最新 Windows SDK，传入完整版本号（如 `10.0.26100.0`），兼容 v141 对 SDK 版本的要求。同时关闭全程序优化（`/GL`），避免静态库依赖特定版本的 LTCG 链接器。
每个构建生成一个 ZIP，包含 `legacy_link_definitions.lib` 和本说明，可在 Actions 页面的 Artifacts 中下载。
例如：`legacy_link_definitions-vc2022-Win32-Release.zip`，其中 Win32 表示 x86。

仅构建和发布 Win32（x86），不生成 x64 产物。

推送以 `v` 开头的标签会在三个构建全部成功后自动创建 GitHub Release，并上传三个 ZIP：

```sh
git tag v1.0.0
git push origin v1.0.0
```

重新运行同一标签的工作流会更新已有 Release 的同名附件。普通分支构建只上传 Artifacts，不发布 Release。
发布使用 GitHub 自动提供的 `GITHUB_TOKEN`，无需另配令牌。
