---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:44:53 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1794587956 83
1794587961 83
1794587966 83
1794587971 83
1794587976 83
1794587981 83
1794587986 83
1794587991 83
1794587996 83
1794588001 83
1794588006 85
1794588011 85
1794588016 85
1794588021 85
1794588026 85
1794588031 85
1794588036 85
1794588041 85
1794588046 85
1794588051 85
```
</details>

---

