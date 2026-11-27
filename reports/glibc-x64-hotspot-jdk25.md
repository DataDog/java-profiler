---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:28:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1795796653 43
1795796658 43
1795796663 43
1795796668 43
1795796673 43
1795796678 43
1795796683 43
1795796688 43
1795796693 45
1795796698 45
1795796703 45
1795796708 45
1795796713 45
1795796718 45
1795796723 43
1795796728 43
1795796733 43
1795796738 43
1795796743 43
1795796748 43
```
</details>

---

