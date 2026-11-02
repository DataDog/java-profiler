---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 08:53:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 10 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 16 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1793627298 39
1793627304 39
1793627309 39
1793627314 39
1793627319 39
1793627324 39
1793627329 39
1793627334 39
1793627339 39
1793627344 39
1793627349 39
1793627354 39
1793627359 39
1793627364 39
1793627369 39
1793627374 51
1793627379 51
1793627384 46
1793627389 46
1793627394 46
```
</details>

---

