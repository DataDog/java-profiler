---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-28 18:13:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1777413969 14
1777413974 14
1777413979 14
1777413984 14
1777413989 14
1777413994 14
1777413999 14
1777414004 14
1777414009 14
1777414014 14
1777414019 14
1777414024 14
1777414029 14
1777414035 14
1777414040 14
1777414045 14
1777414050 14
1777414055 14
1777414060 14
1777414065 9
```
</details>

---

