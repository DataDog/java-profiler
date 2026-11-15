---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 21:04:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1794707986 36
1794707991 36
1794707996 36
1794708001 36
1794708006 36
1794708011 36
1794708016 36
1794708021 36
1794708026 36
1794708031 36
1794708036 36
1794708041 36
1794708046 36
1794708052 48
1794708057 48
1794708062 48
1794708067 48
1794708072 43
1794708077 43
1794708082 43
```
</details>

---

