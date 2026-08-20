---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 20:19:42 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1787184912 40
1787184917 40
1787184922 40
1787184927 40
1787184932 40
1787184937 40
1787184942 40
1787184947 40
1787184952 40
1787184957 40
1787184962 44
1787184967 44
1787184972 48
1787184977 48
1787184982 48
1787184987 48
1787184992 48
1787184997 48
1787185002 48
1787185007 48
```
</details>

---

