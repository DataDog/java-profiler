---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:25:35 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 14 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (4 unique values: 9-13 cores)</summary>

```
1790173206 9
1790173211 12
1790173216 12
1790173221 13
1790173226 13
1790173231 13
1790173236 13
1790173241 13
1790173246 13
1790173251 13
1790173256 13
1790173261 13
1790173266 13
1790173271 11
1790173276 11
1790173281 9
1790173286 9
1790173291 9
1790173296 9
1790173301 9
```
</details>

---

