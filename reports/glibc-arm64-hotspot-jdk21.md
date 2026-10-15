---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-15 12:04:39 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792079975 51
1792079980 51
1792079985 51
1792079990 39
1792079995 39
1792080000 39
1792080005 39
1792080010 39
1792080015 39
1792080020 39
1792080025 39
1792080030 39
1792080035 39
1792080040 39
1792080045 39
1792080050 39
1792080055 39
1792080060 39
1792080065 39
1792080070 39
```
</details>

---

