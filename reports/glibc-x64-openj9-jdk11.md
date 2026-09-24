---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 04:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 882 |
| Sample Rate | 14.70/sec |
| Health Score | 919% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1790238284 23
1790238289 23
1790238294 23
1790238299 23
1790238304 25
1790238309 25
1790238314 25
1790238319 25
1790238324 25
1790238329 25
1790238334 25
1790238339 25
1790238344 25
1790238349 25
1790238354 25
1790238359 25
1790238364 25
1790238369 25
1790238374 25
1790238379 25
```
</details>

---

