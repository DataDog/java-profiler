---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:36:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 11 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795620705 47
1795620710 47
1795620715 47
1795620720 47
1795620725 47
1795620730 47
1795620735 47
1795620740 47
1795620745 47
1795620750 47
1795620755 47
1795620760 47
1795620765 47
1795620770 47
1795620775 47
1795620780 47
1795620785 47
1795620790 42
1795620795 42
1795620800 42
```
</details>

---

