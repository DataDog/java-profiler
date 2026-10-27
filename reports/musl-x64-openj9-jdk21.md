---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:00:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 853 |
| Sample Rate | 14.22/sec |
| Health Score | 889% |
| Threads | 12 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793098429 94
1793098434 94
1793098439 94
1793098444 94
1793098449 94
1793098454 94
1793098459 94
1793098464 94
1793098469 94
1793098474 94
1793098479 94
1793098484 94
1793098489 94
1793098494 94
1793098499 94
1793098504 94
1793098509 96
1793098514 96
1793098519 96
1793098524 96
```
</details>

---

