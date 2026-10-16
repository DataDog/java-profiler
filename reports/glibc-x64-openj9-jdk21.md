---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:53:46 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 62-82 cores)</summary>

```
1792144156 82
1792144161 82
1792144166 82
1792144171 62
1792144176 62
1792144181 62
1792144186 62
1792144191 62
1792144196 62
1792144201 62
1792144206 62
1792144211 62
1792144216 62
1792144221 65
1792144226 65
1792144231 65
1792144236 65
1792144241 65
1792144246 65
1792144251 65
```
</details>

---

