---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 10:30:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 30-64 cores)</summary>

```
1786112738 44
1786112743 44
1786112748 44
1786112753 44
1786112758 44
1786112763 44
1786112768 44
1786112773 44
1786112778 44
1786112783 44
1786112788 44
1786112793 44
1786112798 44
1786112803 44
1786112808 44
1786112813 44
1786112818 44
1786112823 64
1786112828 64
1786112833 64
```
</details>

---

