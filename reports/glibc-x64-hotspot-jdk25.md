---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 15:41:50 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1790278659 48
1790278664 48
1790278669 48
1790278674 48
1790278679 48
1790278684 48
1790278689 48
1790278694 48
1790278699 58
1790278704 58
1790278709 58
1790278714 48
1790278719 48
1790278724 48
1790278729 48
1790278734 48
1790278739 48
1790278744 48
1790278749 48
1790278754 48
```
</details>

---

