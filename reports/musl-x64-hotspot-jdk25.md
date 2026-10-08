---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 12:33:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1791476915 28
1791476920 28
1791476925 26
1791476930 26
1791476935 26
1791476940 26
1791476945 26
1791476950 26
1791476955 26
1791476960 26
1791476965 26
1791476970 26
1791476975 26
1791476980 26
1791476985 26
1791476990 26
1791476995 26
1791477000 26
1791477005 26
1791477010 26
```
</details>

---

