---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 07:29:49 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 85-90 cores)</summary>

```
1791372292 88
1791372297 88
1791372302 88
1791372307 88
1791372312 88
1791372317 88
1791372322 88
1791372327 88
1791372332 88
1791372337 88
1791372342 88
1791372347 88
1791372352 88
1791372357 90
1791372362 90
1791372367 90
1791372372 90
1791372377 90
1791372382 90
1791372387 90
```
</details>

---

