---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 05:59:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 10 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 13 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1793876056 51
1793876061 51
1793876066 51
1793876071 51
1793876076 51
1793876081 51
1793876086 51
1793876091 51
1793876096 47
1793876101 47
1793876106 47
1793876111 47
1793876116 47
1793876121 47
1793876126 47
1793876131 47
1793876136 47
1793876141 47
1793876146 47
1793876151 47
```
</details>

---

