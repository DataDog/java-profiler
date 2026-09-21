---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:40:57 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 42-50 cores)</summary>

```
1789997725 50
1789997730 50
1789997735 50
1789997740 50
1789997745 42
1789997750 42
1789997755 42
1789997761 42
1789997766 42
1789997771 42
1789997776 42
1789997781 42
1789997786 42
1789997791 42
1789997796 42
1789997801 42
1789997806 42
1789997811 42
1789997816 42
1789997821 42
```
</details>

---

