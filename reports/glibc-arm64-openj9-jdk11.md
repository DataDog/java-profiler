---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 12:30:09 EDT

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
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 10 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1791995067 48
1791995072 46
1791995077 46
1791995082 45
1791995087 45
1791995092 45
1791995097 45
1791995102 45
1791995107 45
1791995112 45
1791995117 45
1791995122 45
1791995127 45
1791995132 46
1791995137 46
1791995142 48
1791995147 48
1791995152 48
1791995157 48
1791995162 48
```
</details>

---

