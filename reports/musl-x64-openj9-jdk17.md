---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 21:59:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 41-62 cores)</summary>

```
1793674431 62
1793674436 62
1793674441 62
1793674446 62
1793674451 62
1793674456 62
1793674461 62
1793674466 62
1793674471 62
1793674476 62
1793674481 62
1793674486 62
1793674491 62
1793674496 62
1793674501 62
1793674506 62
1793674511 41
1793674516 41
1793674521 41
1793674526 41
```
</details>

---

