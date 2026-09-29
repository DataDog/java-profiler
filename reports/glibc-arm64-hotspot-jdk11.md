---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 04:21:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 11 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1790669784 64
1790669789 64
1790669794 52
1790669799 52
1790669804 52
1790669809 52
1790669814 52
1790669819 52
1790669824 52
1790669829 52
1790669834 52
1790669839 52
1790669844 52
1790669849 52
1790669854 52
1790669859 52
1790669864 52
1790669869 52
1790669874 52
1790669879 52
```
</details>

---

