---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 17:16:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794435126 48
1794435131 36
1794435136 36
1794435141 36
1794435146 36
1794435151 36
1794435156 36
1794435161 36
1794435166 36
1794435171 36
1794435176 36
1794435181 36
1794435186 36
1794435191 36
1794435196 36
1794435201 36
1794435206 36
1794435211 36
1794435216 36
1794435221 36
```
</details>

---

