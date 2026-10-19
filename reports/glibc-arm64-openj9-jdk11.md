---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-19 14:36:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 12 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1792434745 22
1792434750 24
1792434755 24
1792434760 24
1792434765 24
1792434770 24
1792434775 24
1792434780 24
1792434785 24
1792434790 24
1792434795 24
1792434800 24
1792434805 24
1792434810 24
1792434815 24
1792434820 24
1792434825 24
1792434830 24
1792434835 24
1792434840 24
```
</details>

---

