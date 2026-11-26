---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 09:24:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 12 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 11 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (3 unique values: 42-64 cores)</summary>

```
1795702815 64
1795702820 64
1795702825 64
1795702831 47
1795702836 47
1795702841 47
1795702846 47
1795702851 42
1795702856 42
1795702861 42
1795702866 42
1795702871 42
1795702876 42
1795702881 42
1795702886 42
1795702891 42
1795702896 42
1795702901 42
1795702906 42
1795702911 42
```
</details>

---

