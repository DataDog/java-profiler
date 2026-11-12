---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 10:57:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 55-92 cores)</summary>

```
1794498707 57
1794498712 55
1794498717 55
1794498722 55
1794498727 55
1794498732 74
1794498737 74
1794498742 74
1794498747 74
1794498752 76
1794498757 76
1794498762 76
1794498767 76
1794498772 76
1794498777 76
1794498782 76
1794498787 76
1794498792 76
1794498797 85
1794498802 85
```
</details>

---

