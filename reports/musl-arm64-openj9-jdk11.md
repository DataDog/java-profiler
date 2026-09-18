---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:09:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 9 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 10 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 41-48 cores)</summary>

```
1789743390 41
1789743395 41
1789743400 48
1789743405 48
1789743410 48
1789743415 48
1789743420 48
1789743425 48
1789743430 48
1789743435 48
1789743440 48
1789743445 48
1789743450 48
1789743455 48
1789743460 48
1789743465 48
1789743470 48
1789743475 48
1789743480 48
1789743485 48
```
</details>

---

