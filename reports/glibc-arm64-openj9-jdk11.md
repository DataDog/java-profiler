---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 09:43:02 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 44-47 cores)</summary>

```
1794494148 47
1794494153 47
1794494158 47
1794494163 47
1794494168 47
1794494173 47
1794494178 47
1794494183 47
1794494188 45
1794494193 45
1794494198 45
1794494203 45
1794494208 45
1794494213 45
1794494218 44
1794494223 44
1794494228 44
1794494233 44
1794494238 44
1794494243 44
```
</details>

---

