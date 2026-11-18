---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 14:50:18 EST

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
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795031218 51
1795031223 51
1795031228 51
1795031233 51
1795031238 46
1795031243 46
1795031248 46
1795031253 46
1795031258 46
1795031263 46
1795031268 46
1795031273 46
1795031278 46
1795031283 46
1795031288 46
1795031293 46
1795031298 46
1795031303 46
1795031308 51
1795031313 51
```
</details>

---

