---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 07:42:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 49-68 cores)</summary>

```
1793882264 52
1793882269 54
1793882274 54
1793882279 49
1793882284 49
1793882289 49
1793882294 49
1793882299 49
1793882304 49
1793882309 49
1793882314 49
1793882319 49
1793882324 49
1793882329 49
1793882335 49
1793882340 49
1793882345 49
1793882350 49
1793882355 49
1793882360 49
```
</details>

---

