---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 08:27:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 977 |
| Sample Rate | 16.28/sec |
| Health Score | 1018% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 40-52 cores)</summary>

```
1786105444 40
1786105449 40
1786105454 40
1786105459 40
1786105464 40
1786105469 40
1786105474 40
1786105479 40
1786105484 52
1786105489 52
1786105494 52
1786105499 52
1786105504 52
1786105509 52
1786105514 52
1786105519 52
1786105524 52
1786105529 52
1786105534 52
1786105539 52
```
</details>

---

