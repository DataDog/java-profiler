---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 09:45:19 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 319 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1791466759 15
1791466764 15
1791466769 15
1791466774 15
1791466779 15
1791466784 15
1791466789 15
1791466794 15
1791466799 15
1791466804 15
1791466809 15
1791466814 15
1791466819 15
1791466824 15
1791466829 15
1791466834 15
1791466839 15
1791466844 32
1791466849 32
1791466854 32
```
</details>

---

