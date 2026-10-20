---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 01:06:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 14 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1792472528 23
1792472533 23
1792472538 23
1792472543 23
1792472548 23
1792472553 23
1792472558 23
1792472563 23
1792472568 23
1792472573 23
1792472578 23
1792472584 43
1792472589 43
1792472594 43
1792472599 43
1792472604 43
1792472609 43
1792472614 43
1792472619 43
1792472624 43
```
</details>

---

