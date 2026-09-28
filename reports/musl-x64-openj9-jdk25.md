---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 00:58:21 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 57-96 cores)</summary>

```
1790571236 57
1790571241 57
1790571246 57
1790571251 57
1790571256 57
1790571261 57
1790571266 57
1790571271 57
1790571276 57
1790571281 57
1790571286 57
1790571291 96
1790571296 96
1790571301 96
1790571306 96
1790571311 96
1790571316 96
1790571321 96
1790571326 96
1790571331 96
```
</details>

---

