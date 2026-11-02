---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 08:53:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793627304 28
1793627309 30
1793627314 30
1793627319 30
1793627324 30
1793627329 30
1793627334 30
1793627339 30
1793627344 30
1793627349 30
1793627354 30
1793627359 30
1793627364 30
1793627369 32
1793627374 32
1793627379 32
1793627384 32
1793627389 32
1793627395 32
1793627400 32
```
</details>

---

