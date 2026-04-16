---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-16 08:32:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (5 unique values: 43-54 cores)</summary>

```
1776342307 54
1776342312 54
1776342317 54
1776342322 54
1776342327 44
1776342332 44
1776342337 44
1776342342 44
1776342347 46
1776342352 46
1776342357 46
1776342362 46
1776342367 46
1776342372 46
1776342377 46
1776342382 43
1776342387 43
1776342392 43
1776342397 43
1776342402 43
```
</details>

---

