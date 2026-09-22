---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:27:27 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 49-58 cores)</summary>

```
1790090482 50
1790090487 50
1790090492 50
1790090497 50
1790090502 50
1790090507 50
1790090512 50
1790090517 50
1790090522 50
1790090527 50
1790090532 50
1790090537 50
1790090542 50
1790090547 50
1790090552 50
1790090557 50
1790090562 50
1790090567 50
1790090572 58
1790090577 58
```
</details>

---

