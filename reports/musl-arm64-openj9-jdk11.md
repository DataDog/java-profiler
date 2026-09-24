---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:52:01 EDT

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1790243056 48
1790243061 48
1790243066 48
1790243071 48
1790243076 48
1790243081 48
1790243086 48
1790243091 48
1790243096 46
1790243101 46
1790243106 46
1790243111 46
1790243116 46
1790243121 46
1790243126 46
1790243131 46
1790243136 46
1790243141 46
1790243146 46
1790243151 46
```
</details>

---

