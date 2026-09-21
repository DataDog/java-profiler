---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 05:26:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 25-45 cores)</summary>

```
1789982392 40
1789982397 40
1789982402 45
1789982407 45
1789982412 45
1789982417 45
1789982422 45
1789982427 25
1789982432 25
1789982437 25
1789982442 25
1789982447 25
1789982452 25
1789982457 25
1789982462 25
1789982467 25
1789982472 25
1789982477 25
1789982482 25
1789982487 25
```
</details>

---

