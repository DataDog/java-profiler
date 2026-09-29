---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 06:07:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 66-96 cores)</summary>

```
1790675845 75
1790675850 75
1790675855 75
1790675860 75
1790675865 75
1790675870 75
1790675875 96
1790675880 96
1790675885 96
1790675890 96
1790675895 96
1790675900 96
1790675905 96
1790675910 96
1790675915 96
1790675920 96
1790675925 66
1790675930 66
1790675935 66
1790675940 66
```
</details>

---

