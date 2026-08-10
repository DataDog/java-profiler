---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 05:03:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (3 unique values: 24-33 cores)</summary>

```
1786352338 28
1786352343 28
1786352348 28
1786352353 28
1786352358 28
1786352363 28
1786352368 28
1786352373 28
1786352378 28
1786352383 28
1786352388 28
1786352393 33
1786352398 33
1786352403 33
1786352408 33
1786352413 33
1786352418 33
1786352423 33
1786352428 24
1786352433 24
```
</details>

---

