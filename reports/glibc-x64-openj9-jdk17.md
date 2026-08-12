---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 04:18:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 6-32 cores)</summary>

```
1786522394 6
1786522399 6
1786522404 6
1786522409 6
1786522414 6
1786522419 6
1786522424 6
1786522429 6
1786522434 6
1786522439 6
1786522444 6
1786522449 32
1786522454 32
1786522459 32
1786522464 32
1786522469 32
1786522474 32
1786522479 32
1786522484 32
1786522489 32
```
</details>

---

