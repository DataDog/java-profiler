---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:18:54 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 35-38 cores)</summary>

```
1795529664 36
1795529669 36
1795529674 36
1795529679 36
1795529684 36
1795529689 36
1795529694 36
1795529699 38
1795529704 38
1795529709 38
1795529714 38
1795529719 38
1795529724 38
1795529729 38
1795529734 38
1795529739 38
1795529744 38
1795529749 36
1795529754 36
1795529759 36
```
</details>

---

