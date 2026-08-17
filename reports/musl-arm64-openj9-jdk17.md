---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-17 09:05:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 9 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 29-34 cores)</summary>

```
1786971568 34
1786971573 32
1786971578 32
1786971583 32
1786971588 32
1786971593 32
1786971598 32
1786971603 32
1786971608 32
1786971613 32
1786971618 32
1786971623 32
1786971628 32
1786971633 29
1786971638 29
1786971643 29
1786971648 31
1786971653 31
1786971658 31
1786971663 31
```
</details>

---

