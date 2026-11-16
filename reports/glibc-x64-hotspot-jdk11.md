---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:37:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 82-89 cores)</summary>

```
1794850064 82
1794850069 82
1794850074 82
1794850079 82
1794850084 82
1794850089 82
1794850094 82
1794850099 82
1794850104 82
1794850109 82
1794850114 82
1794850119 82
1794850124 82
1794850129 82
1794850134 82
1794850139 82
1794850144 82
1794850149 82
1794850154 82
1794850159 84
```
</details>

---

