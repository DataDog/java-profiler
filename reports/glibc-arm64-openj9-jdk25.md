---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:22:24 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (5 unique values: 49-59 cores)</summary>

```
1795429091 49
1795429096 49
1795429101 49
1795429106 49
1795429111 55
1795429116 55
1795429121 55
1795429126 55
1795429131 50
1795429136 50
1795429141 50
1795429146 50
1795429151 59
1795429156 59
1795429161 54
1795429166 54
1795429171 54
1795429176 54
1795429181 54
1795429186 54
```
</details>

---

