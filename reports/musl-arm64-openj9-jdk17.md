---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 08:20:16 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 15 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794402900 46
1794402905 46
1794402910 46
1794402915 46
1794402920 46
1794402925 46
1794402930 48
1794402935 48
1794402940 48
1794402945 48
1794402950 48
1794402955 48
1794402960 48
1794402965 48
1794402970 48
1794402975 48
1794402980 48
1794402985 48
1794402990 48
1794402995 48
```
</details>

---

