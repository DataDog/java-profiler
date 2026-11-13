---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 03:42:36 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 39-61 cores)</summary>

```
1794559013 39
1794559018 39
1794559023 39
1794559028 39
1794559033 39
1794559038 39
1794559043 39
1794559048 39
1794559053 39
1794559058 39
1794559063 39
1794559068 39
1794559073 39
1794559078 39
1794559083 47
1794559088 47
1794559093 55
1794559098 55
1794559103 55
1794559108 61
```
</details>

---

