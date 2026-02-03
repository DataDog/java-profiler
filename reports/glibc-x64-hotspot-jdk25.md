---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 05:39:37 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 8 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770114748 32
1770114753 32
1770114758 32
1770114763 32
1770114768 32
1770114773 32
1770114778 32
1770114783 32
1770114788 30
1770114793 30
1770114798 30
1770114803 30
1770114808 30
1770114813 30
1770114818 30
1770114823 30
1770114828 30
1770114833 30
1770114838 30
1770114843 30
```
</details>

---

