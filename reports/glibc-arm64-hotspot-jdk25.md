---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 13:48:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 10 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1793382308 51
1793382313 51
1793382318 51
1793382323 51
1793382328 51
1793382333 51
1793382338 51
1793382343 51
1793382348 51
1793382353 51
1793382358 51
1793382363 51
1793382368 51
1793382373 51
1793382378 51
1793382383 51
1793382388 51
1793382393 51
1793382398 51
1793382403 51
```
</details>

---

