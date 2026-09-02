---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 05:49:12 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788342290 96
1788342295 96
1788342300 96
1788342305 96
1788342310 96
1788342315 96
1788342320 96
1788342325 94
1788342330 94
1788342335 94
1788342340 94
1788342345 94
1788342350 94
1788342355 94
1788342360 94
1788342365 94
1788342370 94
1788342375 94
1788342380 94
1788342385 96
```
</details>

---

