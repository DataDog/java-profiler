---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (4 unique values: 35-51 cores)</summary>

```
1791193601 40
1791193606 40
1791193611 40
1791193616 40
1791193621 40
1791193626 40
1791193631 40
1791193636 40
1791193641 40
1791193646 40
1791193651 40
1791193656 40
1791193661 40
1791193666 40
1791193671 35
1791193676 35
1791193681 35
1791193686 35
1791193691 35
1791193697 35
```
</details>

---

