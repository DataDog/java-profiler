---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 07:57:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 14 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793274843 30
1793274848 30
1793274853 30
1793274858 30
1793274863 30
1793274868 30
1793274873 30
1793274878 30
1793274883 30
1793274888 30
1793274893 30
1793274898 30
1793274903 30
1793274908 30
1793274913 30
1793274918 30
1793274923 30
1793274928 30
1793274933 30
1793274938 30
```
</details>

---

