---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-13 11:55:09 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 11 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1786636231 38
1786636236 43
1786636241 43
1786636246 43
1786636251 43
1786636256 43
1786636261 43
1786636266 43
1786636271 43
1786636276 43
1786636281 43
1786636286 43
1786636291 43
1786636296 43
1786636301 43
1786636306 43
1786636311 43
1786636316 43
1786636321 43
1786636326 43
```
</details>

---

