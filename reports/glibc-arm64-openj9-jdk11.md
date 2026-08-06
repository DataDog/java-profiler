---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 04:51:59 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 14.55/sec |
| Health Score | 909% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786006077 48
1786006082 48
1786006087 48
1786006092 43
1786006097 43
1786006102 43
1786006107 43
1786006112 43
1786006117 43
1786006122 43
1786006127 43
1786006132 43
1786006137 43
1786006142 43
1786006147 43
1786006152 43
1786006157 43
1786006162 43
1786006167 43
1786006172 48
```
</details>

---

