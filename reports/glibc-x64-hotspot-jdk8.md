---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-29 09:48:26 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 151 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 52-61 cores)</summary>

```
1769697782 52
1769697787 55
1769697792 55
1769697797 55
1769697802 55
1769697807 55
1769697812 55
1769697817 55
1769697822 55
1769697827 55
1769697832 55
1769697837 59
1769697842 59
1769697847 59
1769697852 59
1769697857 59
1769697862 59
1769697867 59
1769697872 61
1769697877 61
```
</details>

---

