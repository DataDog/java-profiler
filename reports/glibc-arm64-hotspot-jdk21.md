---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-07 01:56:51 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791352338 40
1791352343 40
1791352348 40
1791352353 40
1791352358 40
1791352363 40
1791352368 40
1791352373 40
1791352378 40
1791352383 40
1791352388 40
1791352393 40
1791352398 40
1791352403 40
1791352408 40
1791352413 40
1791352418 40
1791352423 40
1791352428 40
1791352433 40
```
</details>

---

