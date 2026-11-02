---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 14:28:38 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 10 |
| Allocations | 206 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793647446 36
1793647451 36
1793647456 36
1793647461 36
1793647466 36
1793647471 36
1793647476 36
1793647481 36
1793647486 36
1793647491 36
1793647496 36
1793647501 36
1793647506 36
1793647511 36
1793647516 36
1793647521 36
1793647526 36
1793647531 36
1793647536 36
1793647541 36
```
</details>

---

