---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:59:32 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 442 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 12 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770130528 32
1770130533 32
1770130538 32
1770130543 32
1770130548 32
1770130553 32
1770130558 32
1770130563 32
1770130568 32
1770130573 32
1770130578 32
1770130583 32
1770130588 32
1770130593 32
1770130598 32
1770130603 27
1770130608 27
1770130613 27
1770130618 27
1770130623 27
```
</details>

---

