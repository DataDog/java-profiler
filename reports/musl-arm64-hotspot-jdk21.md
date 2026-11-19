---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 18:09:56 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795129552 29
1795129557 29
1795129562 29
1795129567 29
1795129572 29
1795129577 29
1795129582 34
1795129587 34
1795129592 34
1795129597 34
1795129602 34
1795129607 34
1795129612 34
1795129617 34
1795129622 34
1795129627 34
1795129632 34
1795129637 34
1795129642 34
1795129647 34
```
</details>

---

