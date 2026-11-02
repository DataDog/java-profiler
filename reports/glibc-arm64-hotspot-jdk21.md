---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 08:53:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 11 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 38-46 cores)</summary>

```
1793627338 46
1793627343 46
1793627348 46
1793627353 46
1793627358 46
1793627363 46
1793627368 46
1793627373 46
1793627378 46
1793627383 46
1793627388 41
1793627393 41
1793627398 41
1793627403 41
1793627408 41
1793627413 41
1793627418 41
1793627423 41
1793627428 41
1793627433 41
```
</details>

---

