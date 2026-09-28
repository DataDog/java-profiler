---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:34:15 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (4 unique values: 24-38 cores)</summary>

```
1790605798 38
1790605803 38
1790605808 38
1790605813 38
1790605818 38
1790605823 38
1790605828 38
1790605833 38
1790605838 38
1790605843 38
1790605848 37
1790605853 37
1790605858 37
1790605863 37
1790605868 37
1790605873 37
1790605878 37
1790605883 38
1790605888 38
1790605893 33
```
</details>

---

