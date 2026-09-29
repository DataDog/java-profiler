---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-29 06:43:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 35-96 cores)</summary>

```
1790678275 35
1790678280 35
1790678285 35
1790678290 37
1790678295 37
1790678300 37
1790678305 37
1790678310 37
1790678315 37
1790678321 37
1790678326 37
1790678331 70
1790678336 70
1790678341 70
1790678346 70
1790678351 70
1790678356 70
1790678361 70
1790678366 70
1790678371 70
```
</details>

---

