---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 07:16:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 31-64 cores)</summary>

```
1792580987 31
1792580992 31
1792580997 31
1792581002 31
1792581007 31
1792581012 31
1792581017 31
1792581022 51
1792581027 51
1792581032 51
1792581037 51
1792581042 51
1792581047 51
1792581052 51
1792581057 51
1792581062 64
1792581067 64
1792581072 64
1792581077 64
1792581082 64
```
</details>

---

