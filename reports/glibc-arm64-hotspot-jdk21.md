---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 04:21:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 7 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 11 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790669789 46
1790669794 46
1790669799 46
1790669804 46
1790669809 46
1790669814 46
1790669819 48
1790669824 48
1790669829 48
1790669834 48
1790669839 48
1790669844 48
1790669849 48
1790669854 48
1790669859 48
1790669864 48
1790669869 48
1790669874 48
1790669879 48
1790669884 48
```
</details>

---

