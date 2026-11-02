---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 14:28:38 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 895 |
| Sample Rate | 14.92/sec |
| Health Score | 932% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793647451 48
1793647456 48
1793647461 48
1793647466 48
1793647471 48
1793647476 48
1793647481 48
1793647486 48
1793647491 48
1793647496 48
1793647501 48
1793647506 48
1793647511 48
1793647516 48
1793647521 48
1793647526 48
1793647531 48
1793647536 48
1793647541 48
1793647546 48
```
</details>

---

