---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 12:42:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 63-66 cores)</summary>

```
1789749369 63
1789749374 63
1789749379 63
1789749384 63
1789749389 63
1789749394 63
1789749399 63
1789749404 64
1789749409 64
1789749414 64
1789749419 64
1789749425 66
1789749430 66
1789749435 66
1789749440 66
1789749445 66
1789749450 66
1789749455 66
1789749460 66
1789749465 66
```
</details>

---

