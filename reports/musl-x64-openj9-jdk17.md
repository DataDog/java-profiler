---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 05:01:30 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1789721660 42
1789721665 42
1789721670 42
1789721675 42
1789721680 42
1789721685 44
1789721690 44
1789721695 44
1789721700 44
1789721705 44
1789721710 44
1789721715 44
1789721720 44
1789721725 44
1789721730 44
1789721735 44
1789721740 44
1789721745 44
1789721750 44
1789721755 44
```
</details>

---

