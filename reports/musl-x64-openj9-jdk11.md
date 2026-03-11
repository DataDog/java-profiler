---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 13:39:51 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 986 |
| Sample Rate | 16.43/sec |
| Health Score | 1027% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 80-90 cores)</summary>

```
1773250209 83
1773250214 83
1773250219 83
1773250224 83
1773250229 83
1773250234 83
1773250239 83
1773250244 83
1773250249 83
1773250254 83
1773250259 83
1773250264 83
1773250269 83
1773250274 83
1773250279 83
1773250284 83
1773250289 83
1773250294 83
1773250299 80
1773250304 80
```
</details>

---

