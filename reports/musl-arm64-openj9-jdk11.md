---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:52:44 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 10 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1064 |
| Sample Rate | 17.73/sec |
| Health Score | 1108% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1795013161 38
1795013166 38
1795013172 38
1795013177 38
1795013182 38
1795013187 38
1795013192 38
1795013197 38
1795013202 38
1795013207 38
1795013212 38
1795013217 38
1795013222 38
1795013227 38
1795013232 36
1795013237 36
1795013242 36
1795013247 36
1795013252 36
1795013257 36
```
</details>

---

