---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 14.55/sec |
| Health Score | 909% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 56-60 cores)</summary>

```
1790172176 59
1790172181 59
1790172186 59
1790172191 59
1790172196 59
1790172201 59
1790172206 59
1790172211 59
1790172216 58
1790172221 58
1790172226 58
1790172231 60
1790172236 60
1790172241 60
1790172246 60
1790172251 60
1790172256 60
1790172261 60
1790172266 59
1790172271 59
```
</details>

---

