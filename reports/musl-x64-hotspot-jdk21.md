---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 13:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1794939896 62
1794939901 62
1794939906 62
1794939911 62
1794939916 62
1794939921 62
1794939926 62
1794939931 62
1794939936 62
1794939941 62
1794939946 64
1794939951 64
1794939956 64
1794939961 64
1794939966 64
1794939971 64
1794939976 64
1794939981 64
1794939986 64
1794939991 64
```
</details>

---

