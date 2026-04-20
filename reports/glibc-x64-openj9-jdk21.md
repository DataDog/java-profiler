---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 07:58:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1776686117 64
1776686122 64
1776686127 64
1776686132 60
1776686137 60
1776686142 60
1776686148 60
1776686153 60
1776686158 60
1776686163 60
1776686168 60
1776686173 60
1776686178 60
1776686183 60
1776686188 60
1776686193 60
1776686198 60
1776686203 60
1776686208 60
1776686213 60
```
</details>

---

