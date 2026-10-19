---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 06:39:49 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 28-40 cores)</summary>

```
1792406177 35
1792406182 35
1792406187 35
1792406192 35
1792406197 35
1792406202 35
1792406207 35
1792406212 40
1792406217 40
1792406222 40
1792406227 40
1792406232 40
1792406237 40
1792406242 40
1792406247 40
1792406252 40
1792406257 40
1792406262 40
1792406267 40
1792406272 40
```
</details>

---

