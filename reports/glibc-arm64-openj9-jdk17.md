---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-05 11:34:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1785943748 56
1785943753 64
1785943758 64
1785943763 64
1785943768 64
1785943773 64
1785943779 64
1785943784 64
1785943789 64
1785943794 64
1785943799 64
1785943804 64
1785943809 64
1785943814 64
1785943819 64
1785943824 64
1785943829 64
1785943834 64
1785943839 64
1785943844 64
```
</details>

---

