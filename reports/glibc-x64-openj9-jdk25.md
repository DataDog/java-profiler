---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 07:38:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 26-32 cores)</summary>

```
1777462461 26
1777462466 26
1777462471 26
1777462476 26
1777462481 26
1777462486 26
1777462491 26
1777462496 26
1777462501 26
1777462506 26
1777462511 26
1777462516 26
1777462521 26
1777462526 26
1777462531 26
1777462536 26
1777462541 26
1777462546 26
1777462551 32
1777462556 32
```
</details>

---

