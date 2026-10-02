---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-02 04:21:36 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (4 unique values: 42-59 cores)</summary>

```
1790929046 47
1790929051 47
1790929056 47
1790929061 47
1790929066 47
1790929071 47
1790929076 47
1790929081 59
1790929086 59
1790929091 59
1790929096 52
1790929101 52
1790929106 47
1790929111 47
1790929116 47
1790929121 47
1790929126 47
1790929131 47
1790929136 47
1790929141 47
```
</details>

---

