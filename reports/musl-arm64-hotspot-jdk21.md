---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 11:23:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 12 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793373587 43
1793373592 43
1793373597 43
1793373602 43
1793373607 43
1793373612 43
1793373617 43
1793373622 43
1793373627 43
1793373632 43
1793373637 43
1793373642 43
1793373647 43
1793373652 43
1793373657 43
1793373662 43
1793373667 43
1793373672 43
1793373677 43
1793373682 43
```
</details>

---

