---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 10:05:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1778507970 44
1778507975 44
1778507980 44
1778507985 44
1778507990 44
1778507995 44
1778508000 44
1778508005 44
1778508010 44
1778508015 44
1778508020 44
1778508025 44
1778508030 44
1778508035 44
1778508040 44
1778508045 44
1778508050 44
1778508055 44
1778508060 39
1778508065 39
```
</details>

---

