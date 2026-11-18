---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:10:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 15-28 cores)</summary>

```
1795010745 15
1795010750 15
1795010755 15
1795010760 15
1795010765 15
1795010770 15
1795010775 15
1795010780 15
1795010785 15
1795010790 15
1795010795 15
1795010800 15
1795010805 15
1795010810 15
1795010815 15
1795010820 15
1795010825 15
1795010830 15
1795010835 15
1795010840 15
```
</details>

---

