---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:22:39 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1791191811 48
1791191816 48
1791191821 40
1791191826 40
1791191831 40
1791191836 40
1791191841 40
1791191846 40
1791191851 40
1791191856 40
1791191861 40
1791191866 40
1791191871 40
1791191876 40
1791191881 40
1791191886 40
1791191891 40
1791191896 40
1791191901 40
1791191906 40
```
</details>

---

