---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:02:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 67-74 cores)</summary>

```
1789995403 72
1789995408 72
1789995413 72
1789995418 72
1789995423 72
1789995428 72
1789995433 67
1789995438 67
1789995443 67
1789995448 67
1789995453 69
1789995458 69
1789995463 69
1789995468 69
1789995473 69
1789995478 69
1789995483 69
1789995488 69
1789995493 69
1789995498 69
```
</details>

---

