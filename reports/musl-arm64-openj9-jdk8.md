---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-30 09:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 43 |
| Sample Rate | 0.72/sec |
| Health Score | 45% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 34-53 cores)</summary>

```
1793368007 53
1793368012 53
1793368017 53
1793368022 53
1793368027 53
1793368032 41
1793368037 41
1793368042 36
1793368047 36
1793368052 36
1793368057 36
1793368062 36
1793368067 36
1793368072 36
1793368077 36
1793368082 36
1793368087 36
1793368092 41
1793368097 41
1793368102 41
```
</details>

---

