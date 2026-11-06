---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-06 10:29:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 38-47 cores)</summary>

```
1793978575 47
1793978580 47
1793978585 47
1793978590 47
1793978595 47
1793978600 47
1793978605 47
1793978610 46
1793978615 46
1793978620 42
1793978625 42
1793978630 42
1793978635 42
1793978640 42
1793978645 38
1793978650 38
1793978655 38
1793978660 38
1793978665 38
1793978670 38
```
</details>

---

