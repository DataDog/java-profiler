---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 13:25:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 47-53 cores)</summary>

```
1792689555 53
1792689560 53
1792689565 53
1792689570 51
1792689575 51
1792689580 49
1792689585 49
1792689590 49
1792689595 49
1792689600 49
1792689605 47
1792689610 47
1792689615 47
1792689620 47
1792689625 47
1792689630 47
1792689635 47
1792689640 47
1792689645 47
1792689650 47
```
</details>

---

