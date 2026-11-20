---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 13:41:33 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 56-65 cores)</summary>

```
1795199748 56
1795199753 65
1795199758 65
1795199763 63
1795199768 63
1795199773 63
1795199778 63
1795199783 63
1795199788 63
1795199793 63
1795199798 63
1795199803 63
1795199808 63
1795199813 60
1795199818 60
1795199823 60
1795199828 60
1795199833 60
1795199838 60
1795199843 60
```
</details>

---

