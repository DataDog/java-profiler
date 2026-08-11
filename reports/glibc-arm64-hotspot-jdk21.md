---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 09:33:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1786454983 64
1786454988 64
1786454993 64
1786454998 64
1786455003 64
1786455008 64
1786455013 64
1786455018 64
1786455023 64
1786455028 64
1786455033 64
1786455038 64
1786455043 64
1786455048 64
1786455053 64
1786455058 64
1786455063 64
1786455068 64
1786455073 64
1786455078 44
```
</details>

---

