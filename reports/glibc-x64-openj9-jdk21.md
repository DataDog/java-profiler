---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:55:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1795027806 23
1795027811 21
1795027816 21
1795027821 21
1795027826 21
1795027831 21
1795027836 21
1795027841 21
1795027846 21
1795027851 21
1795027856 21
1795027861 21
1795027866 21
1795027871 21
1795027876 21
1795027881 21
1795027886 21
1795027891 21
1795027896 21
1795027901 21
```
</details>

---

