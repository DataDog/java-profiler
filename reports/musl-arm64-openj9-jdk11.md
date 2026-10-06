---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 08:29:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 12 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1791289477 27
1791289482 32
1791289487 32
1791289492 32
1791289497 32
1791289502 32
1791289507 32
1791289512 32
1791289517 32
1791289522 32
1791289527 32
1791289532 32
1791289537 32
1791289542 32
1791289547 32
1791289552 32
1791289557 32
1791289562 32
1791289567 32
1791289572 32
```
</details>

---

