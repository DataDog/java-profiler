---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 06:42:06 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 38 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795174627 29
1795174632 29
1795174637 29
1795174642 29
1795174647 29
1795174652 29
1795174657 34
1795174662 34
1795174667 34
1795174672 34
1795174677 34
1795174682 34
1795174687 34
1795174692 34
1795174697 29
1795174702 29
1795174707 29
1795174712 29
1795174717 29
1795174722 29
```
</details>

---

