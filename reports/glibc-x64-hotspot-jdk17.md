---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 13:19:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 10 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 413 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1793293966 84
1793293971 84
1793293976 86
1793293981 86
1793293986 86
1793293991 86
1793293996 86
1793294001 86
1793294006 86
1793294011 88
1793294016 88
1793294021 88
1793294026 88
1793294031 88
1793294036 88
1793294041 88
1793294046 88
1793294051 88
1793294056 88
1793294061 88
```
</details>

---

