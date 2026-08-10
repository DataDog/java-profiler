---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-09 21:25:30 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786324738 64
1786324743 64
1786324748 64
1786324753 64
1786324758 64
1786324763 64
1786324768 64
1786324773 64
1786324778 64
1786324783 64
1786324788 64
1786324793 64
1786324798 64
1786324803 64
1786324808 64
1786324813 64
1786324818 64
1786324823 64
1786324828 64
1786324833 64
```
</details>

---

