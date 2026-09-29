---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 12:33:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 922 |
| Sample Rate | 15.37/sec |
| Health Score | 961% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 31-39 cores)</summary>

```
1790699288 31
1790699293 31
1790699298 31
1790699303 31
1790699308 31
1790699313 31
1790699318 31
1790699323 31
1790699329 31
1790699334 31
1790699339 31
1790699344 31
1790699349 31
1790699354 31
1790699359 39
1790699364 39
1790699369 39
1790699374 39
1790699379 39
1790699384 39
```
</details>

---

