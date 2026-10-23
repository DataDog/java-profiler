---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:04:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 11 |
| Allocations | 188 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 11 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1792764068 31
1792764073 31
1792764078 31
1792764083 31
1792764088 31
1792764093 31
1792764098 26
1792764103 26
1792764108 26
1792764113 26
1792764118 26
1792764123 26
1792764128 26
1792764133 26
1792764138 26
1792764143 26
1792764148 26
1792764153 26
1792764158 26
1792764163 26
```
</details>

---

