---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:08:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (6 unique values: 81-91 cores)</summary>

```
1778090379 85
1778090384 85
1778090389 85
1778090394 85
1778090399 85
1778090404 85
1778090409 90
1778090414 90
1778090419 90
1778090424 90
1778090429 90
1778090434 91
1778090439 91
1778090444 91
1778090449 89
1778090454 89
1778090459 91
1778090464 91
1778090469 91
1778090474 86
```
</details>

---

