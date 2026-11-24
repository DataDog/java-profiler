---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:42:50 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 40-51 cores)</summary>

```
1795538298 51
1795538303 51
1795538308 49
1795538313 49
1795538318 47
1795538323 47
1795538328 47
1795538333 47
1795538338 47
1795538343 47
1795538348 49
1795538353 49
1795538358 49
1795538363 49
1795538368 40
1795538373 40
1795538378 40
1795538383 40
1795538388 40
1795538393 40
```
</details>

---

