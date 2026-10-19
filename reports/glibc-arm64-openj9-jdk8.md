---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-18 21:25:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 8-13 cores)</summary>

```
1792372809 10
1792372814 10
1792372819 10
1792372824 9
1792372829 9
1792372834 9
1792372839 9
1792372844 9
1792372849 9
1792372854 8
1792372859 8
1792372864 8
1792372869 8
1792372874 8
1792372879 8
1792372884 8
1792372889 8
1792372894 8
1792372899 8
1792372904 8
```
</details>

---

