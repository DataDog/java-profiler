---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:53:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1789667264 96
1789667269 96
1789667274 96
1789667279 96
1789667284 96
1789667289 96
1789667294 96
1789667299 96
1789667304 96
1789667309 96
1789667314 96
1789667319 96
1789667324 96
1789667329 96
1789667334 96
1789667339 96
1789667344 96
1789667349 96
1789667354 96
1789667359 96
```
</details>

---

