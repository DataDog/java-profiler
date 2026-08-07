---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 08:27:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 53-60 cores)</summary>

```
1786105424 60
1786105429 60
1786105434 60
1786105439 60
1786105444 60
1786105449 60
1786105454 60
1786105459 60
1786105464 60
1786105469 60
1786105474 60
1786105479 55
1786105484 55
1786105489 53
1786105494 53
1786105499 53
1786105504 53
1786105509 53
1786105514 53
1786105519 53
```
</details>

---

