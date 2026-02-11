---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:58:27 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 13 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (5 unique values: 82-89 cores)</summary>

```
1770828704 83
1770828709 83
1770828714 83
1770828719 83
1770828724 83
1770828729 82
1770828734 82
1770828739 82
1770828744 83
1770828749 83
1770828754 83
1770828759 82
1770828764 82
1770828769 84
1770828774 84
1770828779 84
1770828784 85
1770828789 85
1770828794 89
1770828799 89
```
</details>

---

