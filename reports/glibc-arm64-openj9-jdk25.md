---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-29 07:13:55 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 14 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790680225 48
1790680230 48
1790680235 48
1790680240 48
1790680245 48
1790680250 48
1790680255 43
1790680261 43
1790680266 43
1790680271 43
1790680276 43
1790680281 43
1790680286 43
1790680291 43
1790680296 43
1790680301 43
1790680306 43
1790680311 43
1790680316 43
1790680321 43
```
</details>

---

