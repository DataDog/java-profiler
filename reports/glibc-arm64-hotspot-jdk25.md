---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 10:28:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 12-12 cores)</summary>

```
1793978603 12
1793978608 12
1793978613 12
1793978618 12
1793978623 12
1793978628 12
1793978633 12
1793978638 12
1793978643 12
1793978648 12
1793978653 12
1793978658 12
1793978663 12
1793978668 12
1793978673 12
1793978678 12
1793978683 12
1793978688 12
1793978693 12
1793978698 12
```
</details>

---

