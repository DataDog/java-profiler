---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 09:57:16 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 581 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1777384277 91
1777384282 91
1777384287 91
1777384292 91
1777384297 91
1777384302 96
1777384307 96
1777384312 96
1777384317 96
1777384322 96
1777384327 96
1777384332 96
1777384337 96
1777384342 92
1777384347 92
1777384352 92
1777384357 92
1777384362 92
1777384367 92
1777384372 92
```
</details>

---

