---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 10:20:50 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (6 unique values: 79-91 cores)</summary>

```
1790777699 80
1790777704 80
1790777709 79
1790777714 79
1790777719 79
1790777724 79
1790777729 79
1790777734 83
1790777740 83
1790777745 83
1790777750 83
1790777755 83
1790777760 86
1790777765 86
1790777770 86
1790777775 86
1790777780 88
1790777785 88
1790777790 88
1790777795 88
```
</details>

---

