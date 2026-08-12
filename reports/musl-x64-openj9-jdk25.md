---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-12 04:18:25 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 31-35 cores)</summary>

```
1786522434 35
1786522439 35
1786522444 33
1786522449 33
1786522454 33
1786522459 33
1786522464 33
1786522469 33
1786522474 33
1786522479 33
1786522484 33
1786522489 33
1786522494 33
1786522499 33
1786522504 33
1786522509 33
1786522514 33
1786522519 33
1786522524 31
1786522529 31
```
</details>

---

