---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:01:44 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1789682189 36
1789682194 36
1789682199 36
1789682204 36
1789682209 36
1789682214 36
1789682219 36
1789682224 36
1789682229 36
1789682234 36
1789682239 36
1789682244 36
1789682249 36
1789682254 31
1789682259 31
1789682264 31
1789682269 31
1789682274 31
1789682279 31
1789682284 31
```
</details>

---

