---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 08:53:12 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 70-76 cores)</summary>

```
1793627298 76
1793627303 72
1793627308 72
1793627313 72
1793627318 72
1793627323 72
1793627328 72
1793627333 72
1793627338 72
1793627343 72
1793627348 72
1793627353 72
1793627358 72
1793627363 72
1793627368 72
1793627373 72
1793627378 72
1793627383 72
1793627388 72
1793627393 70
```
</details>

---

