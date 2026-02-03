---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:38:36 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 10 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 12 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 52-55 cores)</summary>

```
1770125589 55
1770125594 55
1770125599 55
1770125604 55
1770125609 52
1770125614 52
1770125619 52
1770125624 52
1770125629 52
1770125634 52
1770125639 52
1770125644 52
1770125649 52
1770125654 52
1770125659 52
1770125664 52
1770125669 52
1770125674 52
1770125679 52
1770125684 52
```
</details>

---

