---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 05:19:43 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 11 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 55-60 cores)</summary>

```
1778577361 55
1778577366 55
1778577371 55
1778577376 55
1778577381 60
1778577386 60
1778577391 58
1778577396 58
1778577401 58
1778577406 58
1778577411 58
1778577416 58
1778577421 58
1778577426 60
1778577431 60
1778577436 60
1778577441 60
1778577446 60
1778577451 60
1778577456 60
```
</details>

---

