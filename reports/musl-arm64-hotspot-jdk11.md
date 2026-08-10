---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 09:32:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1786368428 42
1786368433 47
1786368438 47
1786368443 47
1786368448 47
1786368453 47
1786368458 47
1786368463 47
1786368468 47
1786368473 47
1786368478 47
1786368483 47
1786368488 47
1786368493 47
1786368498 47
1786368503 47
1786368508 47
1786368513 47
1786368518 47
1786368523 47
```
</details>

---

