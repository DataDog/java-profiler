---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 09:38:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793367200 36
1793367205 48
1793367210 48
1793367215 48
1793367220 48
1793367225 36
1793367230 36
1793367235 36
1793367240 36
1793367245 36
1793367250 36
1793367255 36
1793367260 36
1793367265 36
1793367270 36
1793367275 36
1793367280 36
1793367285 36
1793367290 36
1793367295 36
```
</details>

---

