---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-17 08:06:00 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (6 unique values: 44-62 cores)</summary>

```
1776427143 44
1776427148 44
1776427153 44
1776427158 44
1776427163 44
1776427168 44
1776427173 49
1776427178 49
1776427183 54
1776427188 54
1776427193 54
1776427198 54
1776427203 54
1776427208 54
1776427213 59
1776427218 59
1776427223 59
1776427228 59
1776427233 59
1776427238 59
```
</details>

---

