---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 05:18:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 9 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1790673269 24
1790673274 24
1790673279 24
1790673284 24
1790673289 24
1790673294 24
1790673299 24
1790673304 24
1790673309 22
1790673314 22
1790673319 22
1790673324 22
1790673329 24
1790673334 24
1790673339 24
1790673344 24
1790673349 24
1790673354 24
1790673359 24
1790673364 24
```
</details>

---

