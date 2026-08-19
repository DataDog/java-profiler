---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 09:51:44 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1787147025 19
1787147030 24
1787147035 24
1787147040 24
1787147045 24
1787147050 24
1787147055 24
1787147060 29
1787147065 29
1787147070 29
1787147075 29
1787147080 29
1787147085 29
1787147090 29
1787147095 29
1787147100 29
1787147105 29
1787147110 29
1787147115 29
1787147120 29
```
</details>

---

