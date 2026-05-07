---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 17:29:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 9-38 cores)</summary>

```
1778189118 9
1778189123 28
1778189128 28
1778189133 38
1778189138 38
1778189143 38
1778189148 38
1778189153 38
1778189158 38
1778189163 38
1778189168 26
1778189173 26
1778189178 26
1778189183 26
1778189188 26
1778189193 26
1778189198 26
1778189203 26
1778189208 26
1778189213 26
```
</details>

---

