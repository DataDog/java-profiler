---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 05:59:56 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1790070781 16
1790070786 16
1790070791 16
1790070796 16
1790070801 16
1790070806 16
1790070811 16
1790070816 16
1790070821 16
1790070826 16
1790070831 16
1790070836 16
1790070841 16
1790070846 16
1790070851 16
1790070856 16
1790070861 16
1790070866 16
1790070871 16
1790070876 16
```
</details>

---

