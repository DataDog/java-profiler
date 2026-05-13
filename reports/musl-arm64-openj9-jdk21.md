---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-13 07:32:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 32-36 cores)</summary>

```
1778671548 32
1778671553 32
1778671558 32
1778671563 32
1778671568 32
1778671573 32
1778671578 32
1778671583 32
1778671588 36
1778671593 36
1778671598 36
1778671603 36
1778671608 36
1778671614 36
1778671619 36
1778671624 36
1778671629 36
1778671634 36
1778671639 36
1778671644 36
```
</details>

---

