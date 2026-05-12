---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:45:07 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 14 |
| Allocations | 204 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778582460 59
1778582465 59
1778582470 59
1778582475 59
1778582480 59
1778582485 59
1778582490 64
1778582496 64
1778582501 64
1778582506 64
1778582511 64
1778582516 64
1778582521 64
1778582526 64
1778582531 64
1778582536 64
1778582541 64
1778582546 64
1778582551 64
1778582556 64
```
</details>

---

