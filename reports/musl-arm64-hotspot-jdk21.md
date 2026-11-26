---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:24:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1795702816 64
1795702821 64
1795702826 64
1795702831 60
1795702836 60
1795702841 60
1795702846 60
1795702851 60
1795702856 60
1795702861 60
1795702866 60
1795702871 60
1795702876 60
1795702881 60
1795702886 60
1795702891 60
1795702896 60
1795702901 60
1795702906 60
1795702911 60
```
</details>

---

