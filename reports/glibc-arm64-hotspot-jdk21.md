---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 09:46:21 EST

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794580937 46
1794580942 46
1794580947 46
1794580952 51
1794580957 51
1794580962 51
1794580967 51
1794580972 51
1794580977 51
1794580982 51
1794580987 51
1794580992 51
1794580997 51
1794581002 51
1794581007 51
1794581012 51
1794581017 51
1794581022 51
1794581027 51
1794581032 51
```
</details>

---

