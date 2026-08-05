---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-05 08:26:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 140 |
| Sample Rate | 2.33/sec |
| Health Score | 146% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 4 |
| Sample Rate | 0.07/sec |
| Health Score | 4% |
| Threads | 4 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 14-64 cores)</summary>

```
1785932446 14
1785932451 14
1785932456 14
1785932461 14
1785932466 14
1785932471 14
1785932476 44
1785932481 44
1785932486 44
1785932491 44
1785932496 44
1785932501 44
1785932506 64
1785932511 64
1785932516 64
1785932521 64
1785932526 64
1785932531 64
1785932536 64
1785932541 64
```
</details>

---

