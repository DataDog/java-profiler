---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:02:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 14 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794427080 43
1794427085 43
1794427090 43
1794427095 43
1794427100 43
1794427105 43
1794427110 43
1794427115 43
1794427120 38
1794427125 38
1794427130 43
1794427135 43
1794427140 43
1794427145 43
1794427150 43
1794427155 43
1794427160 43
1794427165 43
1794427170 43
1794427175 43
```
</details>

---

