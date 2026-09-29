---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 05:19:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 978 |
| Sample Rate | 16.30/sec |
| Health Score | 1019% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (5 unique values: 60-73 cores)</summary>

```
1790673254 73
1790673259 73
1790673264 73
1790673269 73
1790673274 73
1790673279 73
1790673284 73
1790673289 73
1790673294 62
1790673299 62
1790673304 60
1790673309 60
1790673314 60
1790673319 69
1790673324 69
1790673329 69
1790673334 69
1790673339 69
1790673344 69
1790673349 69
```
</details>

---

