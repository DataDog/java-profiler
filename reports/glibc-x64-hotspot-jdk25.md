---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:08:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1789995764 21
1789995769 21
1789995774 21
1789995779 32
1789995784 32
1789995789 32
1789995794 32
1789995799 12
1789995804 12
1789995809 12
1789995814 12
1789995819 12
1789995824 12
1789995829 12
1789995834 12
1789995839 12
1789995844 12
1789995849 12
1789995854 12
1789995859 12
```
</details>

---

