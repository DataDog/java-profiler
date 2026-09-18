---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (2 unique values: 53-63 cores)</summary>

```
1789737692 63
1789737697 63
1789737702 63
1789737707 63
1789737712 63
1789737717 63
1789737722 63
1789737727 53
1789737732 53
1789737737 53
1789737742 53
1789737747 53
1789737752 53
1789737757 53
1789737762 53
1789737767 53
1789737772 53
1789737777 53
1789737782 53
1789737787 53
```
</details>

---

