---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 02:27:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794986604 51
1794986609 51
1794986614 51
1794986619 51
1794986624 51
1794986629 51
1794986634 51
1794986639 51
1794986644 51
1794986649 51
1794986654 51
1794986659 51
1794986664 51
1794986669 51
1794986674 51
1794986679 51
1794986684 51
1794986689 51
1794986694 51
1794986699 51
```
</details>

---

