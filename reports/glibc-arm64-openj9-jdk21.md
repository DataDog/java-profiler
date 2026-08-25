---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 08:42:51 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 9 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 18-54 cores)</summary>

```
1787661408 18
1787661413 18
1787661418 18
1787661423 45
1787661428 45
1787661433 54
1787661438 54
1787661443 54
1787661448 54
1787661453 54
1787661458 54
1787661463 54
1787661468 54
1787661473 54
1787661478 54
1787661483 54
1787661488 54
1787661493 54
1787661498 54
1787661503 54
```
</details>

---

