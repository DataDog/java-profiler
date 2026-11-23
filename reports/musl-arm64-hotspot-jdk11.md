---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 10:21:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 11 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 14 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795447008 34
1795447013 34
1795447018 34
1795447023 34
1795447028 34
1795447033 34
1795447038 34
1795447043 34
1795447048 34
1795447053 29
1795447059 29
1795447064 29
1795447069 29
1795447074 29
1795447079 29
1795447084 29
1795447089 29
1795447094 29
1795447099 29
1795447104 29
```
</details>

---

