---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:25:37 EST

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
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 10 |
| Allocations | 134 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (3 unique values: 34-47 cores)</summary>

```
1795702801 47
1795702806 47
1795702811 47
1795702816 47
1795702821 42
1795702826 42
1795702831 34
1795702836 34
1795702841 34
1795702846 34
1795702851 34
1795702856 34
1795702861 34
1795702866 34
1795702871 34
1795702876 34
1795702881 34
1795702886 34
1795702891 34
1795702896 34
```
</details>

---

