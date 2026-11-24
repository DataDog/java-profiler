---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 07:51:06 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 67-72 cores)</summary>

```
1795524366 67
1795524371 67
1795524376 67
1795524381 72
1795524386 72
1795524391 72
1795524396 72
1795524401 72
1795524406 72
1795524411 72
1795524416 72
1795524421 72
1795524426 72
1795524431 72
1795524436 72
1795524441 72
1795524446 72
1795524451 72
1795524456 72
1795524461 72
```
</details>

---

