---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-29 09:48:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 41-55 cores)</summary>

```
1769697767 55
1769697772 55
1769697777 55
1769697782 50
1769697787 50
1769697792 50
1769697797 50
1769697802 50
1769697807 48
1769697812 48
1769697817 50
1769697822 50
1769697827 50
1769697832 46
1769697837 46
1769697842 46
1769697847 46
1769697852 43
1769697857 43
1769697862 43
```
</details>

---

