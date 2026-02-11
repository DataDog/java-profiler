---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:58:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 12 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 61-68 cores)</summary>

```
1770828749 65
1770828754 65
1770828759 65
1770828764 65
1770828769 65
1770828774 65
1770828779 65
1770828784 65
1770828789 65
1770828794 65
1770828799 65
1770828804 65
1770828809 61
1770828814 61
1770828819 61
1770828824 68
1770828829 68
1770828834 63
1770828839 63
1770828844 61
```
</details>

---

