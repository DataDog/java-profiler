---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:12:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (3 unique values: 26-32 cores)</summary>

```
1770134721 26
1770134726 26
1770134731 26
1770134736 26
1770134741 26
1770134746 26
1770134751 26
1770134756 26
1770134761 26
1770134766 26
1770134771 26
1770134776 26
1770134781 26
1770134786 26
1770134791 30
1770134796 30
1770134801 30
1770134806 30
1770134811 32
1770134816 32
```
</details>

---

