---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:44:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 58-61 cores)</summary>

```
1789731595 58
1789731600 58
1789731605 58
1789731610 58
1789731615 58
1789731620 58
1789731625 59
1789731630 59
1789731635 59
1789731640 61
1789731645 61
1789731650 61
1789731655 61
1789731660 61
1789731665 61
1789731670 61
1789731675 61
1789731680 61
1789731685 61
1789731690 61
```
</details>

---

