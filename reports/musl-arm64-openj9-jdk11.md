---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-11 11:15:03 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791731355 30
1791731360 30
1791731365 30
1791731370 30
1791731375 30
1791731380 30
1791731385 30
1791731390 30
1791731395 30
1791731400 30
1791731405 30
1791731410 30
1791731415 30
1791731420 30
1791731425 30
1791731430 30
1791731435 30
1791731440 30
1791731445 30
1791731450 30
```
</details>

---

