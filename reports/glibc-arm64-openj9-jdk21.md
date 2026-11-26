---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:25:35 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795702830 64
1795702835 64
1795702840 64
1795702845 64
1795702851 64
1795702856 64
1795702861 64
1795702866 64
1795702871 64
1795702876 64
1795702881 64
1795702886 64
1795702891 64
1795702896 64
1795702901 64
1795702906 64
1795702911 64
1795702916 64
1795702921 64
1795702926 64
```
</details>

---

