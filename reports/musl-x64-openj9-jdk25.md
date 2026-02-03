---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:54:11 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 988 |
| Sample Rate | 16.47/sec |
| Health Score | 1029% |
| Threads | 12 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 87-94 cores)</summary>

```
1770137329 87
1770137334 87
1770137339 87
1770137344 87
1770137349 87
1770137354 87
1770137359 87
1770137364 87
1770137369 87
1770137374 87
1770137379 89
1770137384 89
1770137389 89
1770137394 89
1770137399 94
1770137404 94
1770137409 94
1770137414 94
1770137419 94
1770137424 94
```
</details>

---

