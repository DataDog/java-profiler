---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-12 03:21:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 10 |
| Allocations | 119 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 17-34 cores)</summary>

```
1791789407 34
1791789412 34
1791789417 34
1791789422 34
1791789427 22
1791789432 22
1791789438 22
1791789443 22
1791789448 22
1791789453 22
1791789458 22
1791789463 22
1791789468 22
1791789473 22
1791789478 22
1791789483 22
1791789488 17
1791789493 17
1791789498 17
1791789503 17
```
</details>

---

