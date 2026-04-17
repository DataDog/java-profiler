---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 06:07:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 23-29 cores)</summary>

```
1776420229 23
1776420234 23
1776420239 24
1776420244 24
1776420249 24
1776420254 24
1776420259 24
1776420264 24
1776420269 24
1776420274 24
1776420279 24
1776420284 24
1776420289 24
1776420294 24
1776420299 24
1776420305 24
1776420310 24
1776420315 24
1776420320 24
1776420325 29
```
</details>

---

