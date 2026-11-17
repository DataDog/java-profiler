---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-11-17 13:29:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 10 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 38-38 cores)</summary>

```
1794939942 38
1794939947 38
1794939952 38
1794939957 38
1794939962 38
1794939967 38
1794939972 38
1794939977 38
1794939982 38
1794939987 38
1794939992 38
1794939997 38
1794940002 38
1794940007 38
1794940012 38
1794940017 38
1794940022 38
1794940027 38
1794940033 38
1794940038 38
```
</details>

---

