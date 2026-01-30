---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-30 06:15:42 EST

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
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 837 |
| Sample Rate | 13.95/sec |
| Health Score | 872% |
| Threads | 12 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 26-32 cores)</summary>

```
1769771389 32
1769771394 32
1769771399 26
1769771404 26
1769771409 27
1769771414 27
1769771419 27
1769771424 27
1769771429 27
1769771434 27
1769771439 27
1769771444 27
1769771449 27
1769771454 27
1769771459 27
1769771464 27
1769771469 27
1769771474 27
1769771479 27
1769771484 27
```
</details>

---

