---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:22:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (3 unique values: 61-65 cores)</summary>

```
1793722597 63
1793722602 63
1793722607 63
1793722612 61
1793722617 61
1793722622 61
1793722627 61
1793722632 61
1793722637 61
1793722642 61
1793722647 63
1793722652 63
1793722657 63
1793722662 63
1793722667 63
1793722672 63
1793722677 63
1793722682 63
1793722687 63
1793722692 63
```
</details>

---

