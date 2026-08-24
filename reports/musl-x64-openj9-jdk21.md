---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-24 15:44:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787600210 64
1787600215 64
1787600220 64
1787600225 64
1787600230 64
1787600235 64
1787600240 64
1787600245 66
1787600250 66
1787600255 66
1787600260 66
1787600265 66
1787600270 66
1787600275 66
1787600280 66
1787600285 66
1787600290 66
1787600295 66
1787600300 66
1787600305 66
```
</details>

---

