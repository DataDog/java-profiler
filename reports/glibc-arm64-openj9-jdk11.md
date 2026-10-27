---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 01:05:33 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 970 |
| Sample Rate | 16.17/sec |
| Health Score | 1011% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (1 unique values: 28-28 cores)</summary>

```
1793077226 28
1793077231 28
1793077236 28
1793077241 28
1793077246 28
1793077251 28
1793077256 28
1793077261 28
1793077266 28
1793077271 28
1793077276 28
1793077281 28
1793077286 28
1793077291 28
1793077296 28
1793077301 28
1793077306 28
1793077311 28
1793077316 28
1793077321 28
```
</details>

---

