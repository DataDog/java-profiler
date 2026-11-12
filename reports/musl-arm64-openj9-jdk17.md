---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 09:43:04 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794494110 32
1794494115 32
1794494120 32
1794494125 32
1794494130 32
1794494135 32
1794494140 32
1794494145 32
1794494150 32
1794494155 32
1794494160 32
1794494165 32
1794494170 32
1794494175 32
1794494180 32
1794494185 32
1794494190 32
1794494195 32
1794494200 32
1794494205 32
```
</details>

---

