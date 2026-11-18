---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 11 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 13 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795010735 43
1795010740 43
1795010745 43
1795010750 43
1795010755 43
1795010760 43
1795010765 43
1795010770 43
1795010775 43
1795010780 43
1795010785 43
1795010790 43
1795010795 48
1795010800 48
1795010805 48
1795010810 48
1795010815 48
1795010820 48
1795010825 48
1795010830 48
```
</details>

---

