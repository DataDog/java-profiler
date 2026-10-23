---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:56:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 841 |
| Sample Rate | 14.02/sec |
| Health Score | 876% |
| Threads | 10 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1792767108 27
1792767113 27
1792767118 27
1792767123 27
1792767128 27
1792767133 27
1792767138 27
1792767143 27
1792767148 27
1792767153 27
1792767158 27
1792767163 29
1792767168 29
1792767173 29
1792767178 29
1792767183 29
1792767188 29
1792767193 29
1792767198 29
1792767203 29
```
</details>

---

