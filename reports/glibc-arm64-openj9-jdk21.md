---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:58:20 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795452900 43
1795452905 43
1795452910 43
1795452915 43
1795452920 43
1795452925 43
1795452930 43
1795452935 43
1795452940 43
1795452945 43
1795452950 43
1795452955 43
1795452960 43
1795452965 48
1795452970 48
1795452975 48
1795452980 43
1795452985 43
1795452990 43
1795452995 43
```
</details>

---

