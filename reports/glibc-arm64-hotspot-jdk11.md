---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 08:15:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 10 |
| Allocations | 175 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 13 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794748225 32
1794748230 32
1794748235 32
1794748240 32
1794748245 32
1794748250 32
1794748255 32
1794748260 32
1794748265 32
1794748270 32
1794748275 32
1794748280 32
1794748285 32
1794748290 32
1794748295 32
1794748300 32
1794748305 32
1794748310 32
1794748315 32
1794748320 32
```
</details>

---

