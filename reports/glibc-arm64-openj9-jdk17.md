---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 11:42:29 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 12 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1792683251 30
1792683256 30
1792683261 30
1792683266 30
1792683271 30
1792683276 30
1792683281 30
1792683286 30
1792683291 30
1792683296 30
1792683301 30
1792683306 30
1792683311 30
1792683316 30
1792683321 30
1792683326 30
1792683331 35
1792683336 35
1792683341 35
1792683346 35
```
</details>

---

