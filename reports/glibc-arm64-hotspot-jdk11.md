---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:35:09 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 13 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794357077 43
1794357082 48
1794357087 48
1794357092 48
1794357097 48
1794357102 48
1794357107 48
1794357112 48
1794357117 48
1794357122 48
1794357127 48
1794357132 48
1794357137 48
1794357142 48
1794357147 48
1794357152 48
1794357157 48
1794357162 48
1794357167 48
1794357172 48
```
</details>

---

