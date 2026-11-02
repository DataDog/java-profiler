---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 08:53:12 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 67-71 cores)</summary>

```
1793627402 67
1793627407 67
1793627412 67
1793627417 67
1793627422 67
1793627427 67
1793627432 69
1793627437 69
1793627442 71
1793627447 71
1793627452 71
1793627457 71
1793627462 71
1793627467 71
1793627472 71
1793627477 71
1793627482 71
1793627487 71
1793627492 71
1793627497 71
```
</details>

---

