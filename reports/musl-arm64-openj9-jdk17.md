---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:30:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790090668 48
1790090673 48
1790090678 48
1790090683 48
1790090688 48
1790090693 48
1790090698 48
1790090703 48
1790090708 48
1790090713 48
1790090718 48
1790090723 48
1790090728 48
1790090733 36
1790090738 36
1790090743 36
1790090748 36
1790090753 36
1790090758 36
1790090763 36
```
</details>

---

