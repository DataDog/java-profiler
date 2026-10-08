---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 10:10:20 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 24-26 cores)</summary>

```
1791468223 26
1791468228 26
1791468233 26
1791468239 26
1791468244 26
1791468249 26
1791468254 26
1791468259 26
1791468264 26
1791468269 26
1791468274 26
1791468279 26
1791468284 26
1791468289 26
1791468294 26
1791468299 26
1791468304 26
1791468309 26
1791468314 24
1791468319 24
```
</details>

---

