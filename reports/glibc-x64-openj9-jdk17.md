---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 14:02:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 40-73 cores)</summary>

```
1793383052 42
1793383057 42
1793383062 42
1793383067 42
1793383072 42
1793383077 42
1793383082 42
1793383087 42
1793383092 40
1793383097 40
1793383102 40
1793383107 40
1793383112 40
1793383117 40
1793383122 40
1793383127 40
1793383132 40
1793383137 40
1793383142 73
1793383147 73
```
</details>

---

