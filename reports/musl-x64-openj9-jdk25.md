---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:40:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 46-56 cores)</summary>

```
1790238928 56
1790238933 56
1790238938 56
1790238943 56
1790238948 46
1790238953 46
1790238958 46
1790238963 46
1790238968 46
1790238973 46
1790238978 46
1790238984 46
1790238989 46
1790238994 46
1790238999 46
1790239004 46
1790239009 46
1790239014 46
1790239019 46
1790239024 46
```
</details>

---

