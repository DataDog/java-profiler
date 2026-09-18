---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:44:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 28-46 cores)</summary>

```
1789731595 40
1789731600 40
1789731605 40
1789731610 40
1789731615 40
1789731620 40
1789731625 40
1789731630 40
1789731635 40
1789731640 40
1789731645 40
1789731650 38
1789731655 38
1789731660 46
1789731665 46
1789731670 46
1789731675 46
1789731680 46
1789731685 46
1789731690 46
```
</details>

---

