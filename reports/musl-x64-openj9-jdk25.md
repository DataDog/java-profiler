---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 06:14:54 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 10 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 12 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1772795370 32
1772795375 32
1772795380 32
1772795385 31
1772795390 31
1772795395 31
1772795400 31
1772795405 31
1772795410 31
1772795415 32
1772795420 32
1772795425 32
1772795430 32
1772795435 32
1772795440 32
1772795445 32
1772795450 32
1772795455 32
1772795460 32
1772795465 32
```
</details>

---

