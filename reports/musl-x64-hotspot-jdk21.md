---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 04:02:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 82-91 cores)</summary>

```
1778572520 82
1778572525 82
1778572530 82
1778572535 82
1778572540 86
1778572545 86
1778572550 86
1778572555 86
1778572560 91
1778572565 91
1778572570 91
1778572575 91
1778572580 91
1778572585 91
1778572590 91
1778572595 91
1778572600 91
1778572605 91
1778572610 91
1778572615 91
```
</details>

---

