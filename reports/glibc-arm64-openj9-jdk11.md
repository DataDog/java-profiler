---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:25:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 14 |
| Allocations | 184 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793722820 48
1793722825 48
1793722830 48
1793722835 48
1793722840 48
1793722845 48
1793722850 48
1793722855 48
1793722860 48
1793722865 48
1793722870 48
1793722875 48
1793722880 48
1793722885 48
1793722890 48
1793722895 48
1793722900 48
1793722905 48
1793722910 48
1793722915 48
```
</details>

---

