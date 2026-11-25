---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:02:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 972 |
| Sample Rate | 16.20/sec |
| Health Score | 1012% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795618594 47
1795618599 47
1795618604 47
1795618609 47
1795618614 47
1795618619 64
1795618624 64
1795618629 64
1795618634 64
1795618639 64
1795618644 64
1795618649 64
1795618654 64
1795618659 64
1795618664 64
1795618669 64
1795618674 64
1795618679 64
1795618684 64
1795618689 64
```
</details>

---

