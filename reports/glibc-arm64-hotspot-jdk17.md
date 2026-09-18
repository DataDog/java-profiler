---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:05:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 15 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1789743450 40
1789743455 40
1789743460 40
1789743465 40
1789743470 40
1789743475 40
1789743480 40
1789743485 40
1789743490 40
1789743495 40
1789743500 40
1789743505 40
1789743510 40
1789743515 40
1789743520 40
1789743525 40
1789743530 40
1789743535 40
1789743540 40
1789743545 40
```
</details>

---

