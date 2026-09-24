---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:40:53 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 45-59 cores)</summary>

```
1790238957 59
1790238962 59
1790238967 45
1790238972 45
1790238977 45
1790238982 45
1790238987 45
1790238992 45
1790238997 45
1790239002 45
1790239007 45
1790239012 45
1790239017 45
1790239022 45
1790239027 45
1790239032 45
1790239037 45
1790239042 45
1790239047 45
1790239052 45
```
</details>

---

