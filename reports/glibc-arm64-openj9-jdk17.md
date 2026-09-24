---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:38:22 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790238824 50
1790238829 50
1790238834 50
1790238839 50
1790238844 50
1790238849 50
1790238854 50
1790238859 50
1790238864 50
1790238869 50
1790238874 50
1790238879 50
1790238884 50
1790238889 50
1790238894 50
1790238899 50
1790238904 50
1790238909 50
1790238914 50
1790238919 50
```
</details>

---

