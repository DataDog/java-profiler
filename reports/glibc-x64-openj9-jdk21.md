---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 08:37:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 82-87 cores)</summary>

```
1795440782 82
1795440787 82
1795440792 82
1795440797 82
1795440802 82
1795440807 82
1795440812 82
1795440817 82
1795440822 82
1795440827 82
1795440832 82
1795440837 85
1795440842 85
1795440847 85
1795440852 85
1795440857 87
1795440862 87
1795440867 87
1795440872 87
1795440877 87
```
</details>

---

