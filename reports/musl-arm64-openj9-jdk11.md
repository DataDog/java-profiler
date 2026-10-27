---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 14:35:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793125820 48
1793125825 48
1793125830 48
1793125835 48
1793125840 43
1793125845 43
1793125850 43
1793125855 43
1793125860 43
1793125865 43
1793125870 43
1793125875 43
1793125880 43
1793125885 43
1793125890 43
1793125895 43
1793125900 48
1793125905 48
1793125910 48
1793125915 48
```
</details>

---

