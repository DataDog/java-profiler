---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-24 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792831098 51
1792831103 51
1792831108 51
1792831113 51
1792831118 51
1792831123 51
1792831128 51
1792831133 51
1792831138 64
1792831143 64
1792831148 64
1792831153 64
1792831158 64
1792831163 64
1792831168 64
1792831173 64
1792831178 64
1792831183 64
1792831188 64
1792831193 64
```
</details>

---

