---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 18:00:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776981417 64
1776981422 64
1776981428 64
1776981433 64
1776981438 64
1776981443 64
1776981448 64
1776981453 64
1776981458 64
1776981463 64
1776981468 64
1776981473 64
1776981478 64
1776981483 64
1776981488 64
1776981493 64
1776981498 64
1776981503 64
1776981508 64
1776981513 64
```
</details>

---

