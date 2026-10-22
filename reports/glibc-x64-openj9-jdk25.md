---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 12:29:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
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
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1792686172 28
1792686177 28
1792686182 28
1792686187 26
1792686192 26
1792686197 26
1792686202 26
1792686207 26
1792686212 26
1792686217 26
1792686222 26
1792686227 28
1792686232 28
1792686237 30
1792686242 30
1792686247 30
1792686252 30
1792686257 30
1792686262 30
1792686267 30
```
</details>

---

