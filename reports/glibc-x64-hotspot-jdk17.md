---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-08 12:05:50 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791475192 30
1791475197 30
1791475202 30
1791475207 30
1791475212 30
1791475217 30
1791475222 30
1791475227 30
1791475232 32
1791475237 32
1791475242 32
1791475247 32
1791475252 32
1791475257 32
1791475262 32
1791475267 32
1791475272 32
1791475277 32
1791475282 32
1791475287 32
```
</details>

---

