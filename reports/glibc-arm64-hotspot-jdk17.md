---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-17 14:25:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 14 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (2 unique values: 61-64 cores)</summary>

```
1786990900 61
1786990905 61
1786990910 61
1786990915 61
1786990920 61
1786990925 61
1786990930 61
1786990935 61
1786990940 61
1786990945 61
1786990950 61
1786990955 64
1786990960 64
1786990965 64
1786990970 64
1786990975 64
1786990980 64
1786990985 64
1786990990 64
1786990995 64
```
</details>

---

