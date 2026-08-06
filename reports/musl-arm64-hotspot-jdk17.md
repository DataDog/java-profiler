---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-06 08:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786018976 48
1786018981 48
1786018986 48
1786018991 48
1786018996 48
1786019001 48
1786019006 48
1786019011 48
1786019016 48
1786019021 48
1786019026 48
1786019031 48
1786019036 48
1786019041 48
1786019046 48
1786019051 48
1786019056 48
1786019061 48
1786019066 48
1786019071 43
```
</details>

---

