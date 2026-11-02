---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 14:28:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 15 |
| Allocations | 172 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
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
1793647531 43
1793647536 43
1793647541 43
1793647546 43
1793647551 43
1793647556 43
```
</details>

---

