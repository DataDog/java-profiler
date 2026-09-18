---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:08:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 25-35 cores)</summary>

```
1789743415 35
1789743420 25
1789743425 25
1789743430 25
1789743435 25
1789743440 25
1789743445 25
1789743450 25
1789743455 25
1789743460 25
1789743465 25
1789743470 25
1789743475 25
1789743480 25
1789743485 25
1789743490 25
1789743495 25
1789743500 25
1789743505 25
1789743510 27
```
</details>

---

