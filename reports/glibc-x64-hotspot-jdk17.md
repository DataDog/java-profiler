---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:27:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 982 |
| Sample Rate | 16.37/sec |
| Health Score | 1023% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (4 unique values: 59-62 cores)</summary>

```
1789737639 61
1789737644 59
1789737649 59
1789737654 59
1789737659 61
1789737664 61
1789737669 61
1789737674 61
1789737679 61
1789737684 62
1789737689 62
1789737694 62
1789737699 60
1789737704 60
1789737709 62
1789737714 62
1789737719 62
1789737724 62
1789737729 62
1789737734 62
```
</details>

---

