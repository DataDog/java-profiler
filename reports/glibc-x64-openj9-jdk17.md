---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:11:56 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (3 unique values: 16-47 cores)</summary>

```
1789743512 16
1789743517 16
1789743522 16
1789743527 16
1789743532 47
1789743537 47
1789743542 27
1789743547 27
1789743552 27
1789743557 27
1789743562 27
1789743567 27
1789743572 27
1789743577 27
1789743582 27
1789743587 27
1789743592 27
1789743597 27
1789743602 27
1789743607 27
```
</details>

---

