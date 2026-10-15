---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-15 11:57:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792079316 48
1792079321 48
1792079326 48
1792079331 48
1792079336 48
1792079341 48
1792079346 48
1792079351 48
1792079356 48
1792079361 48
1792079366 48
1792079371 48
1792079376 48
1792079381 48
1792079386 48
1792079391 43
1792079396 43
1792079401 43
1792079406 43
1792079411 43
```
</details>

---

