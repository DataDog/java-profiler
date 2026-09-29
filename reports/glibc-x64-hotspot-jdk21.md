---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-29 12:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 40-56 cores)</summary>

```
1790699310 40
1790699315 40
1790699320 40
1790699325 40
1790699330 40
1790699335 40
1790699340 40
1790699345 40
1790699350 40
1790699355 40
1790699360 40
1790699365 40
1790699370 40
1790699375 40
1790699380 48
1790699385 48
1790699390 48
1790699395 48
1790699400 48
1790699405 48
```
</details>

---

