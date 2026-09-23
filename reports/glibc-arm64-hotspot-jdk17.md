---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 08:23:42 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790165961 48
1790165966 48
1790165971 48
1790165976 48
1790165981 43
1790165986 43
1790165991 43
1790165996 43
1790166001 43
1790166006 43
1790166011 43
1790166016 43
1790166021 43
1790166026 43
1790166031 43
1790166036 48
1790166041 48
1790166046 48
1790166051 48
1790166056 48
```
</details>

---

