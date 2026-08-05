---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-05 08:26:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 14-64 cores)</summary>

```
1785932461 14
1785932466 14
1785932471 14
1785932477 44
1785932482 44
1785932487 44
1785932492 44
1785932497 44
1785932502 44
1785932507 64
1785932512 64
1785932517 64
1785932522 64
1785932527 64
1785932532 64
1785932537 64
1785932542 64
1785932547 64
1785932552 64
1785932557 64
```
</details>

---

