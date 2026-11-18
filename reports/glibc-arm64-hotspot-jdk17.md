---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:43:43 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 11 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 23-31 cores)</summary>

```
1794998219 31
1794998224 31
1794998229 31
1794998234 31
1794998239 31
1794998244 31
1794998249 31
1794998254 31
1794998259 31
1794998264 31
1794998269 31
1794998274 31
1794998279 31
1794998284 31
1794998289 31
1794998294 31
1794998300 31
1794998305 23
1794998310 23
1794998315 23
```
</details>

---

