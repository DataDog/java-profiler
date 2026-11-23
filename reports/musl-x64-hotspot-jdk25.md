---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:05:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 69-73 cores)</summary>

```
1795449466 73
1795449471 73
1795449476 73
1795449481 73
1795449486 73
1795449491 73
1795449496 71
1795449501 71
1795449506 71
1795449511 71
1795449516 71
1795449521 71
1795449526 71
1795449531 71
1795449536 73
1795449541 73
1795449546 69
1795449551 69
1795449556 69
1795449561 69
```
</details>

---

