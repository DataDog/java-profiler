---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 16:21:37 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 66-87 cores)</summary>

```
1794950095 68
1794950100 68
1794950105 68
1794950110 68
1794950115 68
1794950120 68
1794950125 68
1794950130 68
1794950135 68
1794950140 68
1794950145 68
1794950150 66
1794950155 66
1794950160 87
1794950165 87
1794950170 87
1794950175 87
1794950180 87
1794950185 87
1794950190 87
```
</details>

---

