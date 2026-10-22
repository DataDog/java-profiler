---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 09:44:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1792676344 44
1792676349 44
1792676354 44
1792676359 44
1792676364 44
1792676369 44
1792676374 44
1792676379 44
1792676384 44
1792676389 44
1792676394 44
1792676399 44
1792676404 44
1792676409 44
1792676414 44
1792676419 44
1792676424 48
1792676429 48
1792676434 48
1792676439 48
```
</details>

---

