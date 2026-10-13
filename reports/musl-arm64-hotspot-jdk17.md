---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-13 01:03:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 9 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1791867567 35
1791867572 35
1791867577 35
1791867582 30
1791867587 30
1791867592 30
1791867597 30
1791867602 30
1791867607 30
1791867612 30
1791867617 30
1791867622 30
1791867627 30
1791867632 30
1791867637 30
1791867643 30
1791867648 30
1791867653 30
1791867658 30
1791867663 30
```
</details>

---

