---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:15:15 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 10 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1795691126 84
1795691131 84
1795691136 84
1795691141 84
1795691146 84
1795691151 84
1795691156 84
1795691161 84
1795691166 84
1795691171 82
1795691176 82
1795691181 82
1795691186 82
1795691191 82
1795691196 82
1795691201 82
1795691206 82
1795691211 82
1795691216 82
1795691221 82
```
</details>

---

