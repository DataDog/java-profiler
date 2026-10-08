---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 05:09:11 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 16-18 cores)</summary>

```
1791450278 17
1791450283 16
1791450288 16
1791450293 16
1791450298 16
1791450303 16
1791450309 16
1791450314 16
1791450319 16
1791450324 16
1791450329 16
1791450334 16
1791450339 16
1791450344 16
1791450349 16
1791450354 16
1791450359 16
1791450364 16
1791450369 16
1791450374 16
```
</details>

---

