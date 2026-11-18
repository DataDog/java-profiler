---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 13:55:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 34-37 cores)</summary>

```
1795027801 37
1795027806 37
1795027811 37
1795027816 37
1795027821 37
1795027826 37
1795027831 37
1795027836 37
1795027841 37
1795027846 37
1795027851 37
1795027856 35
1795027861 35
1795027866 35
1795027871 35
1795027876 34
1795027881 34
1795027886 34
1795027891 34
1795027896 34
```
</details>

---

