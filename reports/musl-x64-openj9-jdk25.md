---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-13 07:46:26 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 14 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 80-86 cores)</summary>

```
1770986445 82
1770986450 82
1770986455 82
1770986460 82
1770986465 82
1770986470 80
1770986475 80
1770986480 80
1770986485 80
1770986490 80
1770986495 80
1770986500 82
1770986505 82
1770986510 82
1770986515 82
1770986520 82
1770986525 82
1770986530 82
1770986535 86
1770986540 86
```
</details>

---

