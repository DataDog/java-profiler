---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 05:01:28 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1789721719 55
1789721724 60
1789721729 60
1789721734 60
1789721739 60
1789721744 60
1789721749 60
1789721754 60
1789721759 60
1789721764 60
1789721769 60
1789721774 60
1789721779 60
1789721784 60
1789721789 60
1789721794 60
1789721799 60
1789721804 60
1789721809 60
1789721814 60
```
</details>

---

