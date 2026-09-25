---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-25 07:37:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790335991 43
1790335996 43
1790336001 43
1790336006 43
1790336011 43
1790336016 43
1790336021 43
1790336026 43
1790336031 43
1790336036 43
1790336041 43
1790336046 43
1790336051 48
1790336056 48
1790336061 48
1790336066 48
1790336071 48
1790336076 48
1790336081 48
1790336086 48
```
</details>

---

