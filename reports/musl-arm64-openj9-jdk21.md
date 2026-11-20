---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 06:42:07 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 29-31 cores)</summary>

```
1795174641 29
1795174646 29
1795174651 29
1795174656 29
1795174661 31
1795174666 31
1795174671 31
1795174676 31
1795174681 31
1795174686 31
1795174691 31
1795174696 31
1795174701 31
1795174706 31
1795174711 31
1795174716 31
1795174721 31
1795174726 31
1795174731 31
1795174736 31
```
</details>

---

