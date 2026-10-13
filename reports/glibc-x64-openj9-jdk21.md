---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 07:44:38 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1791891682 93
1791891687 93
1791891692 93
1791891697 93
1791891702 93
1791891707 93
1791891712 93
1791891717 93
1791891722 93
1791891727 93
1791891732 93
1791891737 93
1791891742 91
1791891747 91
1791891752 91
1791891757 91
1791891762 91
1791891767 91
1791891772 89
1791891777 89
```
</details>

---

