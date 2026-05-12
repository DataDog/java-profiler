---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-05-12 06:43:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1778582414 28
1778582419 28
1778582424 28
1778582429 28
1778582434 28
1778582439 28
1778582444 28
1778582449 28
1778582454 26
1778582459 26
1778582464 28
1778582469 28
1778582474 28
1778582479 28
1778582484 28
1778582489 28
1778582494 28
1778582499 30
1778582504 30
1778582509 30
```
</details>

---

