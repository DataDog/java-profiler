---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 13:50:11 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 63-64 cores)</summary>

```
1793731456 64
1793731461 64
1793731466 64
1793731471 64
1793731476 64
1793731481 63
1793731486 63
1793731491 63
1793731496 63
1793731501 63
1793731506 63
1793731511 63
1793731516 63
1793731521 63
1793731526 63
1793731531 64
1793731536 64
1793731541 64
1793731546 64
1793731551 64
```
</details>

---

