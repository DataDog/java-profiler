---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:44:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 11 |
| Allocations | 158 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1795426791 14
1795426796 14
1795426801 14
1795426806 14
1795426811 14
1795426816 14
1795426821 14
1795426826 14
1795426831 14
1795426836 14
1795426841 14
1795426846 14
1795426851 14
1795426856 14
1795426861 14
1795426866 34
1795426871 34
1795426876 34
1795426881 34
1795426886 34
```
</details>

---

