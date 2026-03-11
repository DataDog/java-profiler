---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 16:37:27 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 13 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 68-82 cores)</summary>

```
1773261129 79
1773261134 79
1773261139 79
1773261144 79
1773261149 77
1773261154 77
1773261159 77
1773261164 77
1773261169 77
1773261174 77
1773261179 77
1773261184 77
1773261189 77
1773261194 77
1773261199 77
1773261204 77
1773261209 82
1773261214 82
1773261219 68
1773261224 68
```
</details>

---

