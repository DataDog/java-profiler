---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 09:35:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 14-16 cores)</summary>

```
1792675547 14
1792675552 14
1792675557 14
1792675562 14
1792675567 14
1792675572 14
1792675577 14
1792675582 14
1792675587 14
1792675592 14
1792675597 14
1792675602 14
1792675607 16
1792675612 16
1792675617 16
1792675622 16
1792675627 16
1792675632 16
1792675637 16
1792675642 16
```
</details>

---

