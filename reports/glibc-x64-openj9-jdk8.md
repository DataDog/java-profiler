---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-03-06 11:13:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1772813283 26
1772813288 26
1772813293 26
1772813298 24
1772813303 24
1772813308 24
1772813313 24
1772813318 24
1772813323 24
1772813328 26
1772813333 26
1772813338 26
1772813343 26
1772813348 26
1772813353 26
1772813358 26
1772813363 26
1772813368 26
1772813373 26
1772813378 29
```
</details>

---

