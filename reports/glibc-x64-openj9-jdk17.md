---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:36:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1794594668 54
1794594673 54
1794594678 54
1794594683 54
1794594688 52
1794594693 52
1794594698 52
1794594703 52
1794594708 52
1794594713 52
1794594718 52
1794594723 52
1794594728 52
1794594733 52
1794594738 52
1794594743 52
1794594748 52
1794594753 52
1794594759 52
1794594764 52
```
</details>

---

