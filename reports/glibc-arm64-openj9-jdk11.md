---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 12:53:16 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 13 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794592159 51
1794592164 51
1794592169 51
1794592174 51
1794592179 51
1794592184 51
1794592189 51
1794592194 51
1794592199 51
1794592204 51
1794592209 51
1794592214 51
1794592219 51
1794592224 51
1794592229 51
1794592234 51
1794592240 46
1794592245 46
1794592250 46
1794592255 46
```
</details>

---

