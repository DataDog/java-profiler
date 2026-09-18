---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:13:58 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
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
1789743550 48
1789743555 48
1789743560 48
1789743565 48
```
</details>

---

