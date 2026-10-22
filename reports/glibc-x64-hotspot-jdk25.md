---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 10:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1792678985 27
1792678990 27
1792678995 27
1792679000 27
1792679005 27
1792679010 27
1792679015 27
1792679020 27
1792679025 27
1792679030 27
1792679035 27
1792679040 27
1792679045 27
1792679050 27
1792679055 29
1792679060 29
1792679065 27
1792679070 27
1792679075 27
1792679080 27
```
</details>

---

