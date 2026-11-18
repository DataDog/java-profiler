---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:20:06 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (5 unique values: 63-94 cores)</summary>

```
1795014940 63
1795014945 63
1795014950 63
1795014955 63
1795014960 91
1795014965 91
1795014970 91
1795014975 91
1795014980 91
1795014985 94
1795014990 94
1795014995 94
1795015000 94
1795015005 72
1795015010 72
1795015015 72
1795015020 72
1795015025 72
1795015030 72
1795015035 74
```
</details>

---

