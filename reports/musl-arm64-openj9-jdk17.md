---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 11:40:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1794414831 35
1794414836 35
1794414841 35
1794414846 35
1794414851 35
1794414856 35
1794414861 35
1794414867 35
1794414872 35
1794414877 35
1794414882 37
1794414887 37
1794414892 37
1794414897 37
1794414902 37
1794414907 37
1794414912 37
1794414917 37
1794414922 37
1794414927 37
```
</details>

---

