---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 05:55:32 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 5 |
| Sample Rate | 0.08/sec |
| Health Score | 5% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 52-53 cores)</summary>

```
1792576247 52
1792576252 52
1792576257 52
1792576262 52
1792576267 53
1792576272 53
1792576277 53
1792576282 53
1792576287 53
1792576292 53
1792576297 53
1792576302 53
1792576307 53
1792576312 53
1792576317 53
1792576322 53
1792576327 53
1792576332 53
1792576337 53
1792576342 53
```
</details>

---

