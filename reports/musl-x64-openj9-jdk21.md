---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 10:56:49 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1792767108 77
1792767113 77
1792767118 77
1792767123 77
1792767128 77
1792767133 77
1792767138 77
1792767143 77
1792767148 77
1792767153 77
1792767158 77
1792767163 77
1792767168 77
1792767173 75
1792767178 75
1792767183 75
1792767188 75
1792767193 75
1792767198 75
1792767203 75
```
</details>

---

