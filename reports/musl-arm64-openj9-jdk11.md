---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:55:40 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793281778 48
1793281783 48
1793281788 48
1793281793 48
1793281798 48
1793281803 48
1793281808 48
1793281813 48
1793281818 48
1793281823 48
1793281828 48
1793281833 48
1793281838 48
1793281843 48
1793281848 48
1793281853 48
1793281858 48
1793281863 48
1793281868 48
1793281873 48
```
</details>

---

