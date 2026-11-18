---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 00:06:53 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1794978122 64
1794978127 64
1794978132 64
1794978137 64
1794978142 64
1794978147 64
1794978152 64
1794978157 64
1794978162 64
1794978167 64
1794978172 64
1794978177 64
1794978182 64
1794978187 64
1794978192 64
1794978197 64
1794978202 64
1794978207 64
1794978212 64
1794978217 62
```
</details>

---

