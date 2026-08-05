---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-05 10:18:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (4 unique values: 45-56 cores)</summary>

```
1785939169 51
1785939174 51
1785939179 51
1785939184 51
1785939189 51
1785939194 51
1785939199 51
1785939204 56
1785939209 56
1785939214 52
1785939219 52
1785939224 52
1785939229 52
1785939234 52
1785939239 52
1785939244 56
1785939249 56
1785939254 56
1785939259 56
1785939264 45
```
</details>

---

