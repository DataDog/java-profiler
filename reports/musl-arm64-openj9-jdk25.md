---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-31 06:53:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 9 |
| Allocations | 433 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1793443766 48
1793443771 48
1793443776 48
1793443781 48
1793443786 48
1793443791 48
1793443796 48
1793443801 48
1793443806 43
1793443811 43
1793443816 43
1793443821 43
1793443826 43
1793443831 43
1793443836 43
1793443841 43
1793443846 41
1793443851 41
1793443856 41
1793443861 41
```
</details>

---

