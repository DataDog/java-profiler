---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 12:24:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 11 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 15 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1792772452 34
1792772457 34
1792772462 34
1792772467 34
1792772472 34
1792772477 34
1792772482 34
1792772487 34
1792772492 34
1792772497 34
1792772502 34
1792772507 34
1792772512 34
1792772517 39
1792772522 39
1792772527 39
1792772532 39
1792772537 39
1792772542 39
1792772547 39
```
</details>

---

