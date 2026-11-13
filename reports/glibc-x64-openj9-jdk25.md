---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 15:07:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 57-65 cores)</summary>

```
1794600132 57
1794600137 57
1794600142 57
1794600147 57
1794600152 57
1794600157 57
1794600162 57
1794600167 57
1794600172 57
1794600177 57
1794600182 57
1794600187 57
1794600192 65
1794600197 65
1794600202 65
1794600207 65
1794600212 65
1794600217 63
1794600222 63
1794600227 64
```
</details>

---

