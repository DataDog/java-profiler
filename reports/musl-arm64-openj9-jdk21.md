---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 16:31:53 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1786393540 53
1786393545 64
1786393550 64
1786393555 64
1786393560 64
1786393565 64
1786393570 64
1786393575 64
1786393580 64
1786393585 64
1786393590 64
1786393595 64
1786393600 64
1786393605 64
1786393610 64
1786393615 64
1786393620 53
1786393625 53
1786393630 53
1786393635 53
```
</details>

---

