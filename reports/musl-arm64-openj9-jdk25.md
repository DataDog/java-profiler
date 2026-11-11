---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 11:40:38 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 10 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (4 unique values: 25-38 cores)</summary>

```
1794414852 25
1794414857 25
1794414862 25
1794414867 25
1794414872 25
1794414877 25
1794414882 25
1794414887 25
1794414892 25
1794414897 25
1794414902 25
1794414907 25
1794414912 25
1794414917 25
1794414922 25
1794414927 38
1794414932 38
1794414937 38
1794414942 38
1794414947 38
```
</details>

---

