---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 15:37:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 14 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 12-34 cores)</summary>

```
1795465977 12
1795465982 12
1795465987 12
1795465992 12
1795465997 12
1795466002 12
1795466007 12
1795466012 12
1795466018 17
1795466023 17
1795466028 17
1795466033 17
1795466038 34
1795466043 34
1795466048 34
1795466053 34
1795466058 34
1795466063 34
1795466068 34
1795466073 34
```
</details>

---

