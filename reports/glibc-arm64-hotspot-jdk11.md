---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 08:55:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792759897 51
1792759902 51
1792759907 51
1792759912 51
1792759917 51
1792759922 39
1792759927 39
1792759932 39
1792759937 39
1792759942 39
1792759947 39
1792759952 39
1792759957 39
1792759962 39
1792759967 39
1792759972 39
1792759978 39
1792759983 39
1792759988 39
1792759993 39
```
</details>

---

