---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:02:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 52-62 cores)</summary>

```
1789995410 52
1789995415 52
1789995420 62
1789995425 62
1789995430 62
1789995435 62
1789995440 62
1789995445 62
1789995450 60
1789995455 60
1789995460 60
1789995465 60
1789995470 60
1789995475 60
1789995480 60
1789995485 60
1789995490 60
1789995495 60
1789995500 60
1789995505 60
```
</details>

---

