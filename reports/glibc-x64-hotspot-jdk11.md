---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:07:07 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (6 unique values: 80-88 cores)</summary>

```
1794502934 88
1794502939 88
1794502944 88
1794502949 88
1794502954 86
1794502959 86
1794502964 86
1794502969 86
1794502974 86
1794502979 86
1794502984 86
1794502989 86
1794502994 86
1794502999 84
1794503004 84
1794503009 84
1794503014 84
1794503019 82
1794503024 82
1794503029 82
```
</details>

---

