---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 16:51:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 66-76 cores)</summary>

```
1788382046 68
1788382051 68
1788382057 68
1788382062 66
1788382067 66
1788382072 66
1788382077 66
1788382082 66
1788382087 66
1788382092 68
1788382097 68
1788382102 68
1788382107 68
1788382112 68
1788382117 68
1788382122 68
1788382127 68
1788382132 76
1788382137 76
1788382142 76
```
</details>

---

