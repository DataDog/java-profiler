---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-05 15:44:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 20-29 cores)</summary>

```
1772743230 29
1772743235 29
1772743240 29
1772743245 29
1772743250 29
1772743255 29
1772743260 29
1772743265 29
1772743270 24
1772743275 24
1772743280 24
1772743285 24
1772743290 24
1772743295 24
1772743300 24
1772743305 24
1772743310 24
1772743315 24
1772743320 24
1772743325 24
```
</details>

---

