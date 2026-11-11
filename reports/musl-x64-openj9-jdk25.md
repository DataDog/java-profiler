---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:10:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1794355399 28
1794355404 28
1794355409 30
1794355414 30
1794355419 30
1794355424 30
1794355429 30
1794355434 30
1794355439 30
1794355444 30
1794355449 32
1794355454 32
1794355459 32
1794355464 32
1794355469 32
1794355474 32
1794355479 32
1794355484 30
1794355489 30
1794355494 30
```
</details>

---

