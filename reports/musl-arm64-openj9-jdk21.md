---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 11:07:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789743517 48
1789743522 48
1789743527 48
1789743532 48
1789743537 48
1789743542 48
1789743547 43
1789743552 43
1789743557 43
1789743562 43
1789743567 43
1789743572 43
1789743577 43
1789743582 43
1789743587 43
1789743592 43
1789743597 43
1789743602 43
1789743607 43
1789743612 43
```
</details>

---

