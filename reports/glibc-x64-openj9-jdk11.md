---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:00:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 8 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 13-26 cores)</summary>

```
1793721212 26
1793721217 26
1793721222 26
1793721227 18
1793721232 18
1793721237 18
1793721242 18
1793721247 18
1793721252 18
1793721257 18
1793721262 18
1793721267 18
1793721272 18
1793721277 13
1793721282 13
1793721287 13
1793721292 13
1793721297 13
1793721302 13
1793721307 13
```
</details>

---

