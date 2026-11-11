---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:06:29 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1794430832 52
1794430837 64
1794430842 64
1794430847 64
1794430852 64
1794430857 64
1794430862 64
1794430867 64
1794430872 64
1794430877 64
1794430882 64
1794430887 51
1794430892 51
1794430897 51
1794430902 51
1794430907 51
1794430913 51
1794430918 51
1794430923 51
1794430928 51
```
</details>

---

