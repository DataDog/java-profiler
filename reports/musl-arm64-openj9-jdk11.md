---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:21:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795641325 64
1795641330 64
1795641335 64
1795641340 64
1795641345 64
1795641350 64
1795641355 64
1795641360 64
1795641365 64
1795641370 64
1795641375 64
1795641380 64
1795641385 64
1795641390 64
1795641395 64
1795641400 64
1795641405 64
1795641410 64
1795641415 64
1795641420 64
```
</details>

---

