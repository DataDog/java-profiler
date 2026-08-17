---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 09:07:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1786971593 32
1786971598 32
1786971603 32
1786971608 32
1786971613 32
1786971618 32
1786971623 32
1786971628 32
1786971633 32
1786971638 29
1786971643 29
1786971648 31
1786971653 31
1786971658 31
1786971663 31
1786971668 31
1786971673 31
1786971678 31
1786971683 31
1786971688 31
```
</details>

---

