---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-22 15:27:28 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787426622 66
1787426627 66
1787426632 66
1787426637 66
1787426642 66
1787426647 66
1787426652 66
1787426657 66
1787426662 66
1787426667 66
1787426672 66
1787426677 66
1787426682 66
1787426687 66
1787426692 66
1787426697 66
1787426702 66
1787426707 66
1787426712 64
1787426717 64
```
</details>

---

