---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-12 05:49:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 431 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 59-76 cores)</summary>

```
1778579046 64
1778579051 64
1778579056 64
1778579061 64
1778579066 64
1778579071 64
1778579076 59
1778579081 59
1778579086 59
1778579091 59
1778579096 59
1778579101 59
1778579106 64
1778579111 64
1778579116 76
1778579121 76
1778579126 76
1778579131 64
1778579136 64
1778579141 76
```
</details>

---

