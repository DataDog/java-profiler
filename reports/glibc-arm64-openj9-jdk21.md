---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-15 00:57:36 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1786769628 34
1786769633 34
1786769638 34
1786769643 34
1786769648 34
1786769653 34
1786769658 34
1786769663 34
1786769668 34
1786769673 34
1786769678 34
1786769683 34
1786769688 32
1786769693 32
1786769698 32
1786769703 32
1786769708 32
1786769713 32
1786769718 32
1786769723 32
```
</details>

---

