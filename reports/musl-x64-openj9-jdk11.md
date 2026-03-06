---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-06 04:35:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 988 |
| Sample Rate | 16.47/sec |
| Health Score | 1029% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1772789424 28
1772789429 28
1772789434 28
1772789439 28
1772789444 28
1772789449 28
1772789454 28
1772789459 32
1772789464 32
1772789469 32
1772789474 32
1772789479 32
1772789484 32
1772789489 32
1772789494 32
1772789499 32
1772789504 32
1772789509 32
1772789514 32
1772789519 32
```
</details>

---

