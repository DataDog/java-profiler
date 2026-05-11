---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:49:57 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1778514225 60
1778514230 60
1778514235 60
1778514240 60
1778514245 60
1778514250 60
1778514255 60
1778514260 60
1778514265 60
1778514270 60
1778514275 60
1778514280 64
1778514285 64
1778514290 64
1778514295 64
1778514300 64
1778514305 64
1778514310 64
1778514315 64
1778514320 64
```
</details>

---

