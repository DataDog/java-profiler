---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 07:10:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1793880345 27
1793880350 27
1793880355 27
1793880360 27
1793880365 27
1793880370 27
1793880375 27
1793880380 27
1793880385 30
1793880390 30
1793880395 30
1793880400 30
1793880405 30
1793880410 30
1793880415 30
1793880420 30
1793880425 30
1793880430 30
1793880435 30
1793880440 30
```
</details>

---

