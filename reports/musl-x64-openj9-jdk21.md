---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 14:07:41 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 311 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 12 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 64-73 cores)</summary>

```
1773252126 73
1773252131 73
1773252136 73
1773252141 73
1773252146 73
1773252151 73
1773252156 65
1773252161 65
1773252166 65
1773252171 65
1773252176 65
1773252181 65
1773252186 67
1773252191 67
1773252196 67
1773252201 67
1773252206 67
1773252211 65
1773252216 65
1773252221 65
```
</details>

---

