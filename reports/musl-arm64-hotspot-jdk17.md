---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-27 14:35:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
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
1793125920 48
1793125925 48
1793125930 48
1793125935 48
1793125940 48
1793125945 48
```
</details>

---

