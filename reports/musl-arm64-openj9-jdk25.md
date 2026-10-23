---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 08:55:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 34 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (5 unique values: 36-45 cores)</summary>

```
1792759860 41
1792759865 41
1792759870 41
1792759875 41
1792759880 41
1792759885 41
1792759890 41
1792759895 36
1792759901 36
1792759906 36
1792759911 36
1792759916 37
1792759921 37
1792759926 39
1792759931 39
1792759936 39
1792759941 39
1792759946 39
1792759951 39
1792759956 39
```
</details>

---

