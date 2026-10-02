---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-02 14:02:18 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (5 unique values: 53-73 cores)</summary>

```
1790963918 71
1790963923 71
1790963928 71
1790963933 71
1790963938 71
1790963943 71
1790963948 71
1790963953 68
1790963958 68
1790963963 68
1790963968 68
1790963973 56
1790963978 56
1790963983 56
1790963988 56
1790963993 56
1790963998 73
1790964003 73
1790964008 73
1790964013 73
```
</details>

---

