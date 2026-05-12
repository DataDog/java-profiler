---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 02:56:28 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1778568619 47
1778568624 47
1778568629 47
1778568634 47
1778568639 47
1778568644 52
1778568649 52
1778568654 52
1778568659 52
1778568664 52
1778568669 52
1778568674 52
1778568679 52
1778568684 52
1778568689 52
1778568694 52
1778568699 52
1778568704 52
1778568709 52
1778568714 52
```
</details>

---

