---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:41:12 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 11 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794487008 48
1794487013 48
1794487018 48
1794487023 43
1794487028 43
1794487033 43
1794487038 43
1794487043 43
1794487048 43
1794487053 43
1794487058 43
1794487063 43
1794487068 43
1794487073 48
1794487078 48
1794487083 48
1794487088 48
1794487093 48
1794487098 48
1794487103 48
```
</details>

---

