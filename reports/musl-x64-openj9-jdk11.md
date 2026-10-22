---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 09:44:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 42-80 cores)</summary>

```
1792676334 42
1792676339 42
1792676344 42
1792676349 42
1792676354 42
1792676359 42
1792676364 42
1792676369 42
1792676374 42
1792676379 42
1792676384 42
1792676389 42
1792676394 42
1792676399 42
1792676404 42
1792676409 59
1792676414 59
1792676419 59
1792676424 59
1792676429 80
```
</details>

---

