---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 51-63 cores)</summary>

```
1790335990 53
1790335995 53
1790336000 51
1790336005 51
1790336010 51
1790336015 51
1790336020 51
1790336025 51
1790336030 51
1790336035 51
1790336040 51
1790336045 51
1790336050 51
1790336055 51
1790336060 51
1790336065 51
1790336070 61
1790336075 61
1790336080 61
1790336085 61
```
</details>

---

