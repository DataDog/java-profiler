---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 04:49:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 25-29 cores)</summary>

```
1792658544 29
1792658549 29
1792658554 29
1792658559 29
1792658564 29
1792658569 27
1792658574 27
1792658579 27
1792658584 27
1792658589 27
1792658594 27
1792658599 25
1792658604 25
1792658609 25
1792658614 25
1792658619 25
1792658624 25
1792658629 25
1792658634 25
1792658639 27
```
</details>

---

