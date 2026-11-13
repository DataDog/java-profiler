---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 11:34:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 76-86 cores)</summary>

```
1794587394 86
1794587399 86
1794587404 86
1794587409 86
1794587414 86
1794587419 86
1794587424 86
1794587429 86
1794587434 86
1794587439 86
1794587444 86
1794587449 86
1794587454 86
1794587459 84
1794587464 84
1794587469 84
1794587474 84
1794587479 84
1794587484 76
1794587489 76
```
</details>

---

