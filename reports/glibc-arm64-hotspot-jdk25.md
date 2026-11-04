---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:02:39 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1793829552 35
1793829557 35
1793829562 35
1793829567 35
1793829572 35
1793829577 35
1793829582 35
1793829587 35
1793829592 35
1793829597 35
1793829602 35
1793829607 40
1793829612 40
1793829617 40
1793829622 40
1793829627 40
1793829632 40
1793829637 40
1793829642 40
1793829647 40
```
</details>

---

