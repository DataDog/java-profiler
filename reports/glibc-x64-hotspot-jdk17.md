---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 10:10:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 69-73 cores)</summary>

```
1791468219 73
1791468224 73
1791468229 73
1791468234 73
1791468239 73
1791468244 73
1791468249 71
1791468254 71
1791468259 71
1791468264 71
1791468269 71
1791468274 71
1791468279 71
1791468284 71
1791468289 71
1791468294 69
1791468299 69
1791468304 69
1791468309 69
1791468314 69
```
</details>

---

