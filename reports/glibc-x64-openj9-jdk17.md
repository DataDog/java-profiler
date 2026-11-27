---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-27 11:28:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 5 |
| Sample Rate | 0.08/sec |
| Health Score | 5% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 50-66 cores)</summary>

```
1795796649 50
1795796654 50
1795796659 50
1795796664 50
1795796669 50
1795796674 50
1795796679 50
1795796684 50
1795796690 50
1795796695 50
1795796700 66
1795796705 66
1795796710 64
1795796715 64
1795796720 64
1795796725 64
1795796730 64
1795796735 64
1795796740 64
1795796745 64
```
</details>

---

