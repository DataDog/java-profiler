---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 07:48:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 11 |
| Allocations | 181 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790682250 43
1790682255 43
1790682260 43
1790682265 43
1790682270 43
1790682275 43
1790682280 43
1790682285 43
1790682290 43
1790682295 43
1790682300 43
1790682305 43
1790682310 43
1790682315 43
1790682320 43
1790682325 43
1790682330 43
1790682335 48
1790682340 48
1790682345 48
```
</details>

---

