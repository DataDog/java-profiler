---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 12:53:35 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 968 |
| Sample Rate | 16.13/sec |
| Health Score | 1008% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 61-70 cores)</summary>

```
1778172542 70
1778172547 70
1778172552 70
1778172557 70
1778172562 70
1778172567 70
1778172572 65
1778172577 65
1778172582 65
1778172587 65
1778172592 65
1778172597 63
1778172602 63
1778172607 61
1778172612 61
1778172617 63
1778172622 63
1778172627 63
1778172632 63
1778172637 63
```
</details>

---

