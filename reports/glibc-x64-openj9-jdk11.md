---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-17 10:21:30 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 896 |
| Sample Rate | 14.93/sec |
| Health Score | 933% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 83-91 cores)</summary>

```
1776435123 83
1776435128 83
1776435133 83
1776435138 83
1776435143 83
1776435148 83
1776435153 87
1776435158 87
1776435163 87
1776435168 83
1776435173 83
1776435178 87
1776435183 87
1776435188 87
1776435193 87
1776435198 91
1776435203 91
1776435208 91
1776435213 91
1776435218 91
```
</details>

---

