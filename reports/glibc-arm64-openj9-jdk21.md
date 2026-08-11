---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 11:48:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 13 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 40-51 cores)</summary>

```
1786462997 46
1786463002 46
1786463007 46
1786463012 46
1786463017 46
1786463022 46
1786463027 46
1786463032 46
1786463037 46
1786463042 51
1786463047 51
1786463052 40
1786463057 40
1786463062 40
1786463067 40
1786463072 40
1786463077 40
1786463082 40
1786463087 40
1786463092 40
```
</details>

---

