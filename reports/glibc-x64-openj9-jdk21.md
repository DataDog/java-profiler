---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 00:06:53 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1794978143 56
1794978148 56
1794978153 56
1794978158 56
1794978163 56
1794978168 56
1794978173 56
1794978179 56
1794978184 56
1794978189 56
1794978194 56
1794978199 56
1794978204 56
1794978209 56
1794978214 56
1794978219 56
1794978224 56
1794978229 56
1794978234 56
1794978239 54
```
</details>

---

