---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-27 03:38:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 22-39 cores)</summary>

```
1777275240 37
1777275245 37
1777275250 37
1777275255 37
1777275260 37
1777275265 22
1777275270 22
1777275275 22
1777275280 22
1777275285 22
1777275290 22
1777275295 24
1777275300 24
1777275305 24
1777275310 24
1777275315 24
1777275320 24
1777275325 24
1777275330 36
1777275335 36
```
</details>

---

