---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 07:03:22 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790161197 40
1790161202 40
1790161207 40
1790161212 40
1790161217 40
1790161222 40
1790161227 40
1790161232 40
1790161237 40
1790161242 40
1790161247 40
1790161252 40
1790161257 40
1790161262 40
1790161267 40
1790161272 40
1790161277 40
1790161282 40
1790161287 40
1790161292 40
```
</details>

---

