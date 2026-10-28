---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 13:11:29 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1793207235 25
1793207240 25
1793207245 25
1793207250 25
1793207255 25
1793207260 25
1793207265 25
1793207270 25
1793207275 25
1793207280 25
1793207285 25
1793207290 25
1793207295 25
1793207300 27
1793207305 27
1793207310 25
1793207315 25
1793207320 25
1793207325 25
1793207330 25
```
</details>

---

